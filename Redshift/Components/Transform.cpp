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

  void Transform::ApplyTransform(Transform* other)
  {
    SetLocalPosition(other->GetLocalPosition());
    SetLocalRotation(other->GetLocalRotation());
    SetLocalScale(other->GetLocalScale());

    SetWorldPosition(other->GetWorldPosition());
    SetWorldRotation(other->GetWorldRotation());
    SetWorldScale(other->GetWorldScale());
  }

  R32V3 Transform::GetWorldPosition() const
  {
    return mWorldPosition;
  }

  R32V3 Transform::GetWorldRotation() const
  {
    return mWorldRotation;
  }

  R32Q Transform::GetWorldQuaternion() const
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

  R32Q Transform::GetLocalQuaternion() const
  {
    return mLocalRotation;
  }

  R32V3 Transform::GetLocalScale() const
  {
    return mLocalScale;
  }

  void Transform::SetWorldPosition(R32V3 worldPosition)
  {
    mWorldPosition = worldPosition + mLocalPosition; // Remove localPosition if possible

    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetWorldPosition(mWorldPosition);
    }
  }

  void Transform::SetWorldRotation(R32V3 worldRotation)
  {
    mWorldRotation = glm::radians(worldRotation);
  }

  void Transform::SetWorldScale(R32V3 worldScale)
  {
    mWorldScale = worldScale;
  }

  void Transform::SetLocalPosition(R32V3 localPosition)
  {
    mLocalPosition = localPosition;
  }

  void Transform::SetLocalRotation(R32V3 localRotation)
  {
    mLocalRotation = glm::radians(localRotation);
  }

  void Transform::SetLocalScale(R32V3 localScale)
  {
    mLocalScale = localScale;
  }

  R32M4 Transform::GetModelMatrix()
  {
    return {};
  }
}