#include <Redshift/Actor.h>

#include <Redshift/Components/Transform.h>

///////////////////////////////////////////////////////////
// Transform implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Transform::Transform(World* world, Actor* actor)
    : Component{ world, actor }
  {

  }

  R32V3 Transform::GetWorldPosition() const
  {
    R32V3 p{ mLocalPosition };
    Actor* next{ mActor->GetParent() };
    while (next)
    {
      p += next->GetComponent<Transform>()->GetLocalPosition();
      next = next->GetParent();
    }
    return p;
  }

  R32V3 Transform::GetWorldRotation() const
  {
    return mWorldRotation;
  }

  R32V3 Transform::GetWorldScale() const
  {
    R32V3 s{ mLocalScale };
    Actor* next{ mActor->GetParent() };
    while (next)
    {
      s *= next->GetComponent<Transform>()->GetLocalScale();
      next = next->GetParent();
    }
    return s;
  }

  R32V3 Transform::GetLocalPosition() const
  {
    return mLocalPosition;
  }

  R32V3 Transform::GetLocalRotation() const
  {
    return mLocalRotation;
  }

  R32V3 Transform::GetLocalScale() const
  {
    return mLocalScale;
  }

  void Transform::SetWorldPosition(R32V3 position)
  {
    mWorldPosition = position;
  }

  void Transform::SetWorldRotation(R32V3 rotation)
  {
    mWorldRotation = glm::radians(rotation);
  }

  void Transform::SetWorldScale(R32V3 scale)
  {
    mWorldScale = scale;
  }

  void Transform::SetLocalPosition(R32V3 position)
  {
    mLocalPosition = position;
  }

  void Transform::SetLocalRotation(R32V3 rotation)
  {
    mLocalRotation = glm::radians(rotation);
  }

  void Transform::SetLocalScale(R32V3 scale)
  {
    mLocalScale = scale;
  }

  R32M4 Transform::GetModelMatrix()
  {
    return {};
  }
}