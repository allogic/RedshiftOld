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
    SetWorldRotation(other->GetWorldRotation());
    //SetWorldScale(other->GetWorldScale());

    SetLocalPosition(other->GetLocalPosition());
    SetLocalRotation(other->GetLocalRotation());
    //SetLocalScale(other->GetLocalScale());
  }

  void Transform::SetWorldPosition(R32V3 worldPosition)
  {
    mWorldPosition = worldPosition;
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetWorldPosition(GetWorldPosition());
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
    mLocalRight = GetLocalQuaternion() * GetWorldRight();
    mLocalUp = GetLocalQuaternion() * GetWorldUp();
    mLocalFront = GetLocalQuaternion() * GetWorldFront();
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetLocalRotation(GetLocalRotation());
      child->GetTransform()->SetWorldPosition(GetWorldPosition());
    }
  }

  void Transform::SetLocalScale(R32V3 localScale)
  {
    mLocalScale = localScale;
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
      child->GetTransform()->SetWorldPosition(GetWorldPosition());
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