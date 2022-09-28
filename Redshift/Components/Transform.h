#ifndef RSH_TRANSFORM_H
#define RSH_TRANSFORM_H

#include <Redshift/Types.h>
#include <Redshift/Component.h>

namespace rsh
{
  class Transform : public Component
  {
  public:
    Transform(R32V3 position, R32V3 rotation, R32V3 scale);

  private:
    R32V3 mPosition;
    R32V3 mRotation;
    R32V3 mScale;
  };
}

#endif