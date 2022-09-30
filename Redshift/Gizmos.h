#ifndef RSH_GIZMOS_H
#define RSH_GIZMOS_H

#include <Redshift/Types.h>
#include <Redshift/World.h>
#include <Redshift/Vao.h>
#include <Redshift/Vertex.h>

namespace rsh
{
  class Gizmos
  {
  public:
    Gizmos(U32 vertexBufferSize, U32 elementBufferSize);

  public:
    void Initialize();
    void Render();

  public:
    static void DrawLine(R32V3 p0, R32V3 p1, R32V4 c);
    static void DrawBox(R32V3 p, R32V3 s, R32V4 c);

  private:
    U32 mVertexBufferSize{};
    U32 mElementBufferSize{};

    VertexGizmos* mBufferVertices{};
    U32* mBufferElements{};

    U32 mVao{};
    U32& mShader;

    U32 mOffsetVertex{};
    U32 mOffsetElement{};

    U32 mOffsetVertexPrev{};
    U32 mOffsetElementPrev{};
  };
}

#endif