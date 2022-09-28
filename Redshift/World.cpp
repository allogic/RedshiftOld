#include <Redshift/World.h>
#include <Redshift/Platform.h>

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
      HINSTANCE instance{ LoadLibraryA(sceneFile.c_str()) };
      if (instance)
      {
        SceneCreateProc sceneCreateProc{ (SceneCreateProc)GetProcAddress(instance, "CreateScene") };
        SceneDestroyProc sceneDestroyProc{ (SceneDestroyProc)GetProcAddress(instance, "DestroyScene") };
        if (sceneCreateProc && sceneDestroyProc)
        {
          Scene* scene{ sceneCreateProc(&sWorld) };
          if (scene)
          {
            auto const [emplaceIt, inserted] { sWorld.mScenes.emplace(sceneName, SceneProxy{ instance, scene, sceneCreateProc, sceneDestroyProc }) };
            return inserted;
          }
        }
      }
    }
#elif defined(OS_LINUX)
    auto const sceneIt{ sWorld.mScenes.find(sceneName) };
    if (sceneIt == sWorld.mScenes.end())
    {
      void* instance{ dlopen(sceneFile.c_str(), RTLD_LAZY) };
      if (instance)
      {
        SceneCreateProc sceneCreateProc{ (SceneCreateProc)dlsym(instance, "CreateScene") };
        SceneDestroyProc sceneDestroyProc{ (SceneDestroyProc)dlsym(instance, "DestroyScene") };
        if (sceneCreateProc && sceneDestroyProc)
        {
          Scene* scene{ sceneCreateProc(&sWorld) };
          if (scene)
          {
            auto const [emplaceIt, inserted] { sWorld.mScenes.emplace(sceneName, SceneProxy{ instance, scene, sceneCreateProc, sceneDestroyProc }) };
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
      sceneProxy.DestroyProc(sceneProxy.Scene);
      FreeLibrary((HMODULE)sceneProxy.Instance);
      sWorld.mScenes.erase(sceneIt);
      return 1;
    }
#elif defined(OS_LINUX)
    auto const sceneIt = sWorld.mScenes.find(sceneName);
    if (sceneIt != sWorld.mScenes.end())
    {
      SceneProxy sceneProxy = sceneIt->second;
      sceneProxy.DestroyProc(SceneProxy.scene);
      dlclose(sceneProxy.Instance);
      sWorld.mScenes.erase(sceneIt);
      return 1;
    }
#else
  #error "Platform not supported!"
#endif
    return 0;
  }
}