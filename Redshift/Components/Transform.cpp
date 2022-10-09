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
    SetWorldPosition(other->GetWorldPosition());
    //SetWorldRotation(other->GetWorldRotation());
    SetWorldScale(other->GetWorldScale());

    SetLocalPosition(other->GetLocalPosition());
    SetLocalRotation(other->GetLocalRotation());
    SetLocalScale(other->GetLocalScale());
  }

  R32V3 Transform::GetWorldPosition() const
  {
    if (mActor->GetParent())
    {
      return GetWorldQuaternion() * mWorldPosition + GetLocalQuaternion() * mLocalPosition;
    }
    else
    {
      return GetWorldQuaternion() * mWorldPosition;
    }
  }

  R32V3 Transform::GetWorldRotation() const
  {
    return glm::degrees(mWorldRotation);
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
    return glm::degrees(mLocalRotation);
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
    mWorldPosition = worldPosition;
    mDirtyPosition = 1;
  }

  void Transform::SetWorldRotation(R32V3 worldRotation)
  {
    mWorldRotation = glm::radians(worldRotation);
    mDirtyPosition = 1;
    mDirtyRotation = 1;
  }

  void Transform::SetWorldScale(R32V3 worldScale)
  {
    mWorldScale = worldScale;
    mDirtyScale = 1;
  }

  void Transform::SetLocalPosition(R32V3 localPosition)
  {
    mLocalPosition = localPosition;
    mDirtyPosition = 1;
  }

  void Transform::SetLocalRotation(R32V3 localRotation)
  {
    mLocalRotation = glm::radians(localRotation);
    mLocalRight = GetLocalQuaternion() * GetWorldRight();
    mLocalUp = GetLocalQuaternion() * GetWorldUp();
    mLocalFront = GetLocalQuaternion() * GetWorldFront();
    mDirtyPosition = 1;
    mDirtyRotation = 1;
  }

  void Transform::SetLocalScale(R32V3 localScale)
  {
    mLocalScale = localScale;
    mDirtyScale = 1;
  }

  void Transform::AddWorldPosition(R32V3 worldPosition)
  {
    mWorldPosition += worldPosition;
    mDirtyPosition = 1;
  }

  void Transform::AddWorldRotation(R32V3 worldRotation)
  {
    mWorldRotation += glm::radians(worldRotation);
    mLocalRight = GetLocalQuaternion() * GetWorldRight();
    mLocalUp = GetLocalQuaternion() * GetWorldUp();
    mLocalFront = GetLocalQuaternion() * GetWorldFront();
    mDirtyPosition = 1;
    mDirtyRotation = 1;
  }

  void Transform::AddWorldScale(R32V3 worldScale)
  {
    mWorldScale += worldScale;
    mDirtyScale = 1;
  }

  void Transform::AddLocalPosition(R32V3 localPosition)
  {
    mLocalPosition += localPosition;
    mDirtyPosition = 1;
  }

  void Transform::AddLocalRotation(R32V3 localRotation)
  {
    mLocalRotation += glm::radians(localRotation);
    mLocalRight = GetLocalQuaternion() * GetWorldRight();
    mLocalUp = GetLocalQuaternion() * GetWorldUp();
    mLocalFront = GetLocalQuaternion() * GetWorldFront();
    mDirtyPosition = 1;
    mDirtyRotation = 1;
  }

  void Transform::AddLocalScale(R32V3 localScale)
  {
    mLocalScale += localScale;
    mDirtyScale = 1;
  }

  R32M4 Transform::GetModelMatrix()
  {
    return {};
  }

  void Transform::EvaluateChildPositions()
  {
    if (mDirtyPosition)
    {
      mDirtyPosition = 0;

      for (Actor* child : mActor->GetChildren())
      {
        child->GetTransform()->SetWorldPosition(GetWorldPosition());
        child->GetTransform()->EvaluateChildPositions();
      }
    }
  }

  void Transform::EvaluateChildRotations()
  {
    if (mDirtyRotation)
    {
      mDirtyRotation = 0;

      for (Actor* child : mActor->GetChildren())
      {
        child->GetTransform()->SetWorldPosition(GetWorldPosition());
        child->GetTransform()->SetLocalRotation(GetLocalRotation());
        child->GetTransform()->EvaluateChildRotations();
      }
    }
  }

  void Transform::EvaluateChildScales()
  {
    if (mDirtyScale)
    {
      mDirtyScale = 0;

      for (Actor* child : mActor->GetChildren())
      {
        child->GetTransform()->SetWorldScale(GetWorldScale());
        child->GetTransform()->EvaluateChildScales();
      }
    }
  }
}