#include <Redshift/World.h>

#include <Redshift/Components/Model.h>

///////////////////////////////////////////////////////////
// Model implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Model::Model(World* world, Actor* actor, std::string const& meshName, std::string const& meshFile)
    : Component{ world, actor }
    , mMeshName{ meshName }
    , mMeshFile{ meshFile }
    , mMesh{ mWorld->GetMesh(meshName).Create<VertexPb, U32>(meshFile) }
  {

  }
}