#include <Redshift/World.h>
#include <Redshift/Platform.h>
#include <Redshift/ShaderFactory.h>

#if defined(OS_WINDOWS)
  #include <windows.h>
#elif defined(OS_LINUX)
  #include <dlfcn.h>
#else
  #error "Platform not supported!"
#endif

///////////////////////////////////////////////////////////
// Externs
///////////////////////////////////////////////////////////

extern rsh::World sWorld;

///////////////////////////////////////////////////////////
// World implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  U32 World::CreateScene(std::string const& sceneName, std::string const& sceneFile)
  {
#if defined(OS_WINDOWS)
    auto const sceneIt{ sWorld.mScenes.find(sceneName) };
    if (sceneIt == sWorld.mScenes.end())
    {
      HINSTANCE instanceModule{ LoadLibraryA(sceneFile.c_str()) };
      if (instanceModule)
      {
        SceneCreateProc sceneCreateProc{ (SceneCreateProc)GetProcAddress(instanceModule, "CreateScene") };
        SceneDestroyProc sceneDestroyProc{ (SceneDestroyProc)GetProcAddress(instanceModule, "DestroyScene") };
        if (sceneCreateProc && sceneDestroyProc)
        {
          Scene* instanceScene{ sceneCreateProc(&sWorld) };
          if (instanceScene)
          {
            auto const [emplaceIt, inserted] { sWorld.mScenes.emplace(sceneName, SceneProxy{ instanceModule, instanceScene, sceneCreateProc, sceneDestroyProc }) };
            return inserted;
          }
        }
      }
    }
#elif defined(OS_LINUX)
    auto const sceneIt{ sWorld.mScenes.find(sceneName) };
    if (sceneIt == sWorld.mScenes.end())
    {
      void* instanceModule{ dlopen(sceneFile.c_str(), RTLD_LAZY) };
      if (instanceModule)
      {
        SceneCreateProc sceneCreateProc{ (SceneCreateProc)dlsym(instanceModule, "CreateScene") };
        SceneDestroyProc sceneDestroyProc{ (SceneDestroyProc)dlsym(instanceModule, "DestroyScene") };
        if (sceneCreateProc && sceneDestroyProc)
        {
          Scene* instanceScene{ sceneCreateProc(&sWorld) };
          if (instanceScene)
          {
            auto const [emplaceIt, inserted] { sWorld.mScenes.emplace(sceneName, SceneProxy{ instanceModule, instanceScene, sceneCreateProc, sceneDestroyProc }) };
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

  U32 World::DestroyScene(std::string const& sceneName)
  {
#if defined(OS_WINDOWS)
    auto const sceneIt = sWorld.mScenes.find(sceneName);
    if (sceneIt != sWorld.mScenes.end())
    {
      SceneProxy sceneProxy = sceneIt->second;
      sceneProxy.DestroyProc(sceneProxy.InstanceScene);
      FreeLibrary((HMODULE)sceneProxy.InstanceModule);
      sWorld.mScenes.erase(sceneIt);
      return 1;
    }
#elif defined(OS_LINUX)
    auto const sceneIt = world->mScenes.find(sceneName);
    if (sceneIt != world->mScenes.end())
    {
      SceneProxy sceneProxy = sceneIt->second;
      sceneProxy.DestroyProc(sceneProxy.InstanceScene);
      dlclose(sceneProxy.InstanceModule);
      sWorld.mScenes.erase(sceneIt);
      return 1;
    }
#else
  #error "Platform not supported!"
#endif
    return 0;
  }

  void World::DestroyActor(World* world, Actor* actor)
  {

  }

  U32 World::CreateShader(std::string const& shaderName, std::string const& shaderFile)
  {
    return 0;
  }

  U32 World::DestroyShader(std::string const& shaderName)
  {
    return 0;
  }

  Handle<U32>& World::GetShaderHandle(std::string const& shaderName)
  {
    return sWorld.mShaders[shaderName];
  }
}