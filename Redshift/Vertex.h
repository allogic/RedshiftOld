#ifndef RSH_VERTEX_H
#define RSH_VERTEX_H

namespace rsh
{
  struct VertexGizmos
  {
    R32V3 Position{};
    R32V4 Color{};
  };

  struct VertexPbr
  {
    R32V3 Position{};
    R32V3 Normal{};
    R32V2 Uv{};
    R32V4 Color{};
  };
}

#endif