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
  class Actor;

  class Camera : public Component
  {
  public:
    Camera(World* world, Actor* actor);

  public:
    inline R32 const& GetFov() const { return mFov; }
    inline R32 const& GetNear() const { return mNear; }
    inline R32 const& GetFar() const { return mFar; }

  public:
    inline void SetFov(R32 fov) { mFov = fov; }
    inline void SetNear(R32 near) { mNear = near; }
    inline void SetFar(R32 far) { mFar = far; }

  public:
    R32M4 GetProjectionMatrix();
    R32M4 GetViewMatrix();

  private:
    R32 mFov{ glm::radians(45.0f) };
    R32 mNear{ 0.001f };
    R32 mFar{ 1000.0f };
  };
}

#endif