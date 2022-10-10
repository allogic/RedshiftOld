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

    GetWorld()->DebugBox(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldScale(), R32V4{1.0f, 1.0f, 0.0f, 1.0f}, GetTransform()->GetLocalQuaternion());
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

    mRoot = GetWorld()->ActorCreate<Box>("Root");

    mBody = GetWorld()->ActorCreate<Box>("Body", mRoot);
    mBody->GetTransform()->SetLocalPosition(R32V3{ 0.0f, 10.0f, 0.0f });
    mBody->GetTransform()->SetWorldScale(R32V3{ 3.0f, 5.0f, 1.0f });

    mLeftUpperArm = GetWorld()->ActorCreate<Box>("LeftUpperArm", mBody);
    mLeftUpperArm->GetTransform()->SetLocalPosition(R32V3{ -2.0f, 2.0f, 0.0f });
    mLeftUpperArm->GetTransform()->SetWorldScale(R32V3{ 1.0f, 2.5f, 1.0f });

    mRightUpperArm = GetWorld()->ActorCreate<Box>("RightUpperArm", mBody);
    mRightUpperArm->GetTransform()->SetLocalPosition(R32V3{ 2.0f, 2.0f, 0.0f });
    mRightUpperArm->GetTransform()->SetWorldScale(R32V3{ 1.0f, 2.5f, 1.0f });

    mLeftUpperLeg = GetWorld()->ActorCreate<Box>("LeftUpperLeg", mBody);
    mLeftUpperLeg->GetTransform()->SetLocalPosition(R32V3{ -1.0f, -3.0f, 0.0f });
    mLeftUpperLeg->GetTransform()->SetWorldScale(R32V3{ 1.0f, 2.5f, 1.0f });

    mRightUpperLeg = GetWorld()->ActorCreate<Box>("RightUpperLeg", mBody);
    mRightUpperLeg->GetTransform()->SetLocalPosition(R32V3{ 1.0f, -3.0f, 0.0f });
    mRightUpperLeg->GetTransform()->SetWorldScale(R32V3{ 1.0f, 2.5f, 1.0f });

    mHead = GetWorld()->ActorCreate<Box>("Head", mBody);
    mHead->GetTransform()->SetLocalPosition(R32V3{ 0.0f, 3.0f, 0.0f });
    mHead->GetTransform()->SetWorldScale(R32V3{ 1.0f, 1.0f, 1.0f });

    mLeftLowerArm = GetWorld()->ActorCreate<Box>("LeftLowerArm", mLeftUpperArm);
    mLeftLowerArm->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -2.0f, 0.0f });
    mLeftLowerArm->GetTransform()->SetWorldScale(R32V3{ 1.0f, 2.5f, 1.0f });

    mRightLowerArm = GetWorld()->ActorCreate<Box>("RightLowerArm", mRightUpperArm);
    mRightLowerArm->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -2.0f, 0.0f });
    mRightLowerArm->GetTransform()->SetWorldScale(R32V3{ 1.0f, 2.5f, 1.0f });

    mLeftLowerLeg = GetWorld()->ActorCreate<Box>("LeftLowerLeg", mLeftUpperLeg);
    mLeftLowerLeg->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -2.0f, 0.0f });
    mLeftLowerLeg->GetTransform()->SetWorldScale(R32V3{ 1.0f, 2.5f, 1.0f });

    mRightLowerLeg = GetWorld()->ActorCreate<Box>("RightLowerLeg", mRightUpperLeg);
    mRightLowerLeg->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -2.0f, 0.0f });
    mRightLowerLeg->GetTransform()->SetWorldScale(R32V3{ 1.0f, 2.5f, 1.0f });

    GetWorld()->SetMainGameActor(mPlayer);
  }

  virtual ~Sandbox()
  {
    GetWorld()->SetMainGameActor(nullptr);

    GetWorld()->ActorDestroy(mPlayer);

    GetWorld()->ActorDestroy(mRoot);

    GetWorld()->ActorDestroy(mBody);

    GetWorld()->ActorDestroy(mLeftUpperArm);
    GetWorld()->ActorDestroy(mRightUpperArm);

    GetWorld()->ActorDestroy(mLeftUpperLeg);
    GetWorld()->ActorDestroy(mRightUpperLeg);

    GetWorld()->ActorDestroy(mHead);

    GetWorld()->ActorDestroy(mLeftLowerArm);
    GetWorld()->ActorDestroy(mRightLowerArm);

    GetWorld()->ActorDestroy(mLeftLowerLeg);
    GetWorld()->ActorDestroy(mRightLowerLeg);
  }

protected:
  void Update(R32 timeDelta) override
  {
    Module::Update(timeDelta);

    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ -2.0f, 0.0f, 0.0f }, R32V4{ 1.0f, 0.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 2.0f, 0.0f }, R32V4{ 0.0f, 1.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 0.0f, 2.0f }, R32V4{ 0.0f, 0.0f, 1.0f, 1.0f });

    mRoot->GetTransform()->SetWorldPosition(R32V3{ 5.0f, 0.0f, 0.0f });
    mRoot->GetTransform()->AddWorldRotation(R32V3{ 0.0f, 0.1f, 0.0f });
    mRoot->GetTransform()->AddLocalRotation(R32V3{ 0.0f, 0.3f, 0.0f });

    // TODO: Inverse quaternion to current local rotation..

    //static R32 pitch{};
    //pitch += timeDelta;
    //mLeftUpperArm->GetTransform()->AddLocalRotation(R32V3{ 0.0f, 0.0f, glm::sin(pitch) * 90.0f });
  }

private:
  Player* mPlayer{};

  Box* mHead{};

  Box* mLeftLowerArm{};
  Box* mRightLowerArm{};

  Box* mLeftUpperArm{};
  Box* mRightUpperArm{};

  Box* mBody{};

  Box* mLeftLowerLeg{};
  Box* mRightLowerLeg{};

  Box* mLeftUpperLeg{};
  Box* mRightUpperLeg{};

  Box* mRoot{};
};

DECLARE_MODULE_IMPL(Sandbox);