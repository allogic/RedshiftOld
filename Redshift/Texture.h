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
    template<typename T>
    Texture& Create(T* pixelBuffer, U32 pixelBufferSize);

    void Destroy();
  };
}

///////////////////////////////////////////////////////////
// Texture implementation
///////////////////////////////////////////////////////////

template<typename T>
rsh::Texture& rsh::Texture::Create(T* pixelBuffer, U32 pixelBufferSize)
{
  return *this;
}

#endif