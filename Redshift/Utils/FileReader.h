#ifndef RSH_FILE_READER_H
#define RSH_FILE_READER_H

#include <string>
#include <vector>

#include <Redshift/Types.h>

///////////////////////////////////////////////////////////
// FileReader definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class FileReader
  {
  public:
    static U8 ReadBytes(std::vector<U8>& bytes, std::string const& file);
  };
}

#endif