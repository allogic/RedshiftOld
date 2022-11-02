#ifndef RSH_HOT_LOADER_H
#define RSH_HOT_LOADER_H

#include <string>
#include <filesystem>

#include <Runtime/WatchDog.h>

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
      std::filesystem::path const& modulePath, std::string const& moduleExt, std::filesystem::path const& moduleStreamingPath,
      std::filesystem::path const& shaderPath, std::string const& shaderExt, std::filesystem::path const& shaderStreamingPath
    );

  public:
    void Update();

  private:
    void UpdateModules();
    void UpdateShaders();

  private:
    World* mWorld{};

    std::filesystem::path mModulePath{};
    std::filesystem::path mShaderPath{};

    std::string mModuleExt{};
    std::string mShaderExt{};

    std::filesystem::path mModuleStreamingPath{};
    std::filesystem::path mShaderStreamingPath{};

    WatchDog mModuleWatchDog{ mModulePath, mModuleExt };
    WatchDog mShaderWatchDog{ mShaderPath, mShaderExt };
  };
}

#endif