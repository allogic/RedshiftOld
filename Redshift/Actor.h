#ifndef RSH_ACTOR_H
#define RSH_ACTOR_H

#include <string>
#include <vector>
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

    /*
    * Global specific
    */

  public:
    inline World* GetWorld() const { return mWorld; }
    inline std::string const& GetName() const { return mName; }

  private:
    World* mWorld{};
    std::string const mName{};

    /*
    * Runtime specific
    */

  public:
    virtual void Update(R32 timeDelta);

    /*
    * Parenting
    */

  public:
    inline Actor* GetParent() const { return mParent; }
    inline void SetParent(Actor* parent) { mParent = parent; }

    inline std::vector<Actor*> const& GetChildren() const { return mChildren; }
    inline U8 HasChildren() const { return mChildren.size() > 0; }
    inline void AddChild(Actor* child) { mChildren.emplace_back(child); }
    inline void RemoveChild(Actor* child) { mChildren.erase(std::find(mChildren.begin(), mChildren.end(), child)); }

  private:
    Actor* mParent{};
    std::vector<Actor*> mChildren{};

    /*
    * Components
    */

  public:
    template<typename C, typename ... Args>
    C* ComponentAttach(Args&& ... args);
    template<typename C>
    C* GetComponent();

  public:
    inline std::map<U64, Component*> const& GetComponents() const { return mComponents; }

  private:
    std::map<U64, Component*> mComponents{};

    /*
    * Default components
    */

  public:
    inline Transform* GetTransform() const { return mTransform; }

  private:
    Transform* mTransform{};
  };
}

///////////////////////////////////////////////////////////
// Actor implementation
///////////////////////////////////////////////////////////

template<typename C, typename ... Args>
C* rsh::Actor::ComponentAttach(Args&& ... args)
{
  U64 hash{ typeid(C).hash_code() };
  auto const findIt{ mComponents.find(hash) };
  if (findIt == mComponents.end())
  {
    auto const [emplaceIt, inserted] { mComponents.emplace(hash, new C{ mWorld, this, std::forward<Args>(args) ... }) };
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