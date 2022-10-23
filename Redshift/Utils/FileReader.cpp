#include <fstream>

#include <Redshift/Utils/FileReader.h>

///////////////////////////////////////////////////////////
// FileReader implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  U8 FileReader::ReadBytes(std::vector<U8>& bytes, std::string const& file)
  {
    std::ifstream stream{ file, std::ios::binary | std::ios::ate };

    if (stream.is_open())
    {
      U64 size{ (U64)stream.tellg() };
      
      bytes.resize(size);

      stream.seekg(std::ios::beg);
      stream.read((char*)&bytes[0], size);
      stream.close();

      return 1;
    }
    
    return 0;
  }
}