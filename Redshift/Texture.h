#ifndef RSH_TEXTURE_H
#define RSH_TEXTURE_H

#include <Redshift/Types.h>

///////////////////////////////////////////////////////////
// Texture definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class Texture
  {
  public:
    Texture& Create(U8* pixelBuffer, U32 pixelBufferSize);

    void Destroy();
  };
}

#endif