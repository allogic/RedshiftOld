#include <fstream>

#include <Redshift/World.h>

#include <Redshift/Utils/FbxImporter.h>
#include <Redshift/Utils/FileReader.h>

///////////////////////////////////////////////////////////
// FbxImporter implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  FbxImporter::FbxImporter(World* world)
    : mWorld{ world }
    , mFbxManager{ FbxManager::Create() }
  {

  }

  void FbxImporter::LoadFbx(std::filesystem::path const& fbxFile)
  {
    std::vector<U8> bytes{};

    if (FileReader::ReadBytes(bytes, fbxFile.string()))
    {
      
    }
  }
}