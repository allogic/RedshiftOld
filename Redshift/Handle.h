#ifndef RSH_HANDLE_H
#define RSH_HANDLE_H

#include <Redshift/Types.h>

namespace rsh
{
  template<typename T>
  class Handle
  {
  public:
    Handle();

  private:
    T* mReference{};
    U32 mDirty{};
  };

  template<typename T>
  Handle<T>::Handle()
  {

  }
}

#endif