#ifndef RSH_MODULE_H
#define RSH_MODULE_H

#include <Redshift/Types.h>
#include <Redshift/Platform.h>

///////////////////////////////////////////////////////////
// Module definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class Module
  {
  public:
    Module(World* world);
    virtual ~Module();

  public:
    virtual void Update(R32 timeDelta);

  public:
    inline World* GetWorld() const { return mWorld; }

  private:
    World* mWorld{};
  };

  using ModuleCreateProc = Module* (*)(World* world);
  using ModuleDestroyProc = void (*)(Module* instance);

  struct ModuleProxy
  {
    void* InstanceNative{};
    Module* InstanceModule{};
    ModuleCreateProc CreateProc{};
    ModuleDestroyProc DestroyProc{};
  };
}

///////////////////////////////////////////////////////////
// Module interface
///////////////////////////////////////////////////////////

extern "C"
{
#if defined(OS_WINDOWS)
  __declspec(dllexport) rsh::Module* CreateModule(rsh::World* world);
  __declspec(dllexport) void DestroyModule(rsh::Module* instance);
#elif defined(OS_LINUX)
  rsh::Module* CreateModule(rsh::World* world);
  void DestroyModule(rsh::Module* instance);
#else
  #error "Platform not supported!"
#endif
}

#define DECLARE_MODULE_IMPL(MODULE) \
rsh::Module* CreateModule(rsh::World* world) { return new MODULE{ world }; } \
void DestroyModule(rsh::Module* instance) { delete instance; }

#endif