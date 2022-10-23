#ifndef RSH_MODEL_H
#define RSH_MODEL_H

#include <string>

#include <Redshift/Types.h>
#include <Redshift/Component.h>
#include <Redshift/Mesh.h>

///////////////////////////////////////////////////////////
// Model definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;
  class Actor;

  class Model : public Component
  {
  public:
    Model(World* world, Actor* actor, std::string const& meshName, std::string const& modelFile);

  private:
    Mesh& mMesh;
  };
}

#endif