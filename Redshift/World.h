#ifndef RSH_WORLD_H
#define RSH_WORLD_H

#include <string>
#include <map>

#include <Redshift/Types.h>
#include <Redshift/Scene.h>
#include <Redshift/Actor.h>
#include <Redshift/Handle.h>

namespace rsh
{
  class World
  {
  public:
    static U32 CreateScene(std::string const& sceneName, std::string const& sceneFile);
    static U32 DestroyScene(std::string const& sceneName);

  public:
    template<typename A>
    static A* CreateActor(World* world, std::string const& actorName, Actor* parent = nullptr);
    static void DestroyActor(World* world, Actor* actor);

  public:
    static U32 CreateShader(std::string const& shaderName, std::string const& shaderFile);
    static U32 DestroyShader(std::string const& shaderName);

  public:
    static Handle<U32>& GetShaderHandle(std::string const& shaderName);

  private:
    std::map<std::string, SceneProxy> mScenes{};
    std::map<std::string, Actor*> mActors{};

  private:
    std::map<std::string, Handle<U32>> mShaders{};
  };

  template<typename A>
  A* World::CreateActor(World* world, std::string const& actorName, Actor* parent)
  {
    auto const findIt{ world->mActors.find(actorName) };
    if (findIt == world->mActors.end())
    {
      auto const [emplaceIt, inserted] { world->mActors.emplace(actorName, new A{ actorName }) };
      if (parent)
      {
        emplaceIt->second->SetParent(parent);
      }
      return (A*)emplaceIt->second;
    }
    return (A*)findIt->second;
  }
}

#endif