#include <windows.h>

#include <Redshift/World.h>
#include <Redshift/Platform.h>

///////////////////////////////////////////////////////////
// Externs
///////////////////////////////////////////////////////////

extern rsh::World sWorld;

///////////////////////////////////////////////////////////
// World implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  U32 World::CreateScene(std::string const& sceneName, std::string const& scenePath)
  {
#if defined(OS_WINDOWS)
    auto const sceneIt{ sWorld.mScenes.find(sceneName) };
    if (sceneIt == sWorld.mScenes.end())
    {
      HINSTANCE instance{ LoadLibraryA(scenePath.c_str()) };
      if (instance)
      {
        SceneCreateProc sceneCreateProc{ (SceneCreateProc)GetProcAddress(instance, "CreateScene") };
        SceneDestroyProc sceneDestroyProc{ (SceneDestroyProc)GetProcAddress(instance, "DestroyScene") };
        if (sceneCreateProc && sceneDestroyProc)
        {
          Scene* scene{ sceneCreateProc(&sWorld) };
          if (scene)
          {
            auto const& [emplaceIt, inserted] { sWorld.mScenes.emplace(sceneName, SceneProxy{ instance, scene, sceneCreateProc, sceneDestroyProc }) };
            return inserted;
          }
        }
      }
    }
#elif defined(OS_LINUX)
  #warning "Platform not implemented!"
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
      sceneProxy.destroyProc(sceneProxy.scene);
      FreeLibrary((HMODULE)sceneProxy.instance);
      sWorld.mScenes.erase(sceneIt);
      return 1;
    }
#elif defined(OS_LINUX)
  #warning "Platform not implemented!"
#else
  #error "Platform not supported!"
#endif
    return 0;
  }
}