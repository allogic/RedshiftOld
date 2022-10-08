#include <Redshift/Types.h>

#include <Runtime/Watchdog.h>

///////////////////////////////////////////////////////////
// Watchdog implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Watchdog::Watchdog(std::filesystem::path const& scanPath, std::string const& fileExt)
    : mScanPath{ scanPath }
    , mFileExt{ fileExt }
  {
    std::filesystem::create_directory(mScanPath);
  }

  void Watchdog::Update()
  {
    CheckFilesDeleted();
    CheckFilesModified();
    CheckFilesCreated();
  }

  void Watchdog::CheckFilesCreated()
  {
    mFilesCreated.clear();
    for (auto const& file : std::filesystem::directory_iterator{ mScanPath })
    {
      if (file.path().extension() != mFileExt) continue;
      if (mFileInfos.find(file.path()) != mFileInfos.cend()) continue;
      mFileInfos.emplace(file.path(), std::filesystem::last_write_time(file.path()));
      mFilesCreated.emplace(file.path());
    }
  }

  void Watchdog::CheckFilesDeleted()
  {
    mFilesDeleted.clear();
    std::erase_if(mFileInfos, [&](auto const& fileInfo)
      {
        std::filesystem::path const& file{ fileInfo.first };
        U32 exists{ (U32)std::filesystem::exists(file) };
        if (!exists) mFilesDeleted.emplace(file);
        return !exists;
      });
  }

  void Watchdog::CheckFilesModified()
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