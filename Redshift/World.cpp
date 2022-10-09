#include <cstring>

#include <Redshift/World.h>
#include <Redshift/Platform.h>
#include <Redshift/Shader.h>

#include <Redshift/Components/Transform.h>
#include <Redshift/Components/Camera.h>

#include <Vendor/Glfw/glfw3.h>

#include <Vendor/ImGui/imgui.h>

#if defined(OS_WINDOWS)
  #undef APIENTRY
  #include <windows.h>
#elif defined(OS_LINUX)
  #include <dlfcn.h>
#else
  #error "Platform not supported!"
#endif

///////////////////////////////////////////////////////////
// World implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  World::World(U32 windowWidth, U32 windowHeight)
    : mWindowWidth{ windowWidth }
    , mWindowHeight{ windowHeight }
    , mGlfwContext{ glfwGetCurrentContext() }
    , mImGuiContext{ ImGui::GetCurrentContext() }
  {

  }

  World::~World()
  {
    ModuleUnloadAll();
  }

  U32 World::ModuleCreate(std::string const& moduleName, std::string const& moduleFile)
  {
#if defined(OS_WINDOWS)
    auto const moduleIt{ mModules.find(moduleName) };
    if (moduleIt == mModules.end())
    {
      HINSTANCE instanceNative{ LoadLibraryA(moduleFile.c_str()) };
      if (instanceNative)
      {
        ModuleCreateProc moduleCreateProc{ (ModuleCreateProc)GetProcAddress(instanceNative, "CreateModule") };
        ModuleDestroyProc moduleDestroyProc{ (ModuleDestroyProc)GetProcAddress(instanceNative, "DestroyModule") };
        if (moduleCreateProc && moduleDestroyProc)
        {
          Module* instanceModule{ moduleCreateProc(this) };
          if (instanceModule)
          {
            auto const [emplaceIt, inserted] { mModules.emplace(moduleName, ModuleProxy{ instanceNative, instanceModule, moduleCreateProc, moduleDestroyProc }) };
            return inserted;
          }
        }
      }
    }
#elif defined(OS_LINUX)
    auto const moduleIt{ mModules.find(moduleName) };
    if (moduleIt == mModules.end())
    {
      void* instanceNative{ dlopen(moduleFile.c_str(), RTLD_LAZY) };
      if (instanceNative)
      {
        ModuleCreateProc moduleCreateProc{ (ModuleCreateProc)dlsym(instanceNative, "CreateModule") };
        ModuleDestroyProc moduleDestroyProc{ (ModuleDestroyProc)dlsym(instanceNative, "DestroyModule") };
        if (moduleCreateProc && moduleDestroyProc)
        {
          Module* instanceModule{ moduleCreateProc(this) };
          if (instanceModule)
          {
            auto const [emplaceIt, inserted] { mModules.emplace(moduleName, ModuleProxy{ instanceNative, instanceModule, moduleCreateProc, moduleDestroyProc }) };
            return inserted;
          }
        }
      }
    }
#else
  #error "Platform not supported!"
#endif
return 0;
  }

  U32 World::ModuleDestroy(std::string const& moduleName)
  {
#if defined(OS_WINDOWS)
    auto const moduleIt = mModules.find(moduleName);
    if (moduleIt != mModules.end())
    {
      ModuleProxy moduleProxy = moduleIt->second;
      moduleProxy.DestroyProc(moduleProxy.InstanceModule);
      FreeLibrary((HMODULE)moduleProxy.InstanceNative);
      mModules.erase(moduleIt);
      return 1;
    }
#elif defined(OS_LINUX)
    auto const moduleIt = mModules.find(moduleName);
    if (moduleIt != mModules.end())
    {
      ModuleProxy moduleProxy = moduleIt->second;
      moduleProxy.DestroyProc(moduleProxy.InstanceModule);
      dlclose(moduleProxy.InstanceNative);
      mModules.erase(moduleIt);
      return 1;
    }
#else
  #error "Platform not supported!"
#endif
    return 0;
  }

  void World::ModuleUnloadAll()
  {
    for (auto const& [name, proxy] : mModules)
    {
#if defined(OS_WINDOWS)
      proxy.DestroyProc(proxy.InstanceModule);
      FreeLibrary((HMODULE)proxy.InstanceNative);
#elif defined(OS_LINUX)
      proxy.DestroyProc(proxy.InstanceModule);
      dlclose(proxy.InstanceNative);
#else
  #error "Platform not supported!"
#endif
    }
  }

  void World::Update(R32 timeDelta)
  {
    for (auto const& [name, proxy] : mModules)
    {
      proxy.InstanceModule->Update(timeDelta);
    }

    for (auto const& [name, actor] : mActors)
    {
      actor->GetTransform()->ReEvaluateTransform();
      actor->Update(timeDelta);
    }
  }

  void World::ActorDestroy(Actor* actor)
  {
    std::string const actorName{ actor->GetName() };
    delete actor;
    mActors.erase(actorName);
  }

  void World::ActorDestroy(std::string const& actorName)
  {
    delete mActors[actorName];
    mActors.erase(actorName);
  }

  Camera* World::GetMainCamera() const
  {
    Actor* actor{ GetMainEditorActor() };
    if (!actor)
    {
      actor = GetMainGameActor(); 
    }
    if (actor)
    {
      return actor->GetComponent<Camera>();
    }
    return nullptr;
  }

  U32 World::ShaderCreate(std::string const& shaderName, std::string const& shaderFile)
  {
    std::string vertexShader{};
    std::string fragmentShader{};
    if (Shader::ExtractShaderStages(shaderFile, vertexShader, fragmentShader))
    {
      Shader& shader{ GetShader(shaderName) };
      return shader.Create(vertexShader, fragmentShader);
    }
    return 0;
  }

  U32 World::ShaderDestroy(std::string const& shaderName)
  {
    Shader& shader{ GetShader(shaderName) };
    if (shader.Valid())
    {
      shader.Destroy();
      return 1;
    }
    return 0;
  }

  U32 World::MeshCreate(std::string const& meshName)
  {
    return 0;
  }

  U32 World::MeshDestroy(std::string const& meshName)
  {
    return 0;
  }

  void World::PollEvents()
  {
    glfwPollEvents();

    for (U32 i{ GLFW_KEY_SPACE }; i < GLFW_KEY_LAST; i++)
    {
      I32 action{ glfwGetKey(mGlfwContext, i) };

      mKeyboardKeys[i].Prev = mKeyboardKeys[i].Curr;

      if (action == GLFW_PRESS)
      {
        if (mKeyboardKeys[i].Curr != eEventStateDown && mKeyboardKeys[i].Prev != eEventStateHeld)
        {
          mKeyboardKeys[i].Curr = eEventStateDown;
        }
        else
        {
          mKeyboardKeys[i].Curr = eEventStateHeld;
        }
      }

      if (action == GLFW_RELEASE)
      {
        if (mKeyboardKeys[i].Curr != eEventStateUp && mKeyboardKeys[i].Prev == eEventStateHeld)
        {
          mKeyboardKeys[i].Curr = eEventStateUp;
        }
        else
        {
          mKeyboardKeys[i].Curr = eEventStateNone;
        }
      }
    }

    for (U32 i{}; i < GLFW_MOUSE_BUTTON_LAST; i++)
    {
      I32 action{ glfwGetMouseButton(mGlfwContext, i) };

      mMouseKeys[i].Prev = mMouseKeys[i].Curr;

      if (action == GLFW_PRESS)
      {
        if (mMouseKeys[i].Curr != eEventStateDown && mMouseKeys[i].Prev != eEventStateHeld)
        {
          mMouseKeys[i].Curr = eEventStateDown;
        }
        else
        {
          mMouseKeys[i].Curr = eEventStateHeld;
        }
      }

      if (action == GLFW_RELEASE)
      {
        if (mMouseKeys[i].Curr != eEventStateUp && mMouseKeys[i].Prev == eEventStateHeld)
        {
          mMouseKeys[i].Curr = eEventStateUp;
        }
        else
        {
          mMouseKeys[i].Curr = eEventStateNone;
        }
      }
    }
  }

  void World::DebugLine(R32V3 p0, R32V3 p1, R32V4 c)
  {
    mDebugVertexBuffer[mDebugVertexOffset + 0].Position = p0;
    mDebugVertexBuffer[mDebugVertexOffset + 1].Position = p1;

    mDebugVertexBuffer[mDebugVertexOffset + 0].Color = c;
    mDebugVertexBuffer[mDebugVertexOffset + 1].Color = c;

    mDebugElementBuffer[mDebugElementOffset + 0] = mDebugVertexOffset + 0;
    mDebugElementBuffer[mDebugElementOffset + 1] = mDebugVertexOffset + 1;

    mDebugVertexOffset += 2;
    mDebugElementOffset += 2;
  }

  void World::DebugBox(R32V3 p, R32V3 s, R32V4 c, R32Q r)
  {
    mDebugVertexBuffer[mDebugVertexOffset + 0].Position = p + r * R32V3{ 0.0f, 0.0f, 0.0f };
    mDebugVertexBuffer[mDebugVertexOffset + 1].Position = p + r * R32V3{ s.x, 0.0f, 0.0f };
    mDebugVertexBuffer[mDebugVertexOffset + 2].Position = p + r * R32V3{ 0.0f, s.y, 0.0f };
    mDebugVertexBuffer[mDebugVertexOffset + 3].Position = p + r * R32V3{ s.x, s.y, 0.0f };

    mDebugVertexBuffer[mDebugVertexOffset + 4].Position = p + r * R32V3{ 0.0f, 0.0f, s.z };
    mDebugVertexBuffer[mDebugVertexOffset + 5].Position = p + r * R32V3{ s.x, 0.0f, s.z };
    mDebugVertexBuffer[mDebugVertexOffset + 6].Position = p + r * R32V3{ 0.0f, s.y, s.z };
    mDebugVertexBuffer[mDebugVertexOffset + 7].Position = p + r * R32V3{ s.x, s.y, s.z };

    mDebugVertexBuffer[mDebugVertexOffset + 0].Color = c;
    mDebugVertexBuffer[mDebugVertexOffset + 1].Color = c;
    mDebugVertexBuffer[mDebugVertexOffset + 2].Color = c;
    mDebugVertexBuffer[mDebugVertexOffset + 3].Color = c;

    mDebugVertexBuffer[mDebugVertexOffset + 4].Color = c;
    mDebugVertexBuffer[mDebugVertexOffset + 5].Color = c;
    mDebugVertexBuffer[mDebugVertexOffset + 6].Color = c;
    mDebugVertexBuffer[mDebugVertexOffset + 7].Color = c;

    mDebugElementBuffer[mDebugElementOffset + 0] = mDebugVertexOffset + 0;
    mDebugElementBuffer[mDebugElementOffset + 1] = mDebugVertexOffset + 1;
    mDebugElementBuffer[mDebugElementOffset + 2] = mDebugVertexOffset + 0;
    mDebugElementBuffer[mDebugElementOffset + 3] = mDebugVertexOffset + 2;
    mDebugElementBuffer[mDebugElementOffset + 4] = mDebugVertexOffset + 2;
    mDebugElementBuffer[mDebugElementOffset + 5] = mDebugVertexOffset + 3;

    mDebugElementBuffer[mDebugElementOffset + 6] = mDebugVertexOffset + 3;
    mDebugElementBuffer[mDebugElementOffset + 7] = mDebugVertexOffset + 1;
    mDebugElementBuffer[mDebugElementOffset + 8] = mDebugVertexOffset + 4;
    mDebugElementBuffer[mDebugElementOffset + 9] = mDebugVertexOffset + 5;
    mDebugElementBuffer[mDebugElementOffset + 10] = mDebugVertexOffset + 4;
    mDebugElementBuffer[mDebugElementOffset + 11] = mDebugVertexOffset + 6;

    mDebugElementBuffer[mDebugElementOffset + 12] = mDebugVertexOffset + 6;
    mDebugElementBuffer[mDebugElementOffset + 13] = mDebugVertexOffset + 7;
    mDebugElementBuffer[mDebugElementOffset + 14] = mDebugVertexOffset + 7;
    mDebugElementBuffer[mDebugElementOffset + 15] = mDebugVertexOffset + 5;
    mDebugElementBuffer[mDebugElementOffset + 16] = mDebugVertexOffset + 0;
    mDebugElementBuffer[mDebugElementOffset + 17] = mDebugVertexOffset + 4;

    mDebugElementBuffer[mDebugElementOffset + 18] = mDebugVertexOffset + 1;
    mDebugElementBuffer[mDebugElementOffset + 19] = mDebugVertexOffset + 5;
    mDebugElementBuffer[mDebugElementOffset + 20] = mDebugVertexOffset + 2;
    mDebugElementBuffer[mDebugElementOffset + 21] = mDebugVertexOffset + 6;
    mDebugElementBuffer[mDebugElementOffset + 22] = mDebugVertexOffset + 3;
    mDebugElementBuffer[mDebugElementOffset + 23] = mDebugVertexOffset + 7;

    mDebugVertexOffset += 8;
    mDebugElementOffset += 24;
  }

  void World::DebugRender()
  {
    Camera* camera{ GetMainCamera() };

    if (camera)
    {
      if (mDebugShader.Valid())
      {
        mDebugShader.Bind();

        mDebugShader.SetUniformR32M4("UniformProjectionMatrix", camera->GetProjectionMatrix());
        mDebugShader.SetUniformR32M4("UniformViewMatrix", camera->GetViewMatrix());

        mDebugMesh.Bind();

        mDebugMesh.UploadVertices(mDebugVertexBuffer, mDebugVertexBufferSize);
        mDebugMesh.UploadElements(mDebugElementBuffer, mDebugElementBufferSize);

        mDebugMesh.Render(mDebugElementBufferSize);

        mDebugMesh.UnBind();
        mDebugShader.UnBind();
      }
    }

    if (mDebugVertexBufferSize)
    {
      std::memset(mDebugVertexBuffer, 0, mDebugVertexBufferSize);
    }

    if (mDebugElementBufferSize)
    {
      std::memset(mDebugElementBuffer, 0, mDebugElementBufferSize);
    }

    mDebugVertexOffset = 0;
    mDebugElementOffset = 0;
  }
}