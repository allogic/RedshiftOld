#include <Redshift/Vao.h>

#include <Vendor/Glad/glad.h>

namespace rsh
{
  void Vao::Destroy(U32 vao)
  {
    glDeleteVertexArrays(1, &vao);
  }
}