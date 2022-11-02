#ifndef RSH_WATCH_DOG_H
#define RSH_WATCH_DOG_H

#include <string>
#include <set>
#include <map>
#include <filesystem>

///////////////////////////////////////////////////////////
// WatchDog definition
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