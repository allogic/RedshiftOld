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
    return mWorldPosition;
  }

  R32V3 Transform::GetWorldRotation() const
  {
    return mWorldRotation;
  }

  R32V3 Transform::GetWorldScale() const
  {
    return mWorldScale;
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

  void Transform::SetWorldPosition(R32V3 worldPosition)
  {
    mWorldPosition = worldPosition + mLocalPosition;
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetWorldPosition(mWorldPosition);
    }
  }

  void Transform::SetWorldRotation(R32V3 rotation)
  {
    mWorldRotation = glm::radians(rotation);
  }

  void Transform::SetWorldScale(R32V3 scale)
  {
    mWorldScale = scale;
  }

  void Transform::SetLocalPosition(R32V3 localPosition)
  {
    mLocalPosition = localPosition;
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