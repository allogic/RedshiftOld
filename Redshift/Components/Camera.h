#ifndef RSH_CAMERA_H
#define RSH_CAMERA_H

#include <Redshift/Types.h>
#include <Redshift/Component.h>

namespace rsh
{
  class Camera : public Component
  {
  public:
    Camera(R32 fov, R32 near, R32 far);

  private:
    R32 mFov{};
    R32 mNear{};
    R32 mFar{};
  };
}

#endif