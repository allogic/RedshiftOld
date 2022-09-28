#include <Redshift/Components/Transform.h>

namespace rsh
{
  Transform::Transform(R32V3 position, R32V3 rotation, R32V3 scale)
    : Component{}
    , mPosition{ position }
    , mRotation{ rotation }
    , mScale{ scale }
  {

  }
}