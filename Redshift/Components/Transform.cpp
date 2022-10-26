#include <Redshift/Actor.h>

#include <Redshift/Components/Transform.h>

#include <Vendor/Glm/gtc/matrix_transform.hpp>

///////////////////////////////////////////////////////////
// Transform implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Transform::Transform(World* world, Actor* actor)
    : Component{ world, actor }
  {

  }

  R32M4 Transform::GetModelMatrix() const
  {
    R32M4 model{ glm::identity<R32M4>() };
    model = glm::translate(model, mPosition);
    model = glm::rotate(model, mRotation.x, mWorldRight);
    model = glm::rotate(model, mRotation.y, mWorldUp);
    model = glm::rotate(model, mRotation.z, mWorldFront);
    model = glm::scale(model, mScale);
    return model;
  }

  R32V3 Transform::GetWorldPosition() const
  {
    Actor* parent{ mActor->GetParent() };
    if (parent)
    {
      return parent->GetTransform()->GetWorldPosition() + (mPosition * mScale);
    }
    else
    {
      return (mPosition * mScale);
    }
  }

  R32V3 Transform::GetWorldRotation() const
  {
    return glm::degrees(mRotation);
  }

  R32Q Transform::GetWorldQuaternion() const
  {
    return mRotation;
  }

  R32V3 Transform::GetWorldScale() const
  {
    return mScale;
  }

  void Transform::SetWorldPosition(R32V3 position)
  {
    mPosition = position;
  }

  void Transform::SetWorldRotation(R32V3 rotation)
  {
    mRotation = glm::radians(rotation);
  }

  void Transform::SetWorldScale(R32V3 scale)
  {
    mScale = scale;
  }

  void Transform::SetLocalPosition(R32V3 position)
  {
    mPosition = position;
  }

  void Transform::SetLocalRotation(R32V3 rotation)
  {
    mRotation = glm::radians(rotation);
    R32Q q{ mRotation };
    mLocalRight = q * mWorldRight;
    mLocalUp = q * mWorldUp;
    mLocalFront = q * mWorldFront;
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetLocalRotation(GetRotation());
    }
  }

  void Transform::SetLocalScale(R32V3 scale)
  {
    mScale = scale;
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetLocalScale(GetScale());
    }
  }

  void Transform::AddWorldPosition(R32V3 position)
  {
    mPosition += position;
  }

  void Transform::AddWorldRotation(R32V3 rotation)
  {
    mRotation += glm::radians(rotation);
  }

  void Transform::AddWorldScale(R32V3 scale)
  {
    mScale += scale;
  }

  void Transform::AddLocalPosition(R32V3 position)
  {
    mPosition += position;
  }

  void Transform::AddLocalRotation(R32V3 rotation)
  {
    mRotation += glm::radians(rotation);
    R32Q q{ mRotation };
    mLocalRight = q * mWorldRight;
    mLocalUp = q * mWorldUp;
    mLocalFront = q * mWorldFront;
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetLocalRotation(GetRotation());
    }
  }

  void Transform::AddLocalScale(R32V3 scale)
  {
    mScale += scale;
    for (Actor* child : mActor->GetChildren())
    {
      child->GetTransform()->SetLocalScale(GetScale());
    }
  }
}