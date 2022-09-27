#ifndef RSH_SCENE_H
#define RSH_SCENE_H

#include <Redshift/Types.h>
#include <Redshift/Platform.h>

namespace rsh
{
  class Scene
  {
  public:
    typedef Scene* (*CreateProc)();
    typedef void (*DestroyProc)();

  public:
    Scene() = default;
    virtual ~Scene() = default;

  public:
    virtual U32 Tick(R32 deltaTime) = 0;
  };
}

extern "C"
{
#if defined(OS_WINDOWS)
  __declspec(dllexport) rsh::Scene* CreateScene();
  __declspec(dllexport) void DestroyScene(rsh::Scene* scene);
#elif defined(OS_UNIX)
  #warning "Platform not implemented!"
#else
  #error "Platform not supported!"
#endif
}

#define DECLARE_SCENE_IMPL(SCENE)                       \
rsh::Scene* CreateScene() { return new SCENE; }         \
void DestroyModule(rsh::Scene* scene) { delete scene; }

#endif