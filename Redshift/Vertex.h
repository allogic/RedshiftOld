#ifndef RSH_VERTEX_H
#define RSH_VERTEX_H

#include <Redshift/Types.h>

namespace rsh
{
  enum VertexType
  {
    Gizmos,
    Pbr,
  };

  struct VertexGizmos
  {
    constexpr static VertexType Type{ Gizmos };

    R32V3 Position{};
    R32V4 Color{};
  };

  struct VertexPbr
  {
    constexpr static VertexType Type{ Pbr };

    R32V3 Position{};
    R32V3 Normal{};
    R32V2 Uv{};
    R32V4 Color{};
  };
}

#endif