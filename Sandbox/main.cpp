#include <vector>

#include <Redshift/World.h>
#include <Redshift/Scene.h>
#include <Redshift/Debug.h>
#include <Redshift/Actor.h>
#include <Redshift/Event.h>

#include <Redshift/Components/Transform.h>
#include <Redshift/Components/Camera.h>

using namespace rsh;

///////////////////////////////////////////////////////////
// Custom actors
///////////////////////////////////////////////////////////

class Box : public Actor
{
public:
  Box(World* world, std::string const& name) : Actor{ world, name }
  {

  }

public:
  void Update(R32 timeDelta) override
  {
    mWorld->DebugLine(mTransform->GetWorldPosition(), mTransform->GetWorldPosition() + R32V3{ 1.0f, 0.0f, 0.0f }, R32V4{ 1.0f, 0.0f, 0.0f, 1.0f });
    mWorld->DebugLine(mTransform->GetWorldPosition(), mTransform->GetWorldPosition() + R32V3{ 0.0f, 1.0f, 0.0f }, R32V4{ 0.0f, 1.0f, 0.0f, 1.0f });
    mWorld->DebugLine(mTransform->GetWorldPosition(), mTransform->GetWorldPosition() + R32V3{ 0.0f, 0.0f, 1.0f }, R32V4{ 0.0f, 0.0f, 1.0f, 1.0f });

    mWorld->DebugBox(mTransform->GetWorldPosition(), mTransform->GetWorldScale(), R32V4{ 1.0f, 1.0f, 0.0f, 1.0f }, mTransform->GetLocalRotation());
  }
};

class Player : public Actor
{
public:
  Player(World* world, std::string const& name) : Actor{ world, name }
  {

  }

public:
  void Update(R32 timeDelta) override
  {
    
  }

private:
  Camera* mCamera{ ComponentAttach<Camera>() };
};

///////////////////////////////////////////////////////////
// Sandbox implementation
///////////////////////////////////////////////////////////

class Sandbox : public Scene
{
public:
  Sandbox(World* world) : Scene{ world }
  {
    mPlayer = mWorld->ActorCreate<Player>("Player");
    mPlayer->GetComponent<Transform>()->SetLocalPosition(R32V3{ 0.0f, 0.0f, -10.0f });

    mRoot = mWorld->ActorCreate<Box>("Root");
    mRoot->GetComponent<Transform>()->SetLocalRotation(R32V3{ 0.0f, 0.0f, 45.0f });
    mRoot->GetComponent<Transform>()->SetLocalScale(R32V3{ 1.0f, 0.5f, 1.0f });

    mChildLeft = mWorld->ActorCreate<Box>("ChildLeft", mRoot);
    mChildLeft->GetComponent<Transform>()->SetLocalPosition(R32V3{ -5.0f, 3.0f, 5.0f });
    mChildLeft->GetComponent<Transform>()->SetLocalRotation(R32V3{ 0.0f, 0.0f, 45.0f });
    mChildLeft->GetComponent<Transform>()->SetLocalScale(R32V3{ 3.0f, 3.0f, 3.0f });

    mChildRight = mWorld->ActorCreate<Box>("ChildRight", mRoot);
    mChildRight->GetComponent<Transform>()->SetLocalPosition(R32V3{ 5.0f, 3.0f, 5.0f });
    mChildRight->GetComponent<Transform>()->SetLocalRotation(R32V3{ 0.0f, 0.0f, -45.0f });
    mChildRight->GetComponent<Transform>()->SetLocalScale(R32V3{ 3.0f, 3.0f, 3.0f });

    mWorld->SetMainActor(mPlayer);
  }
  virtual ~Sandbox()
  {

  }

protected:
  void Update(R32 timeDelta) override
  {
    Scene::Update(timeDelta);

    mWorld->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 1.0f, 0.0f, 0.0f }, R32V4{ 1.0f, 0.0f, 0.0f, 1.0f });
    mWorld->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 1.0f, 0.0f }, R32V4{ 0.0f, 1.0f, 0.0f, 1.0f });
    mWorld->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 0.0f, 1.0f }, R32V4{ 0.0f, 0.0f, 1.0f, 1.0f });

    static R32 x{};
    static R32 y{};
    mRoot->GetComponent<Transform>()->SetLocalPosition(R32V3{ glm::sin(x += 0.001f), glm::cos(y += 0.001f), 5.0f });
  }

private:
  Player* mPlayer{};

  Box* mRoot{};
  Box* mChildLeft{};
  Box* mChildRight{};
};

DECLARE_SCENE_IMPL(Sandbox);