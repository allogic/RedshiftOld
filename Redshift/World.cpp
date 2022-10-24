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

    for (auto const& actor : mActors)
    {
      actor->Update(timeDelta);
    }
  }

  void World::ActorDestroy(Actor* actor)
  {
    mActors.erase(std::find(mActors.begin(), mActors.end(), actor));
    delete actor;
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
}