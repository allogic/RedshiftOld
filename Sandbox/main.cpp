#include <string>
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

    if (GetParent())
    {
      mWorld->DebugLine(mTransform->GetWorldPosition(), GetParent()->GetTransform()->GetWorldPosition(), R32V4{ 1.0f, 1.0f, 1.0f, 1.0f });
    }

    mWorld->DebugBox(mTransform->GetWorldPosition(), mTransform->GetWorldScale(), R32V4{ 1.0f, 1.0f, 0.0f, 1.0f }, mTransform->GetWorldRotation());
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
    mPlayer->GetTransform()->SetWorldPosition(R32V3{ 0.0f, 0.0f, -25.0f });

    Box* boxPrev{};
    for (U32 i{}; i < 8; i++)
    {
      Box* box{ mWorld->ActorCreate<Box>(std::string{ "Box" } + std::to_string(i), boxPrev) };
      box->GetTransform()->SetLocalPosition(R32V3{ 0.0f, 1.0f, 0.0f });
      box->GetTransform()->SetLocalRotation(R32V3{ 0.0f, 0.0f, 0.0f });
      box->GetTransform()->SetLocalScale(R32V3{ 1.0f, 1.0f, 1.0f }); 
      mBoxes.emplace_back(box);
      boxPrev = box;
    }

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
    mBoxes[0]->GetTransform()->SetWorldPosition(R32V3{ glm::sin((x += timeDelta) * 10.0f), -4.0f + glm::cos((y += timeDelta) * 10.0f), 5.0f });
  }

private:
  Player* mPlayer{};

  std::vector<Box*> mBoxes{};
};

DECLARE_SCENE_IMPL(Sandbox);