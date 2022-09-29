#ifndef RSH_GIZMOS_H
#define RSH_GIZMOS_H

#include <Redshift/Types.h>
#include <Redshift/Handle.h>
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
    void Render();

  public:
    static void DrawLine(R32V3 p0, R32V3 p1, R32V4 c);
    static void DrawBox(R32V3 p, R32V3 s, R32V4 c);

  private:
    U32 mVertexBufferSize{};
    U32 mElementBufferSize{};

    VertexGizmos* mBufferVertices{ new VertexGizmos[mVertexBufferSize] };
    U32* mBufferElements{ new U32[mElementBufferSize] };

    U32 mVao{ Vao::Create<VertexGizmos, U32>(mVertexBufferSize, mBufferVertices, mElementBufferSize, mBufferElements) };
    Handle<U32>& mShader{ World::GetShaderHandle("Gizmos") };

    U32 mOffsetVertex{};
    U32 mOffsetElement{};

    U32 mOffsetVertexPrev{};
    U32 mOffsetElementPrev{};
  };
}

#endif