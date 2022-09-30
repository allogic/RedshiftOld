#include <Redshift/World.h>
#include <Redshift/Shader.h>

#include <Editor/HotLoader.h>

///////////////////////////////////////////////////////////
// HotLoader implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  HotLoader::HotLoader(
    std::filesystem::path const& scenePath, std::string const& sceneExt, std::filesystem::path const& sceneStreamingPath,
    std::filesystem::path const& shaderPath, std::string const& shaderExt
  )
    : mScenePath{ scenePath }
    , mSceneExt{ sceneExt }
    , mSceneStreamingPath{ sceneStreamingPath }
    , mShaderPath{ shaderPath }
    , mShaderExt{ shaderExt }
  {
    std::filesystem::create_directory(mSceneStreamingPath);
  }

  void HotLoader::Update()
  {
    UpdateScenes();
    UpdateShaders();
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

  void HotLoader::UpdateShaders()
  {
    mShaderWatchdog.Update();

    for (auto const& file : mShaderWatchdog.FilesDeleted())
    {
      U32& shader{ World::GetShader(file.stem().string()) };
      if (shader)
      {
        Shader::Destroy(shader);
        shader = 0;
      }
    }
    
    for (auto const& file : mShaderWatchdog.FilesModified())
    {
      std::string vertexShader{};
      std::string fragmentShader{};
      if (Shader::ExtractShaderStages(file.string(), vertexShader, fragmentShader))
      {
        U32& shader{ World::GetShader(file.stem().string()) };
        if (shader)
        {
          Shader::Destroy(shader);
          shader = Shader::Create(vertexShader, fragmentShader);
        }
      }
    }
    
    for (auto const& file : mShaderWatchdog.FilesCreated())
    {
      std::string vertexShader{};
      std::string fragmentShader{};
      if (Shader::ExtractShaderStages(file.string(), vertexShader, fragmentShader))
      {
        U32& shader{ World::GetShader(file.stem().string()) };
        shader = Shader::Create(vertexShader, fragmentShader);
      }
    }
  }
}