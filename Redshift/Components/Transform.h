#ifndef RSH_TRANSFORM_H
#define RSH_TRANSFORM_H

#include <Redshift/Types.h>
#include <Redshift/Component.h>

///////////////////////////////////////////////////////////
// Transform definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class Transform : public Component
  {
  public:
    Transform(World* world);
    Transform(World* world, R32V3 position, R32V3 rotation, R32V3 scale);

  public:
    inline R32V3 const& GetPosition() const { return mPosition; }
    inline R32V3 const& GetRotation() const { return mRotation; }
    inline R32V3 const& GetScale() const { return mScale; }

  public:
    inline void SetPosition(R32V3 position) { mPosition = position; }
    inline void SetRotation(R32V3 rotation) { mRotation = glm::radians(rotation); }
    inline void SetScale(R32V3 scale) { mScale = scale; }

  public:
    inline void AddPosition(R32V3 position) { mPosition += position; }
    inline void AddRotation(R32V3 rotation) { mRotation += glm::radians(rotation); }
    inline void AddScale(R32V3 scale) { mScale += scale; }

  public:
    R32M4 GetModelMatrix();

  private:
    R32V3 mPosition{ 0.0f, 0.0f, 0.0f };
    R32V3 mRotation{ 0.0f, 0.0f, 0.0f };
    R32V3 mScale{ 1.0f, 1.0f, 1.0f };
  };
}

#endif