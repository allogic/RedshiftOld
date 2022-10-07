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
    std::filesystem::path const& modulePath, std::string const& moduleExt, std::filesystem::path const& moduleStreamingPath,
    std::filesystem::path const& shaderPath, std::string const& shaderExt, std::filesystem::path const& shaderStreamingPath
  )
    : mWorld{ world }
    , mModulePath{ modulePath }
    , mModuleExt{ moduleExt }
    , mModuleStreamingPath{ moduleStreamingPath }
    , mShaderPath{ shaderPath }
    , mShaderExt{ shaderExt }
    , mShaderStreamingPath{ shaderStreamingPath }
  {
    std::filesystem::create_directory(mModuleStreamingPath);
    std::filesystem::create_directory(mShaderStreamingPath);
  }

  void HotLoader::Update()
  {
    UpdateModules();
    UpdateShaders();
  }

  void HotLoader::UpdateModules()
  {
    mModuleWatchdog.Update();
    
    for (auto const& file : mModuleWatchdog.GetFilesDeleted())
    {
      std::filesystem::path tempFile{ mModuleStreamingPath / file.filename().string() };

      if (mWorld->ModuleDestroy(file.stem().string()))
      {
        std::filesystem::remove(tempFile);

        RSH_LOG("Module %s deleted\n", file.stem().string().c_str());
      }
    }
    
    for (auto const& file : mModuleWatchdog.GetFilesModified())
    {
      std::filesystem::path tempFile{ mModuleStreamingPath / file.filename().string() };

      if (mWorld->ModuleDestroy(file.stem().string()))
      {
        std::filesystem::remove(tempFile);

        RSH_LOG("Module %s deleted\n", file.stem().string().c_str());
      }

      std::filesystem::copy(file, tempFile, std::filesystem::copy_options::overwrite_existing);

      if (mWorld->ModuleCreate(file.stem().string(), tempFile.string()))
      {
        RSH_LOG("Module %s created\n", file.stem().string().c_str());
      }
      else
      {
        std::filesystem::remove(tempFile);
      }
    }
    
    for (auto const& file : mModuleWatchdog.GetFilesCreated())
    {
      std::filesystem::path tempFile{ mModuleStreamingPath / file.filename().string() };

      std::filesystem::copy(file, tempFile, std::filesystem::copy_options::overwrite_existing);

      if (mWorld->ModuleCreate(file.stem().string(), tempFile.string()))
      {
        RSH_LOG("Module %s created\n", file.stem().string().c_str());
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