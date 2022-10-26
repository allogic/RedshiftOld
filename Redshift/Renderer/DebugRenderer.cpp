#include <Redshift/World.h>

#include <Redshift/Components/Camera.h>

#include <Redshift/Renderer/DebugRenderer.h>

///////////////////////////////////////////////////////////
// DebugRenderer implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  DebugRenderer::DebugRenderer(World* world)
    : mWorld{ world }
    , mMesh{ mWorld->GetMesh("Debug").Create<VertexDebug, U32>(mVertexBuffer, mVertexBufferSize, mElementBuffer, mElementBufferSize) }
    , mShader{ mWorld->GetShader("Debug") }
  {

  }

  void DebugRenderer::Render()
  {
    Camera* camera{ mWorld->GetMainCamera() };

    if (camera)
    {
      if (mShader.Valid())
      {
        mShader.Bind();

        mShader.SetUniformR32M4("UniformProjectionMatrix", camera->GetProjectionMatrix());
        mShader.SetUniformR32M4("UniformViewMatrix", camera->GetViewMatrix());

        mMesh.Bind();

        mMesh.UploadVertices(mVertexBuffer, mVertexBufferSize);
        mMesh.UploadElements(mElementBuffer, mElementBufferSize);

        mMesh.Render(Mesh::eRenderModeLines);

        mMesh.UnBind();
        mShader.UnBind();
      }
    }

    if (mVertexBufferSize)
    {
      std::memset(mVertexBuffer, 0, mVertexBufferSize);
    }

    if (mElementBufferSize)
    {
      std::memset(mElementBuffer, 0, mElementBufferSize);
    }

    mVertexOffset = 0;
    mElementOffset = 0;
  }

  void DebugRenderer::DebugLine(R32V3 p0, R32V3 p1, R32V4 c)
  {
    mVertexBuffer[mVertexOffset + 0].Position = p0;
    mVertexBuffer[mVertexOffset + 1].Position = p1;

    mVertexBuffer[mVertexOffset + 0].Color = c;
    mVertexBuffer[mVertexOffset + 1].Color = c;

    mElementBuffer[mElementOffset + 0] = mVertexOffset + 0;
    mElementBuffer[mElementOffset + 1] = mVertexOffset + 1;

    mVertexOffset += 2;
    mElementOffset += 2;
  }

  void DebugRenderer::DebugBox(R32V3 p, R32V3 s, R32V4 c, R32Q r)
  {
    R32V3 h{ s / 2.0f };

    mVertexBuffer[mVertexOffset + 0].Position = p + r * R32V3{ -h.x, -h.y, -h.z };
    mVertexBuffer[mVertexOffset + 1].Position = p + r * R32V3{ h.x, -h.y, -h.z };
    mVertexBuffer[mVertexOffset + 2].Position = p + r * R32V3{ -h.x, h.y, -h.z };
    mVertexBuffer[mVertexOffset + 3].Position = p + r * R32V3{ h.x, h.y, -h.z };

    mVertexBuffer[mVertexOffset + 4].Position = p + r * R32V3{ -h.x, -h.y, h.z };
    mVertexBuffer[mVertexOffset + 5].Position = p + r * R32V3{ h.x, -h.y, h.z };
    mVertexBuffer[mVertexOffset + 6].Position = p + r * R32V3{ -h.x, h.y, h.z };
    mVertexBuffer[mVertexOffset + 7].Position = p + r * R32V3{ h.x, h.y, h.z };

    mVertexBuffer[mVertexOffset + 0].Color = c;
    mVertexBuffer[mVertexOffset + 1].Color = c;
    mVertexBuffer[mVertexOffset + 2].Color = c;
    mVertexBuffer[mVertexOffset + 3].Color = c;

    mVertexBuffer[mVertexOffset + 4].Color = c;
    mVertexBuffer[mVertexOffset + 5].Color = c;
    mVertexBuffer[mVertexOffset + 6].Color = c;
    mVertexBuffer[mVertexOffset + 7].Color = c;

    mElementBuffer[mElementOffset + 0] = mVertexOffset + 0;
    mElementBuffer[mElementOffset + 1] = mVertexOffset + 1;
    mElementBuffer[mElementOffset + 2] = mVertexOffset + 0;
    mElementBuffer[mElementOffset + 3] = mVertexOffset + 2;
    mElementBuffer[mElementOffset + 4] = mVertexOffset + 2;
    mElementBuffer[mElementOffset + 5] = mVertexOffset + 3;

    mElementBuffer[mElementOffset + 6] = mVertexOffset + 3;
    mElementBuffer[mElementOffset + 7] = mVertexOffset + 1;
    mElementBuffer[mElementOffset + 8] = mVertexOffset + 4;
    mElementBuffer[mElementOffset + 9] = mVertexOffset + 5;
    mElementBuffer[mElementOffset + 10] = mVertexOffset + 4;
    mElementBuffer[mElementOffset + 11] = mVertexOffset + 6;

    mElementBuffer[mElementOffset + 12] = mVertexOffset + 6;
    mElementBuffer[mElementOffset + 13] = mVertexOffset + 7;
    mElementBuffer[mElementOffset + 14] = mVertexOffset + 7;
    mElementBuffer[mElementOffset + 15] = mVertexOffset + 5;
    mElementBuffer[mElementOffset + 16] = mVertexOffset + 0;
    mElementBuffer[mElementOffset + 17] = mVertexOffset + 4;

    mElementBuffer[mElementOffset + 18] = mVertexOffset + 1;
    mElementBuffer[mElementOffset + 19] = mVertexOffset + 5;
    mElementBuffer[mElementOffset + 20] = mVertexOffset + 2;
    mElementBuffer[mElementOffset + 21] = mVertexOffset + 6;
    mElementBuffer[mElementOffset + 22] = mVertexOffset + 3;
    mElementBuffer[mElementOffset + 23] = mVertexOffset + 7;

    mVertexOffset += 8;
    mElementOffset += 24;
  }
}