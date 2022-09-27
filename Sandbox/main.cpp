#include <Redshift/Scene.h>

class Sandbox : public rsh::Scene
{
protected:
  rsh::U32 Tick(rsh::R32 deltaTime) override
  {
    return 0;
  }
};

DECLARE_SCENE_IMPL(Sandbox);