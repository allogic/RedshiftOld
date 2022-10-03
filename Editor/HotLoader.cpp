#include <Redshift/World.h>
#include <Redshift/Shader.h>
#include <Redshift/Debug.h>

#include <Editor/HotLoader.h>

///////////////////////////////////////////////////////////
// HotLoader implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  HotLoader::HotLoader(
    World* world,
    std::filesystem::path const& scenePath, std::string const& sceneExt, std::filesystem::path const& sceneStreamingPath,
    std::filesystem::path const& shaderPath, std::string const& shaderExt, std::filesystem::path const& shaderStreamingPath
  )
    : mWorld{ world }
    , mScenePath{ scenePath }
    , mSceneExt{ sceneExt }
    , mSceneStreamingPath{ sceneStreamingPath }
    , mShaderPath{ shaderPath }
    , mShaderExt{ shaderExt }
    , mShaderStreamingPath{ shaderStreamingPath }
  {
    std::filesystem::create_directory(mSceneStreamingPath);
    std::filesystem::create_directory(mShaderStreamingPath);
  }

  void HotLoader::Update()
  {
    UpdateScenes();
    UpdateShaders();
  }

  void HotLoader::UpdateScenes()
  {
    mSceneWatchdog.Update();
    
    for (auto const& file : mSceneWatchdog.GetFilesDeleted())
    {
      std::filesystem::path tempFile{ mSceneStreamingPath / file.filename().string() };

      if (mWorld->SceneDestroy(file.stem().string()))
      {
        std::filesystem::remove(tempFile);

        RSH_LOG("Scene %s deleted\n", file.stem().string().c_str());
      }
    }
    
    for (auto const& file : mSceneWatchdog.GetFilesModified())
    {
      std::filesystem::path tempFile{ mSceneStreamingPath / file.filename().string() };

      if (mWorld->SceneDestroy(file.stem().string()))
      {
        std::filesystem::remove(tempFile);

        RSH_LOG("Scene %s deleted\n", file.stem().string().c_str());
      }

      std::filesystem::copy(file, tempFile, std::filesystem::copy_options::overwrite_existing);

      if (mWorld->SceneCreate(file.stem().string(), tempFile.string()))
      {
        RSH_LOG("Scene %s created\n", file.stem().string().c_str());
      }
      else
      {
        std::filesystem::remove(tempFile);
      }
    }
    
    for (auto const& file : mSceneWatchdog.GetFilesCreated())
    {
      std::filesystem::path tempFile{ mSceneStreamingPath / file.filename().string() };

      std::filesystem::copy(file, tempFile, std::filesystem::copy_options::overwrite_existing);

      if (mWorld->SceneCreate(file.stem().string(), tempFile.string()))
      {
        RSH_LOG("Scene %s created\n", file.stem().string().c_str());
      }
      else
      {
        std::filesystem::remove(tempFile);
      }
    }
  }

  void HotLoader::UpdateShaders()
  {
    mShaderWatchdog.Update();

    for (auto const& file : mShaderWatchdog.GetFilesDeleted())
    {
      std::filesystem::path tempFile{ mShaderStreamingPath / file.filename().string() };

      if (mWorld->ShaderDestroy(file.stem().string()))
      {
        std::filesystem::remove(tempFile);

        RSH_LOG("Shader %s deleted\n", file.stem().string().c_str());
      }
    }
    
    for (auto const& file : mShaderWatchdog.GetFilesModified())
    {
      std::filesystem::path tempFile{ mShaderStreamingPath / file.filename().string() };

      if (mWorld->ShaderDestroy(file.stem().string()))
      {
        std::filesystem::remove(tempFile);

        RSH_LOG("Shader %s deleted\n", file.stem().string().c_str());
      }

      std::filesystem::copy(file, tempFile, std::filesystem::copy_options::overwrite_existing);

      if (mWorld->ShaderCreate(file.stem().string(), tempFile.string()))
      {
        RSH_LOG("Shader %s created\n", file.stem().string().c_str());
      }
      else
      {
        std::filesystem::remove(tempFile);
      }
    }
    
    for (auto const& file : mShaderWatchdog.GetFilesCreated())
    {
      std::filesystem::path tempFile{ mShaderStreamingPath / file.filename().string() };

      std::filesystem::copy(file, tempFile, std::filesystem::copy_options::overwrite_existing);

      if (mWorld->ShaderCreate(file.stem().string(), tempFile.string()))
      {
        RSH_LOG("Shader %s created\n", file.stem().string().c_str());
      }
      else
      {
        std::filesystem::remove(tempFile);
      }
    }
  }
}