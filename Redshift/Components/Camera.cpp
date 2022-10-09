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
    R32 aspect{ mWorld->GetAspectRatio() };

    return glm::perspective(mFov, aspect, mNear, mFar);
  }

  R32M4 Camera::GetViewMatrix()
  {
    R32V3 position{ mActor->GetTransform()->GetWorldPosition() };
    R32V3 up{ mActor->GetTransform()->GetLocalUp() };
    R32V3 front{ mActor->GetTransform()->GetLocalFront() };

    return glm::lookAt(position, position + front, up);
  }
}