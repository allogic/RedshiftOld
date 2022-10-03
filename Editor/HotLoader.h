#ifndef RSH_HOTLOADER_H
#define RSH_HOTLOADER_H

#include <string>

#include <Redshift/Platform.h>

#if defined(OS_WINDOWS)
  #include <filesystem>
#elif defined(OS_LINUX)
  #include <experimental/filesystem>
  namespace std
  {
    namespace filesystem = experimental::filesystem;
  }
#else
  #error "Platform not supported!"
#endif

#include <Editor/Watchdog.h>

///////////////////////////////////////////////////////////
// HotLoader definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class HotLoader
  {
  public:
    HotLoader(
      World* world,
      std::filesystem::path const& scenePath, std::string const& sceneExt, std::filesystem::path const& sceneStreamingPath,
      std::filesystem::path const& shaderPath, std::string const& shaderExt, std::filesystem::path const& shaderStreamingPath
    );

  public:
    void Update();

  private:
    void UpdateScenes();
    void UpdateShaders();

  private:
    World* mWorld{};

    std::filesystem::path mScenePath{};
    std::string mSceneExt{};
    std::filesystem::path mSceneStreamingPath{};

    std::filesystem::path mShaderPath{};
    std::string mShaderExt{};
    std::filesystem::path mShaderStreamingPath{};

    Watchdog mSceneWatchdog{ mScenePath, mSceneExt };
    Watchdog mShaderWatchdog{ mShaderPath, mShaderExt };
  };
}

#endif