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

  R32V3 Actor::GetWorldCoordinates()
  {
    R32V3 p{ mTransform->GetPosition() };
    R32Q r{ mTransform->GetRotation() };
    R32V3 s{ mTransform->GetScale() };

    p = r * p;
    p = p * s;

    Actor* next{ GetParent() };
    while (next)
    {
      p = next->mTransform->GetPosition();
      r = next->mTransform->GetRotation();
      s = next->mTransform->GetScale();

      p = r * p;
      p = p * s;

      next = next->GetParent();
    }

    return p;
  }
}