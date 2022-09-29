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

namespace rsh
{
  class Watchdog
  {
  public:
    Watchdog(std::filesystem::path const& scanPath, std::string const& fileExt);

  public:
    void Update();

  public:
    inline auto const& FilesCreated() const { return mFilesCreated; }
    inline auto const& FilesDeleted() const { return mFilesDeleted; }
    inline auto const& FilesModified() const { return mFilesModified; }

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