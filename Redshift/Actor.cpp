#include <Redshift/Actor.h>

namespace rsh
{
  Actor::Actor(std::string const& name)
    : mName{ name }
  {

  }

  void Actor::SetParent(Actor* parent)
  {
    mParent = parent;
  }
}