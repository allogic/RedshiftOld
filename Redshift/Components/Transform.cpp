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
    return mWorldPosition + mLocalPosition;
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
    mWorldPosition = GetWorldQuaternion() * worldPosition;
    mDirtyPosition = 1;
  }

  void Transform::SetWorldRotation(R32V3 worldRotation)
  {
    mWorldRotation = glm::radians(worldRotation);
    SetWorldPosition(mWorldPosition);
    mDirtyRotation = 1;
  }

  void Transform::SetWorldScale(R32V3 worldScale)
  {
    mWorldScale = worldScale;
    mDirtyScale = 1;
  }

  void Transform::SetLocalPosition(R32V3 localPosition)
  {
    mLocalPosition = GetLocalQuaternion() * localPosition;
    mDirtyPosition = 1;
  }

  void Transform::SetLocalRotation(R32V3 localRotation)
  {
    mLocalRotation = glm::radians(localRotation);
    SetLocalPosition(mLocalPosition);
    mLocalRight = GetLocalQuaternion() * mLocalRight;
    mLocalUp = GetLocalQuaternion() * mLocalUp;
    mLocalFront = GetLocalQuaternion() * mLocalFront;
    mDirtyRotation = 1;
  }

  void Transform::SetLocalScale(R32V3 localScale)
  {
    mLocalScale = localScale;
    mDirtyScale = 1;
  }

  R32M4 Transform::GetModelMatrix()
  {
    return {};
  }

  void Transform::ReEvaluateTransform()
  {
    if (mDirtyRotation)
    {
      mDirtyRotation = 0;

      for (Actor* child : mActor->GetChildren())
      {
        child->GetTransform()->SetWorldRotation(mWorldRotation);
      }
    }

    if (mDirtyPosition)
    {
      mDirtyPosition = 0;

      for (Actor* child : mActor->GetChildren())
      {
        child->GetTransform()->SetWorldPosition(mWorldPosition);
      }
    }
  }
}