#include <Redshift/World.h>
#include <Redshift/Actor.h>

#include <Redshift/Components/Camera.h>
#include <Redshift/Components/Transform.h>

#include <Vendor/Glm/gtc/matrix_transform.hpp>

///////////////////////////////////////////////////////////
// World implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Camera::Camera(World* world, Actor* actor)
    : Component{ world, actor }
  {

  }

  R32M4 Camera::GetProjectionMatrix()
  {
    R32 aspect{ (R32)mWorld->GetEditorWidth() / mWorld->GetEditorHeight() };
    return glm::perspective(glm::radians(mFov), aspect, mNear, mFar);
  }

  R32M4 Camera::GetViewMatrix()
  {
    R32V3 u{ 0.0f, 1.0f, 0.0f };
    R32V3 f{ 0.0f, 0.0f, 1.0f };
    R32V3 p{ mActor->GetTransform()->GetWorldPosition() };
    R32Q r{ mActor->GetTransform()->GetWorldRotation() };

    f = r * f;
    p = r * p;

    return glm::lookAt(p, p + f, u);
  }
}