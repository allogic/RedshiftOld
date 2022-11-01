#ifndef RSH_FBX_IMPORTER_H
#define RSH_FBX_IMPORTER_H

#include <string>
#include <vector>

#include <Redshift/Types.h>
#include <Redshift/Vertex.h>
#include <Redshift/Platform.h>

#if defined(OS_WINDOWS)
  #include <filesystem>
#elif defined(OS_LINUX)
  #include <experimental/filesystem>
  namespace std
  {
    namespace filesystem = experimental::filesystem;
  }
#else
  #error "Platform not supported!"
#endif

#include <Vendor/FbxSdk/fbxsdk.h>

///////////////////////////////////////////////////////////
// FbxImporter definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class FbxImporter
  {
  public:
    FbxImporter(World* world);

  public:
    void LoadFbx(std::filesystem::path const& fbxFile);

  private:
    World* mWorld{};
    FbxManager* mFbxManager{};
  };
}

#endif