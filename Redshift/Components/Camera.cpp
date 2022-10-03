#include <Redshift/World.h>

#include <Redshift/Components/Camera.h>
#include <Redshift/Components/Transform.h>

#include <Vendor/Glm/gtc/matrix_transform.hpp>

///////////////////////////////////////////////////////////
// World implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Camera::Camera(World* world)
    : Component{ world }
  {

  }

  Camera::Camera(World* world, R32 fov, R32 near, R32 far)
    : Component{ world }
    , mFov{ fov }
    , mNear{ near }
    , mFar{ far }
  {

  }

  R32M4 Camera::GetProjectionMatrix()
  {
    R32 aspect{ (R32)mWorld->GetEditorWidth() / mWorld->GetEditorHeight() };
    return glm::perspective(glm::radians(mFov), aspect, mNear, mFar);
  }

  R32M4 Camera::GetViewMatrix(Transform* transform)
  {
    R32V3 u{ 0.0f, 1.0f, 0.0f };
    R32V3 f{ 0.0f, 0.0f, 1.0f };
    R32V3 p{ transform->GetPosition() };
    R32Q r{ transform->GetRotation() };

    f = r * f;
    p = r * p;

    return glm::lookAt(p, p + f, u);
  }
}