#ifndef RSH_SCENE_H
#define RSH_SCENE_H

#include <string>
#include <map>
#include <type_traits>

#include <Redshift/Types.h>
#include <Redshift/Platform.h>
#include <Redshift/Actor.h>

namespace rsh
{
  class World;

  class Scene
  {
  public:
    Scene(World* world);
    virtual ~Scene();

  public:
    virtual U32 Tick(R32 deltaTime) = 0;

  public:
    template<typename A>
    requires std::is_base_of_v<Actor, A>
    A* CreateActor(std::string const& actorName, Actor* parent = nullptr);

    void DestroyActor(Actor* actor);

  private:
    World* mWorld{};

    std::map<std::string, Actor*> mActors{};
  };

  template<typename A>
  requires std::is_base_of_v<Actor, A>
  A* Scene::CreateActor(std::string const& actorName, Actor* parent)
  {
    auto const findIt{ mActors.find(actorName) };
    if (findIt == mActors.end())
    {
      auto const [emplaceIt, inserted] { mActors.emplace(actorName, new A{ actorName }) };
      if (parent)
      {
        emplaceIt->second->SetParent(parent);
      }
      return (A*)emplaceIt->second;
    }
    return nullptr;
  }

  using SceneCreateProc = Scene* (*)(World* world);
  using SceneDestroyProc = void (*)(Scene* scene);

  struct SceneProxy
  {
    void* Instance{};
    Scene* Scene{};
    SceneCreateProc CreateProc{};
    SceneDestroyProc DestroyProc{};
  };
}

extern "C"
{
#if defined(OS_WINDOWS)
  __declspec(dllexport) rsh::Scene* CreateScene(rsh::World* world);
  __declspec(dllexport) void DestroyScene(rsh::Scene* scene);
#elif defined(OS_LINUX)
  rsh::Scene* CreateScene(rsh::World* world);
  void DestroyScene(rsh::Scene* scene);
#else
  #error "Platform not supported!"
#endif
}

#define DECLARE_SCENE_IMPL(SCENE) \
rsh::Scene* CreateScene(rsh::World* world) { return new SCENE{ world }; } \
void DestroyScene(rsh::Scene* scene) { delete scene; }

#endif