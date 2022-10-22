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
    Actor* parent{ mActor->GetParent() };
    if (parent)
    {
      return parent->GetTransform()->GetWorldPosition() + GetLocalQuaternion() * (mLocalPosition * mLocalScale);
    }
    else
    {
      return GetWorldQuaternion() * (mWorldPosition * mWorldScale) + GetLocalQuaternion() * (mLocalPosition * mLocalScale);
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
    return mWorldScale * mLocalScale;
  }

  void Transform::SetWorldPosition(R32V3 worldPosition)
  {
    mWorldPosition = worldPosition;
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
    mLocalRight = GetLocalQuaternion() * GetWorldRight();
    mLocalUp = GetLocalQuaternion() * GetWorldUp();
    mLocalFront = GetLocalQuaternion() * GetWorldFront();
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetLocalRotation(GetLocalRotation());
    }
  }

  void Transform::SetLocalScale(R32V3 localScale)
  {
    mLocalScale = localScale;
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetLocalScale(GetLocalScale());
    }
  }

  void Transform::AddWorldPosition(R32V3 worldPosition)
  {
    mWorldPosition += worldPosition;
  }

  void Transform::AddWorldRotation(R32V3 worldRotation)
  {
    mWorldRotation += glm::radians(worldRotation);
    mLocalRight = GetLocalQuaternion() * GetWorldRight();
    mLocalUp = GetLocalQuaternion() * GetWorldUp();
    mLocalFront = GetLocalQuaternion() * GetWorldFront();
  }

  void Transform::AddWorldScale(R32V3 worldScale)
  {
    mWorldScale += worldScale;
  }

  void Transform::AddLocalPosition(R32V3 localPosition)
  {
    mLocalPosition += localPosition;
  }

  void Transform::AddLocalRotation(R32V3 localRotation)
  {
    mLocalRotation += glm::radians(localRotation);
    mLocalRight = GetLocalQuaternion() * GetWorldRight();
    mLocalUp = GetLocalQuaternion() * GetWorldUp();
    mLocalFront = GetLocalQuaternion() * GetWorldFront();
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetLocalRotation(GetLocalRotation());
    }
  }

  void Transform::AddLocalScale(R32V3 localScale)
  {
    mLocalScale += localScale;
  }

  R32M4 Transform::GetModelMatrix()
  {
    return {};
  }
}