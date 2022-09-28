#include <Redshift/Components/Camera.h>

namespace rsh
{
  Camera::Camera(R32 fov, R32 near, R32 far)
    : Component{}
    , mFov{ fov }
    , mNear{ near }
    , mFar{ far }
  {

  }
}