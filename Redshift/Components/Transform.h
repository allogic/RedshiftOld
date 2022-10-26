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
  class Actor;

  class Transform : public Component
  {
  public:
    Transform(World* world, Actor* actor);

  public:
    inline R32V3 const& GetWorldRight() const { return mWorldRight; }
    inline R32V3 const& GetWorldUp() const { return mWorldUp; }
    inline R32V3 const& GetWorldFront() const { return mWorldFront; }

    inline R32V3 const& GetLocalRight() const { return mLocalRight; }
    inline R32V3 const& GetLocalUp() const { return mLocalUp; }
    inline R32V3 const& GetLocalFront() const { return mLocalFront; }

  public:
    inline R32V3 GetPosition() const { return mPosition; }
    inline R32V3 GetRotation() const { return glm::degrees(mRotation); }
    inline R32Q GetQuaternion() const { return mRotation; }
    inline R32V3 GetScale() const { return mScale; }

  public:
    R32M4 GetModelMatrix() const;

  public:
    R32V3 GetWorldPosition() const;
    R32V3 GetWorldRotation() const;
    R32Q GetWorldQuaternion() const;
    R32V3 GetWorldScale() const;

  public:
    void SetWorldPosition(R32V3 position);
    void SetWorldRotation(R32V3 rotation);
    void SetWorldScale(R32V3 scale);

    void SetLocalPosition(R32V3 position);
    void SetLocalRotation(R32V3 rotation);
    void SetLocalScale(R32V3 scale);

  public:
    void AddWorldPosition(R32V3 position);
    void AddWorldRotation(R32V3 rotation);
    void AddWorldScale(R32V3 scale);

    void AddLocalPosition(R32V3 position);
    void AddLocalRotation(R32V3 rotation);
    void AddLocalScale(R32V3 scale);

  private:
    R32V3 const mWorldRight{ 1.0f, 0.0f, 0.0f };
    R32V3 const mWorldUp{ 0.0f, 1.0f, 0.0f };
    R32V3 const mWorldFront{ 0.0f, 0.0f, 1.0f };

    R32V3 mLocalRight{ 1.0f, 0.0f, 0.0f };
    R32V3 mLocalUp{ 0.0f, 1.0f, 0.0f };
    R32V3 mLocalFront{ 0.0f, 0.0f, 1.0f };

    R32V3 mPosition{ 0.0f, 0.0f, 0.0f };
    R32V3 mRotation{ 0.0f, 0.0f, 0.0f };
    R32V3 mScale{ 1.0f, 1.0f, 1.0f };
  };
}

#endif