#ifndef RSH_IMPORTER_H
#define RSH_IMPORTER_H

#include <string>
#include <vector>

#include <Redshift/Types.h>
#include <Redshift/Vertex.h>

///////////////////////////////////////////////////////////
// Importer definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class Importer
  {
  public:
    static U8 LoadFbx(std::string const& fbxFile, std::vector<VertexPhysicalBased>& vertices, std::vector<U32>& elements);
  };
}

#endif