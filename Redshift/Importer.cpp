#include <Redshift/World.h>
#include <Redshift/Importer.h>

///////////////////////////////////////////////////////////
// Importer implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Importer::Importer(World* world)
    : mWorld{ world }
    , mFbxManager{ FbxManager::Create() }
    , mFbxIoSettings{ FbxIOSettings::Create(mFbxManager, IOSROOT) }
  {
    mFbxManager->SetIOSettings(mFbxIoSettings);
  }

  Importer::~Importer()
  {
    mFbxIoSettings->Destroy();
    mFbxManager->Destroy();
  }

  void Importer::LoadFbx(std::string const& fbxFile)
  {
    FbxImporter* fbxImporter{ FbxImporter::Create(mFbxManager, "") };

    if (fbxImporter->Initialize(fbxFile.c_str(), -1, mFbxManager->GetIOSettings()))
    {
      FbxScene* fbxScene{ FbxScene::Create(mFbxManager, "myScene") };

      fbxImporter->Import(fbxScene);

      FbxNode* fbxRootNode{ fbxScene->GetRootNode() };

      if (fbxRootNode)
      {

      }

      fbxScene->Destroy();
    }

    fbxImporter->Destroy();
  }
}