#include <Redshift/Mesh.h>

///////////////////////////////////////////////////////////
// Mesh implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  U32 Mesh::Valid()
  {
    return mVao;
  }

  void Mesh::Bind()
  {
    glBindVertexArray(mVao);
  }

  void Mesh::Render()
  {
    glDrawElements(GL_LINES, mElementCount, GL_UNSIGNED_INT, NULL);
  }

  void Mesh::UnBind()
  {
    glBindVertexArray(0);
  }

  void Mesh::Destroy()
  {
    glDeleteBuffers(1, &mVbo);
    glDeleteBuffers(1, &mEbo);

    glDeleteVertexArrays(1, &mVao);
  }
}