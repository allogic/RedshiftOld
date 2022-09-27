#include <Redshift/World.h>
#include <Redshift/Scene.h>

///////////////////////////////////////////////////////////
// Sandbox implementation
///////////////////////////////////////////////////////////

class Sandbox : public rsh::Scene
{
public:
  Sandbox(rsh::World* world) : rsh::Scene(world) {}

protected:
  rsh::U32 Tick(rsh::R32 deltaTime) override
  {
    return 0;
  }
};

DECLARE_SCENE_IMPL(Sandbox);