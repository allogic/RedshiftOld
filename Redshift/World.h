#ifndef RSH_WORLD_H
#define RSH_WORLD_H

#include <string>
#include <map>

#include <Redshift/Types.h>
#include <Redshift/Scene.h>

namespace rsh
{
  class World
  {
  public:
    static U32 CreateScene(std::string const& sceneName, std::string const& scenePath);
    static U32 DestroyScene(std::string const& sceneName);

  private:
    std::map<std::string, SceneProxy> mScenes{};
  };
}

#endif