#ifndef RSH_COMPONENT_H
#define RSH_COMPONENT_H

///////////////////////////////////////////////////////////
// Component definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class Component
  {
  public:
    Component(World* world);

  protected:
    World* mWorld{};
  };
}

#endif