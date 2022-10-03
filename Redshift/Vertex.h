#ifndef RSH_VERTEX_H
#define RSH_VERTEX_H

#include <Redshift/Types.h>

///////////////////////////////////////////////////////////
// Vertex definition
///////////////////////////////////////////////////////////

namespace rsh
{
  enum VertexType
  {
    eVertexTypeDebug,
    eVertexTypePbr,
  };

  struct VertexDebug
  {
    static constexpr VertexType Type{ eVertexTypeDebug };

    R32V3 Position{};
    R32V4 Color{};
  };

  struct VertexPbr
  {
    static constexpr VertexType Type{ eVertexTypePbr };

    R32V3 Position{};
    R32V3 Normal{};
    R32V2 Uv{};
    R32V4 Color{};
  };
}

#endif