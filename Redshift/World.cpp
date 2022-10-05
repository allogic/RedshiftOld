#include <cstring>

#include <Redshift/World.h>
#include <Redshift/Platform.h>
#include <Redshift/Shader.h>

#include <Redshift/Components/Transform.h>
#include <Redshift/Components/Camera.h>

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
  World::World(U32 editorWidth, U32 editorHeight)
    : mEditorWidth{ editorWidth }
    , mEditorHeight{ editorHeight }
  {

  }

  World::~World()
  {
    SceneUnloadAll();
  }

  U32 World::SceneCreate(std::string const& sceneName, std::string const& sceneFile)
  {
#if defined(OS_WINDOWS)
    auto const sceneIt{ mScenes.find(sceneName) };
    if (sceneIt == mScenes.end())
    {
      HINSTANCE instanceModule{ LoadLibraryA(sceneFile.c_str()) };
      if (instanceModule)
      {
        SceneCreateProc sceneCreateProc{ (SceneCreateProc)GetProcAddress(instanceModule, "CreateScene") };
        SceneDestroyProc sceneDestroyProc{ (SceneDestroyProc)GetProcAddress(instanceModule, "DestroyScene") };
        if (sceneCreateProc && sceneDestroyProc)
        {
          Scene* instanceScene{ sceneCreateProc(this) };
          if (instanceScene)
          {
            auto const [emplaceIt, inserted] { mScenes.emplace(sceneName, SceneProxy{ instanceModule, instanceScene, sceneCreateProc, sceneDestroyProc }) };
            return inserted;
          }
        }
      }
    }
#elif defined(OS_LINUX)
    auto const sceneIt{ mScenes.find(sceneName) };
    if (sceneIt == mScenes.end())
    {
      void* instanceModule{ dlopen(sceneFile.c_str(), RTLD_LAZY) };
      if (instanceModule)
      {
        SceneCreateProc sceneCreateProc{ (SceneCreateProc)dlsym(instanceModule, "CreateScene") };
        SceneDestroyProc sceneDestroyProc{ (SceneDestroyProc)dlsym(instanceModule, "DestroyScene") };
        if (sceneCreateProc && sceneDestroyProc)
        {
          Scene* instanceScene{ sceneCreateProc(this) };
          if (instanceScene)
          {
            auto const [emplaceIt, inserted] { mScenes.emplace(sceneName, SceneProxy{ instanceModule, instanceScene, sceneCreateProc, sceneDestroyProc }) };
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

  U32 World::SceneDestroy(std::string const& sceneName)
  {
#if defined(OS_WINDOWS)
    auto const sceneIt = mScenes.find(sceneName);
    if (sceneIt != mScenes.end())
    {
      SceneProxy sceneProxy = sceneIt->second;
      sceneProxy.DestroyProc(sceneProxy.InstanceScene);
      FreeLibrary((HMODULE)sceneProxy.InstanceModule);
      mScenes.erase(sceneIt);
      return 1;
    }
#elif defined(OS_LINUX)
    auto const sceneIt = mScenes.find(sceneName);
    if (sceneIt != mScenes.end())
    {
      SceneProxy sceneProxy = sceneIt->second;
      sceneProxy.DestroyProc(sceneProxy.InstanceScene);
      dlclose(sceneProxy.InstanceModule);
      mScenes.erase(sceneIt);
      return 1;
    }
#else
  #error "Platform not supported!"
#endif
    return 0;
  }

  void World::SceneUnloadAll()
  {
    for (auto const& [name, proxy] : mScenes)
    {
#if defined(OS_WINDOWS)
      proxy.DestroyProc(proxy.InstanceScene);
      FreeLibrary((HMODULE)proxy.InstanceModule);
#elif defined(OS_LINUX)
      proxy.DestroyProc(proxy.InstanceScene);
      dlclose(proxy.InstanceModule);
#else
  #error "Platform not supported!"
#endif
    }
  }

  void World::Update(R32 timeDelta)
  {
    for (auto const& [name, proxy] : mScenes)
    {
      proxy.InstanceScene->Update(timeDelta);
    }

    for (auto const& [name, actor] : mActors)
    {
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
    Actor* mainActor{ GetMainActor() };

    if (mainActor)
    {
      if (mDebugShader.Valid())
      {
        mDebugShader.Bind();

        Transform* transform{ mainActor->GetTransform() };
        Camera* camera{ mainActor->GetComponent<Camera>() };

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