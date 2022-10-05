#include <Redshift/Actor.h>

#include <Redshift/Components/Transform.h>

#include <Vendor/Glm/gtc/matrix_transform.hpp>

///////////////////////////////////////////////////////////
// Actor implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Actor::Actor(World* world, std::string const& name)
    : mWorld{ world }
    , mName{ name }
    , mTransform{ ComponentAttach<Transform>() }
  {

  }

  Actor::~Actor()
  {

  }

  void Actor::Update(R32 timeDelta)
  {

  }
}