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
    GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldPosition() + R32V3{ 2.0f, 0.0f, 0.0f }, R32V4{ 1.0f, 0.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldPosition() + R32V3{ 0.0f, 2.0f, 0.0f }, R32V4{ 0.0f, 1.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldPosition() + R32V3{ 0.0f, 0.0f, 2.0f }, R32V4{ 0.0f, 0.0f, 1.0f, 1.0f });

    GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldPosition() + GetTransform()->GetLocalRight() * 2.0f, R32V4{ 1.0f, 0.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldPosition() + GetTransform()->GetLocalUp() * 2.0f, R32V4{ 0.0f, 1.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldPosition() + GetTransform()->GetLocalFront() * 2.0f, R32V4{ 0.0f, 0.0f, 1.0f, 1.0f });

    if (GetParent())
    {
      GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetParent()->GetTransform()->GetWorldPosition(), R32V4{ 1.0f, 1.0f, 1.0f, 1.0f });
    }

    GetWorld()->DebugBox(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldScale(), R32V4{ 1.0f, 1.0f, 0.0f, 1.0f }, GetTransform()->GetLocalQuaternion());
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
    static R32 yaw{};
    yaw += timeDelta * 5.0f;

    //GetTransform()->SetWorldRotation(R32V3{ 0.0f, yaw, 0.0f });
    //GetTransform()->SetWorldPosition(GetTransform()->GetLocalQuaternion() * GetTransform()->GetLocalPosition());

    //RSH_LOG("%f, %f, %f\n", GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, GetTransform()->GetLocalPosition().z);
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
    mPlayer = GetWorld()->ActorCreate<Player>("Player");
    mPlayer->GetTransform()->SetWorldPosition(R32V3{ 0.0f, 15.0f, -15.0f });

    Box* root{ GetWorld()->ActorCreate<Box>("Root") };

    root->GetTransform()->SetWorldPosition(R32V3{ 1.0f, 0.0f, 0.0f });
    root->GetTransform()->SetWorldRotation(R32V3{ 0.0f, 45.0f, 0.0f });
    root->GetTransform()->SetWorldScale(R32V3{ 1.0f, 1.0f, 1.0f });

    root->GetTransform()->SetLocalPosition(R32V3{ 0.0f, 0.0f, 0.0f });
    root->GetTransform()->SetLocalRotation(R32V3{ 0.0f, 45.0f, 0.0f });
    root->GetTransform()->SetLocalScale(R32V3{ 1.0f, 1.0f, 1.0f });

    mBoxes.emplace_back(root);

    Box* boxPrev{ root };
    for (U32 i{}; i < 7; i++)
    {
      Box* box{ GetWorld()->ActorCreate<Box>(std::string{ "Box" } + std::to_string(i), boxPrev) };
      box->GetTransform()->SetLocalPosition(R32V3{ 1.0f, 1.0f, 0.0f });
      //box->GetTransform()->SetLocalRotation(R32V3{ 0.0f, 0.0f, 0.0f });
      box->GetTransform()->SetLocalScale(R32V3{ 1.0f, 1.0f, 1.0f }); 
      mBoxes.emplace_back(box);
      boxPrev = box;
    }

    GetWorld()->SetMainActor(mPlayer);
  }
  virtual ~Sandbox()
  {

  }

protected:
  void Update(R32 timeDelta) override
  {
    Scene::Update(timeDelta);

    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 2.0f, 0.0f, 0.0f }, R32V4{ 1.0f, 0.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 2.0f, 0.0f }, R32V4{ 0.0f, 1.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 0.0f, 2.0f }, R32V4{ 0.0f, 0.0f, 1.0f, 1.0f });

    static R32 x{};
    x += timeDelta;

    //for (U32 i{}; i < 7; i++)
    //{
    //  mBoxes[i + 1]->GetTransform()->SetLocalPosition(R32V3{ glm::sin(x), 1.0f, 0.0f });
    //}

    //mBoxes[0]->GetTransform()->SetWorldPosition(R32V3{ glm::sin(x), 0.0f, 0.0f });
  }

private:
  Player* mPlayer{};

  std::vector<Box*> mBoxes{};
};

DECLARE_SCENE_IMPL(Sandbox);