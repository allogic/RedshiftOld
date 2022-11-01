#include <Redshift/World.h>

#include <Redshift/Components/Model.h>

///////////////////////////////////////////////////////////
// Model implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Model::Model(World* world, Actor* actor, std::string const& modelFile, std::string const& shaderName)
    : Component{ world, actor }
    , mShader{ mWorld->GetShader(shaderName) }
  {
    //Importer::LoadFbx(world, modelFile);
  }
}