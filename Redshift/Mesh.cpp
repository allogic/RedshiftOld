#include <Redshift/Mesh.h>

///////////////////////////////////////////////////////////
// Mesh implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  void Mesh::Destroy()
  {
    glDeleteBuffers(1, &mVbo);
    glDeleteBuffers(1, &mEbo);

    glDeleteVertexArrays(1, &mVao);
  }

  U32 Mesh::Valid() const
  {
    return mVao;
  }

  void Mesh::Bind() const
  {
    glBindVertexArray(mVao);
  }

  void Mesh::Render(RenderMode renderMode) const
  {
    glDrawElements(renderMode, mElementCount, GL_UNSIGNED_INT, NULL);
  }

  void Mesh::UnBind() const
  {
    glBindVertexArray(0);
  }
}