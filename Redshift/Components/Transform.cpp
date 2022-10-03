#include <Redshift/Components/Transform.h>

///////////////////////////////////////////////////////////
// Transform implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Transform::Transform(World* world)
    : Component{ world }
  {

  }

  Transform::Transform(World* world, R32V3 position, R32V3 rotation, R32V3 scale)
    : Component{ world }
    , mPosition{ position }
    , mRotation{ rotation }
    , mScale{ scale }
  {

  }

  R32M4 Transform::GetModelMatrix()
  {
    return {};
  }
}