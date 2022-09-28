#include <Editor/Watchdog.h>

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
    for (const auto& file : std::filesystem::directory_iterator{ mScanPath })
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
    std::erase_if(mFileInfos, [&](const auto& fileInfo)
      {
        const auto& file{ fileInfo.first };
        const auto exists{ std::filesystem::exists(file) };
        if (!exists) mFilesDeleted.emplace(file);
        return !exists;
      });
  }

  void Watchdog::CheckFilesModified()
  {
    mFilesModified.clear();
    for (auto& [file, prevTime] : mFileInfos)
    {
      auto const time{ std::filesystem::last_write_time(file) };
      if (time > prevTime)
      {
        prevTime = time;
        mFilesModified.emplace(file);
      }
    }
  }
}