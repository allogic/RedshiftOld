#include <Redshift/World.h>

#include <Redshift/Components/Model.h>

///////////////////////////////////////////////////////////
// Model implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Model::Model(World* world, Actor* actor, std::string const& meshName, std::string const& modelFile)
    : Component{ world, actor }
    , mMesh{ mWorld->GetMesh(meshName) }
  {

  }
}