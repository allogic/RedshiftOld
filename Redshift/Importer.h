#ifndef RSH_IMPORTER_H
#define RSH_IMPORTER_H

#include <string>
#include <vector>

#include <Redshift/Types.h>
#include <Redshift/Vertex.h>
#include <Redshift/Platform.h>

#if defined(OS_WINDOWS)
  #include <filesystem>
#elif defined(OS_LINUX)
  #include <experimental/filesystem>
  namespace std
  {
    namespace filesystem = experimental::filesystem;
  }
#else
  #error "Platform not supported!"
#endif

///////////////////////////////////////////////////////////
// Importer definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class Importer
  {
  public:
    static U8 LoadFbx(World* world, std::filesystem::path const& fbxFile);
  };
}

#endif