#ifndef RSH_CAMERA_H
#define RSH_CAMERA_H

#include <Redshift/Types.h>
#include <Redshift/Component.h>

///////////////////////////////////////////////////////////
// Camera definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;
  class Transform;

  class Camera : public Component
  {
  public:
    Camera(World* world);
    Camera(World* world, R32 fov, R32 near, R32 far);

  public:
    inline R32 const& GetFov() const { return mFov; }
    inline R32 const& GetNear() const { return mNear; }
    inline R32 const& GetFar() const { return mFar; }

  public:
    R32M4 GetProjectionMatrix();
    R32M4 GetViewMatrix(Transform* transform);

  private:
    R32 mFov{ 45.0f };
    R32 mNear{ 0.001f };
    R32 mFar{ 1000.0f };
  };
}

#endif