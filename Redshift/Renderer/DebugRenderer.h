#ifndef RSH_DEBUG_RENDERER_H
#define RSH_DEBUG_RENDERER_H

#include <Redshift/Types.h>
#include <Redshift/Shader.h>
#include <Redshift/Mesh.h>
#include <Redshift/Vertex.h>

///////////////////////////////////////////////////////////
// DebugRenderer definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class DebugRenderer
  {
  public:
    DebugRenderer(World* world);

  public:
    void Render();

  public:
    void DebugLine(R32V3 p0, R32V3 p1, R32V4 c);
    void DebugBox(R32V3 p, R32V3 s, R32V4 c, R32Q r = R32Q{});

  private:
    World* mWorld{};

    U32 mVertexBufferSize{ 65535 * 3 };
    U32 mElementBufferSize{ mVertexBufferSize * 2 };

    VertexDebug* mVertexBuffer{ new VertexDebug[mVertexBufferSize] };
    U32* mElementBuffer{ new U32[mElementBufferSize] };

    Mesh& mMesh;
    Shader& mShader;

    U32 mVertexOffset{};
    U32 mElementOffset{};
  };
}

#endif