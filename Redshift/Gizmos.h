#ifndef RSH_GIZMOS_H
#define RSH_GIZMOS_H

#include <Redshift/Types.h>

namespace rsh
{
  class Gizmos
  {
  public:
    Gizmos();

  public:
    static void DrawLine(R32V3 p0, R32V3 p1, R32V3 c);
    static void DrawBox(R32V3 p, R32V3 s, R32V3 c);
  };
}

#endif