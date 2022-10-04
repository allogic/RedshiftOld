#include <Redshift/Component.h>
#include <Redshift/Actor.h>

///////////////////////////////////////////////////////////
// Component implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Component::Component(World* world, Actor* actor)
    : mWorld{ world }
    , mActor{ actor }
  {

  }
}