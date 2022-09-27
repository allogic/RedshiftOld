#ifndef RSH_HOTLOADER_H
#define RSH_HOTLOADER_H

#include <string>
#include <filesystem>

#include <Editor/Watchdog.h>

namespace rsh
{
  class HotLoader
  {
  public:
    HotLoader(std::filesystem::path const& scenePath, std::string const& sceneExt, std::filesystem::path const& sceneStreamingPath);

  public:
    void Update();

  private:
    void UpdateScenes();

  private:
    std::filesystem::path mScenePath{};
    std::string mSceneExt{};
    std::filesystem::path mSceneStreamingPath{};

    Watchdog mSceneWatchdog{ mScenePath, mSceneExt };
  };
}

#endif