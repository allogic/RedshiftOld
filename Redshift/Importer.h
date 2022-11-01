#ifndef RSH_IMPORTER_H
#define RSH_IMPORTER_H

#include <string>
#include <vector>

#include <Redshift/Types.h>
#include <Redshift/Vertex.h>

#include <Vendor/FbxSdk/fbxsdk.h>

///////////////////////////////////////////////////////////
// Importer definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class Importer
  {
  public:
    Importer(World* world);
    virtual ~Importer();

  public:
    void LoadFbx(std::string const& fbxFile);

  private:
    World* mWorld{};

    FbxManager* mFbxManager{};
    FbxIOSettings* mFbxIoSettings{};
  };
}

#endif