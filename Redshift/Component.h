#ifndef RSH_COMPONENT_H
#define RSH_COMPONENT_H

///////////////////////////////////////////////////////////
// Component definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;
  class Actor;

  class Component
  {
  public:
    Component(World* world, Actor* actor);

  protected:
    World* mWorld{};
    Actor* mActor{};
  };
}

#endif