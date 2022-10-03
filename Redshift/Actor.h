#ifndef RSH_ACTOR_H
#define RSH_ACTOR_H

#include <string>
#include <map>
#include <typeinfo>

#include <Redshift/Types.h>
#include <Redshift/Component.h>

///////////////////////////////////////////////////////////
// Actor definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;
  class Transform;

  class Actor
  {
    /*
    * Constructor/Destructor
    */

  public:
    Actor(World* world, std::string const& name);
    virtual ~Actor();

  public:
    inline std::string const& GetName() const { return mName; }

  protected:
    World* mWorld{};

    std::string const mName{};

    /*
    * Editor specific
    */

  public:
    virtual void Update(R32 timeDelta);

    /*
    * Transformations
    */

  public:
    R32V3 GetWorldCoordinates();

    /*
    * Parenting
    */

  public:
    inline Actor* GetParent() const { return mParent; }
    inline void SetParent(Actor* parent) { mParent = parent; }

  private:
    Actor* mParent{};

    /*
    * Components
    */

  public:
    template<typename C, typename ... Args>
    C* ComponentAttach(Args &&... args);
    template<typename C>
    C* GetComponent();

  private:
    std::map<U64, Component*> mComponents{};

    /*
    * Default components
    */

  protected:
    Transform* mTransform{};
  };
}

///////////////////////////////////////////////////////////
// Inline actor implementation
///////////////////////////////////////////////////////////

template<typename C, typename ... Args>
C* rsh::Actor::ComponentAttach(Args &&... args)
{
  U64 hash{ typeid(C).hash_code() };
  auto const findIt{ mComponents.find(hash) };
  if (findIt == mComponents.end())
  {
    auto const [emplaceIt, inserted] { mComponents.emplace(hash, new C{ mWorld, std::forward<Args>(args) ... }) };
    return (C*)emplaceIt->second;
  }
  return (C*)findIt->second;
}

template<typename C>
C* rsh::Actor::GetComponent()
{
  return (C*)mComponents[typeid(C).hash_code()];
}

#endif