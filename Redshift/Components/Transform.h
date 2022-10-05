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
    void ApplyTransform(Transform* other);

  public:
    inline R32V3 const& GetLocalRight() const { return mLocalRight; }
    inline R32V3 const& GetLocalUp() const { return mLocalUp; }
    inline R32V3 const& GetLocalFront() const { return mLocalFront; }

  public:
    R32V3 GetWorldPosition() const;
    R32V3 GetWorldRotation() const;
    R32Q GetWorldQuaternion() const;
    R32V3 GetWorldScale() const;

    R32V3 GetLocalPosition() const;
    R32V3 GetLocalRotation() const;
    R32Q GetLocalQuaternion() const;
    R32V3 GetLocalScale() const;

  public:
    void SetWorldPosition(R32V3 worldPosition);
    void SetWorldRotation(R32V3 worldRotation);
    void SetWorldScale(R32V3 worldScale);

    void SetLocalPosition(R32V3 localPosition);
    void SetLocalRotation(R32V3 localRotation);
    void SetLocalScale(R32V3 localScale);

  public:
    R32M4 GetModelMatrix();

  private:
    U32 mDirty{};

    R32V3 mLocalRight{ 1.0f, 0.0f, 0.0f };
    R32V3 mLocalUp{ 0.0f, 1.0f, 0.0f };
    R32V3 mLocalFront{ 0.0f, 0.0f, 1.0f };

    R32V3 mWorldPosition{ 0.0f, 0.0f, 0.0f };
    R32V3 mWorldRotation{ 0.0f, 0.0f, 0.0f };
    R32V3 mWorldScale{ 1.0f, 1.0f, 1.0f };

    R32V3 mLocalPosition{ 0.0f, 0.0f, 0.0f };
    R32V3 mLocalRotation{ 0.0f, 0.0f, 0.0f };
    R32V3 mLocalScale{ 1.0f, 1.0f, 1.0f };
  };
}

#endif