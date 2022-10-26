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
    eVertexTypePhysicalBased,
  };

#pragma pack(push, 1)
  struct VertexDebug
  {
    static constexpr VertexType Type{ eVertexTypeDebug };

    R32V3 Position{};
    R32V4 Color{};
  };
  struct VertexPhysicalBased
  {
    static constexpr VertexType Type{ eVertexTypePhysicalBased };

    R32V3 Position{};
    R32V3 Normal{};
    R32V2 Uv{};
    R32V4 Color{};
    R32V3 Tangent{};
  };
#pragma pack(pop)
}

#endif