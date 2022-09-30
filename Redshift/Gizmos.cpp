#include <Redshift/Gizmos.h>

///////////////////////////////////////////////////////////
// Externs
///////////////////////////////////////////////////////////

extern rsh::Gizmos sGizmos;

///////////////////////////////////////////////////////////
// Gizmos implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Gizmos::Gizmos(U32 vertexBufferSize, U32 elementBufferSize)
    : mVertexBufferSize{ vertexBufferSize }
    , mElementBufferSize{ elementBufferSize }
    , mBufferVertices{ new VertexGizmos[mVertexBufferSize] }
    , mBufferElements{ new U32[mElementBufferSize] }
    , mShader{ World::GetShader("Gizmos") }
  {

  }

  void Gizmos::Initialize()
  {
    mVao = Vao::Create<VertexGizmos, U32>(mVertexBufferSize, mBufferVertices, mElementBufferSize, mBufferElements);
  }
  void Gizmos::Render()
  {

  }

  void Gizmos::DrawLine(R32V3 p0, R32V3 p1, R32V4 c)
  {
    sGizmos.mBufferVertices[sGizmos.mOffsetVertex + 0].Position = p0;
    sGizmos.mBufferVertices[sGizmos.mOffsetVertex + 0].Color = c;

    sGizmos.mBufferVertices[sGizmos.mOffsetVertex + 1].Position = p1;
    sGizmos.mBufferVertices[sGizmos.mOffsetVertex + 1].Color = c;

    sGizmos.mBufferElements[sGizmos.mOffsetElement + 0] = sGizmos.mOffsetVertex + 0;
    sGizmos.mBufferElements[sGizmos.mOffsetElement + 1] = sGizmos.mOffsetVertex + 1;

    sGizmos.mOffsetVertex += 2;
    sGizmos.mOffsetElement += 2;
  }

  void Gizmos::DrawBox(R32V3 p, R32V3 s, R32V4 c)
  {

  }
}