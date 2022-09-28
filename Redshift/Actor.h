#ifndef RSH_ACTOR_H
#define RSH_ACTOR_H

#include <string>
#include <map>
#include <type_traits>

#include <Redshift/Types.h>
#include <Redshift/Component.h>

namespace rsh
{
  class Actor
  {
  public:
    Actor(std::string const& name);

  public:
    void SetParent(Actor* parent);

  public:
    template<typename C, typename ... Args>
    requires std::is_base_of_v<Component, C>
    C* AttachComponent(Args &&... args);

  private:
    std::string mName{};

    Actor* mParent{};

    std::map<U64, Component*> mComponents{};
  };

  template<typename C, typename ... Args>
  requires std::is_base_of_v<Component, C>
  C* Actor::AttachComponent(Args &&... args)
  {
    U64 hash{ typeid(C).hash_code() };
    auto const findIt{ mComponents.find(hash) };
    if (findIt == mComponents.end())
    {
      auto const [emplaceIt, inserted] { mComponents.emplace(hash, new C{ std::forward<Args>(args) ... }) };
      return (C*)emplaceIt->second;
    }
    return nullptr;
  }
}

#endif