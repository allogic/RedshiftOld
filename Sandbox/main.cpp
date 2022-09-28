#include <Redshift/World.h>
#include <Redshift/Scene.h>
#include <Redshift/Debug.h>

///////////////////////////////////////////////////////////
// Sandbox implementation
///////////////////////////////////////////////////////////

class Sandbox : public rsh::Scene
{
public:
  Sandbox(rsh::World* world) : rsh::Scene(world)
  {
    RSH_LOG("Created\n");
  }
  virtual ~Sandbox()
  {
    RSH_LOG("Destroyed\n");
  }

protected:
  rsh::U32 Tick(rsh::R32 deltaTime) override
  {
    return 0;
  }
};

DECLARE_SCENE_IMPL(Sandbox);