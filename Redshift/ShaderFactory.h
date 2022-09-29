#ifndef RSH_SHADER_FACTORY_H
#define RSH_SHADER_FACTORY_H

#include <Redshift/Types.h>

namespace rsh
{
  class ShaderFactory
  {
  public:
    static U32 Create();

    static void Destroy(U32 shader);
  };
}

#endif