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