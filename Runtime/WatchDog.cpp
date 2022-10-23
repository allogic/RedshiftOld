#include <Redshift/Types.h>

#include <Runtime/WatchDog.h>

///////////////////////////////////////////////////////////
// WatchDog implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  WatchDog::WatchDog(std::filesystem::path const& scanPath, std::string const& fileExt)
    : mScanPath{ scanPath }
    , mFileExt{ fileExt }
  {
    std::filesystem::create_directory(mScanPath);
  }

  void WatchDog::Update()
  {
    CheckFilesDeleted();
    CheckFilesModified();
    CheckFilesCreated();
  }

  void WatchDog::CheckFilesCreated()
  {
    mFilesCreated.clear();
    for (auto const& file : std::filesystem::directory_iterator{ mScanPath })
    {
      if (file.path().extension() == mFileExt)
      {
        if (mFileInfos.find(file.path()) == mFileInfos.cend())
        {
          mFileInfos.emplace(file.path(), std::filesystem::last_write_time(file.path()));
          mFilesCreated.emplace(file.path());
        }
      }
    }
  }

  void WatchDog::CheckFilesDeleted()
  {
    mFilesDeleted.clear();
    std::erase_if(mFileInfos, [&](auto const& fileInfo)
      {
        std::filesystem::path const& file{ fileInfo.first };
        U32 exists{ (U32)std::filesystem::exists(file) };
        if (!exists)
        {
          mFilesDeleted.emplace(file);
        }
        return !exists;
      });
  }

  void WatchDog::CheckFilesModified()
  {
    mFilesModified.clear();
    for (auto& [file, prevTime] : mFileInfos)
    {
      std::filesystem::file_time_type time{ std::filesystem::last_write_time(file) };
      if (time > prevTime)
      {
        prevTime = time;
        mFilesModified.emplace(file);
      }
    }
  }
}