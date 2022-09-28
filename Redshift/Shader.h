#ifndef RSH_SHADER_H
#define RSH_SHADER_H

#include <Redshift/Types.h>

namespace rsh
{
  class Shader
  {
  public:
    static U32 Create();

    static void Destroy(U32 shader);
  };
}

#endif