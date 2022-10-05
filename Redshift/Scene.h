#ifndef RSH_SCENE_H
#define RSH_SCENE_H

#include <Redshift/Types.h>
#include <Redshift/Platform.h>

///////////////////////////////////////////////////////////
// Scene definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class Scene
  {
  public:
    Scene(World* world);
    virtual ~Scene();

  public:
    virtual void Update(R32 timeDelta);

  public:
    inline World* GetWorld() const { return mWorld; }

  private:
    World* mWorld{};
  };

  using SceneCreateProc = Scene* (*)(World* world);
  using SceneDestroyProc = void (*)(Scene* scene);

  struct SceneProxy
  {
    void* InstanceModule{};
    Scene* InstanceScene{};
    SceneCreateProc CreateProc{};
    SceneDestroyProc DestroyProc{};
  };
}

///////////////////////////////////////////////////////////
// Scene interface
///////////////////////////////////////////////////////////

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