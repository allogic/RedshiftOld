#include <filesystem>

#include <Redshift/World.h>

#include <Editor/HotLoader.h>

///////////////////////////////////////////////////////////
// HotLoader implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  HotLoader::HotLoader(std::filesystem::path const& scenePath, std::string const& sceneExt, std::filesystem::path const& sceneStreamingPath)
    : mScenePath{ scenePath }
    , mSceneExt{ sceneExt }
    , mSceneStreamingPath{ sceneStreamingPath }
  {
    std::filesystem::create_directory(mScenePath);
    std::filesystem::create_directory(mSceneStreamingPath);
  }

  void HotLoader::Update()
  {
    UpdateScenes();
  }

  void HotLoader::UpdateScenes()
  {
    mSceneWatchdog.Update();
    
    for (auto const& file : mSceneWatchdog.FilesDeleted())
    {
      std::filesystem::path tempFilePath{ mSceneStreamingPath / file.filename().string() };
      if (World::DestroyScene(file.stem().string()))
      {
        std::filesystem::remove(tempFilePath);
      }
    }
    
    for (auto const& file : mSceneWatchdog.FilesModified())
    {
      std::filesystem::path tempFilePath{ mSceneStreamingPath / file.filename().string() };
      if (World::DestroyScene(file.stem().string()))
      {
        std::filesystem::remove(tempFilePath);
        std::filesystem::copy(file, tempFilePath, std::filesystem::copy_options::overwrite_existing);
        if (World::CreateScene(file.stem().string(), tempFilePath.string()))
        {
    
        }
      }
    }
    
    for (auto const& file : mSceneWatchdog.FilesCreated())
    {
      std::filesystem::path tempFilePath{ mSceneStreamingPath / file.filename().string() };
      std::filesystem::copy(file, tempFilePath, std::filesystem::copy_options::overwrite_existing);
      if (World::CreateScene(file.stem().string(), tempFilePath.string()))
      {
    
      }
    }
  }
}