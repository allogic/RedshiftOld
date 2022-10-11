#ifndef RSH_WATCHDOG_H
#define RSH_WATCHDOG_H

#include <string>
#include <set>
#include <map>

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

///////////////////////////////////////////////////////////
// Watchdog definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class WatchDog
  {
  public:
    WatchDog(std::filesystem::path const& scanPath, std::string const& fileExt);

  public:
    void Update();

  public:
    inline std::set<std::filesystem::path> const& GetFilesCreated() const { return mFilesCreated; }
    inline std::set<std::filesystem::path> const& GetFilesDeleted() const { return mFilesDeleted; }
    inline std::set<std::filesystem::path> const& GetFilesModified() const { return mFilesModified; }

  private:
    void CheckFilesDeleted();
    void CheckFilesModified();
    void CheckFilesCreated();

  private:
    std::filesystem::path mScanPath{};
    std::string mFileExt{};

    std::map<std::filesystem::path, std::filesystem::file_time_type> mFileInfos{};

    std::set<std::filesystem::path> mFilesCreated{};
    std::set<std::filesystem::path> mFilesDeleted{};
    std::set<std::filesystem::path> mFilesModified{};
  };
}

#endif