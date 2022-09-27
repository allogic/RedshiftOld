#ifndef RSH_HOTLOADER_H
#define RSH_HOTLOADER_H

#include <string>

namespace rsh
{
  class HotLoader
  {
  public:
    HotLoader(std::string const& streamingPath);

  private:
    std::string mStreamingPath{};
  };
}

#endif