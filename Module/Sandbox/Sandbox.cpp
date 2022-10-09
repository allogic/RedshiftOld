#include <string>
#include <vector>

#include <Redshift/Module.h>
#include <Redshift/World.h>
#include <Redshift/Debug.h>
#include <Redshift/Actor.h>

#include <Redshift/Components/Transform.h>
#include <Redshift/Components/Camera.h>

#include <Vendor/ImGui/imgui.h>

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
    GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldPosition() + GetTransform()->GetWorldRight() * 2.0f, R32V4{1.0f, 0.0f, 0.0f, 1.0f});
    GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldPosition() + GetTransform()->GetWorldUp() * 2.0f, R32V4{ 0.0f, 1.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldPosition() + GetTransform()->GetWorldFront() * 2.0f, R32V4{ 0.0f, 0.0f, 1.0f, 1.0f });

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
    
  }

private:
  Camera* mCamera{ ComponentAttach<Camera>() };
};

///////////////////////////////////////////////////////////
// Sandbox implementation
///////////////////////////////////////////////////////////

class Sandbox : public Module
{
public:
  Sandbox(World* world) : Module{ world }
  {
    mPlayer = GetWorld()->ActorCreate<Player>("GamePlayer");

    mPlayer->GetTransform()->SetWorldPosition(R32V3{ 0.0f, 0.0f, -15.0f });

    Box* root{ GetWorld()->ActorCreate<Box>("Root") };

    root->GetTransform()->SetWorldPosition(R32V3{ 3.0f, 0.0f, 0.0f });
    //root->GetTransform()->SetWorldRotation(R32V3{ 0.0f, 45.0f, 0.0f });
    root->GetTransform()->SetWorldScale(R32V3{ 1.0f, 1.0f, 1.0f });

    root->GetTransform()->SetLocalPosition(R32V3{ 0.0f, 0.0f, 0.0f });
    //root->GetTransform()->SetLocalRotation(R32V3{ 0.0f, 45.0f, 0.0f });
    root->GetTransform()->SetLocalScale(R32V3{ 1.0f, 1.0f, 1.0f });

    mBoxes.emplace_back(root);

    Box* boxPrev{ root };
    for (U32 i{}; i < 7; i++)
    {
      Box* box{ GetWorld()->ActorCreate<Box>(std::string{ "Box" } + std::to_string(i), boxPrev) };

      box->GetTransform()->SetLocalPosition(box->GetTransform()->GetLocalFront() * 2.0f);
      //box->GetTransform()->SetLocalRotation(R32V3{ 0.0f, 10.0f, 0.0f });
      //box->GetTransform()->SetLocalScale(R32V3{ 1.0f, 1.0f, 1.0f });

      mBoxes.emplace_back(box);

      boxPrev = box;
    }

    //mBoxes[4]->GetTransform()->SetLocalRotation(R32V3{ 0.0f, 45.0f, 0.0f });

    for (U32 i{}; i < 8; i++)
    {
      RSH_LOG("Box:[%u] WP:[%.02f %.02f %.02f] WR:[%.02f %.02f %.02f] WS:[%.02f %.02f %.02f] LP:[%.02f %.02f %.02f] LR:[%.02f %.02f %.02f] LS:[%.02f %.02f %.02f]\n",
        i,
        mBoxes[i]->GetTransform()->GetWorldPosition().x, mBoxes[i]->GetTransform()->GetWorldPosition().y, mBoxes[i]->GetTransform()->GetWorldPosition().z,
        mBoxes[i]->GetTransform()->GetWorldRotation().x, mBoxes[i]->GetTransform()->GetWorldRotation().y, mBoxes[i]->GetTransform()->GetWorldRotation().z,
        mBoxes[i]->GetTransform()->GetWorldScale().x, mBoxes[i]->GetTransform()->GetWorldScale().y, mBoxes[i]->GetTransform()->GetWorldScale().z,
        mBoxes[i]->GetTransform()->GetLocalPosition().x, mBoxes[i]->GetTransform()->GetLocalPosition().y, mBoxes[i]->GetTransform()->GetLocalPosition().z,
        mBoxes[i]->GetTransform()->GetLocalRotation().x, mBoxes[i]->GetTransform()->GetLocalRotation().y, mBoxes[i]->GetTransform()->GetLocalRotation().z,
        mBoxes[i]->GetTransform()->GetLocalScale().x, mBoxes[i]->GetTransform()->GetLocalScale().y, mBoxes[i]->GetTransform()->GetLocalScale().z
      );
    }

    GetWorld()->SetMainGameActor(mPlayer);
  }

  virtual ~Sandbox()
  {
    GetWorld()->SetMainGameActor(nullptr);

    for (Box* box : mBoxes)
    {
      GetWorld()->ActorDestroy(box);
    }

    GetWorld()->ActorDestroy(mPlayer);
  }

protected:
  void Update(R32 timeDelta) override
  {
    Module::Update(timeDelta);

    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ -2.0f, 0.0f, 0.0f }, R32V4{ 1.0f, 0.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 2.0f, 0.0f }, R32V4{ 0.0f, 1.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 0.0f, 2.0f }, R32V4{ 0.0f, 0.0f, 1.0f, 1.0f });

    static R32 x{};
    x += timeDelta;

    //for (U32 i{}; i < 7; i++)
    //{
    //  mBoxes[i + 1]->GetTransform()->SetLocalRotation(R32V3{ glm::sin(x) * 90.0f, 0.0f, 0.0f });
    //}

    static R32 yaw{};
    yaw += timeDelta * 50.0f;
    //mBoxes[0]->GetTransform()->SetWorldPosition(mBoxes[0]->GetTransform()->GetLocalRight() * glm::sin(x * 10.0f) * 5.0f);
    mBoxes[0]->GetTransform()->SetWorldRotation(R32V3{ 0.0f, yaw, 0.0f });
    mBoxes[0]->GetTransform()->SetLocalRotation(R32V3{ 0.0f, yaw, 0.0f });

    mBoxes[4]->GetTransform()->SetLocalRotation(R32V3{ 0.0f, 0.0f, yaw });
  }

private:
  Player* mPlayer{};

  std::vector<Box*> mBoxes{};
};

DECLARE_MODULE_IMPL(Sandbox);