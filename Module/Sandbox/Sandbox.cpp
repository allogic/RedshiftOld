#include <string>
#include <vector>

#include <Redshift/Module.h>
#include <Redshift/World.h>
#include <Redshift/Debug.h>
#include <Redshift/Actor.h>

#include <Redshift/Components/Transform.h>
#include <Redshift/Components/Camera.h>
#include <Redshift/Components/Model.h>

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

    GetWorld()->DebugBox(GetTransform()->GetWorldPosition(), GetTransform()->GetWorldScale(), R32V4{1.0f, 1.0f, 0.0f, 1.0f}, GetTransform()->GetQuaternion());
  }
};

class Rock : public Actor
{
public:
  Rock(World* world, std::string const& name) : Actor{ world, name }
  {

  }

public:
  void Update(R32 timeDelta) override
  {

  }

private:
  Model* mModel{ ComponentAttach<Model>(ASSET_DIR "Rock/Rock.fbx", "Pbr") };
};

class Marauder : public Actor
{
public:
  Marauder(World* world, std::string const& name) : Actor{ world, name }
  {

  }

public:
  void Update(R32 timeDelta) override
  {

  }

private:
  Model* mModel{ ComponentAttach<Model>(ASSET_DIR "Marauder/MarauderScaled.fbx", "Pbr") };
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
    mPlayer = GetWorld()->ActorCreate<Player>("GamePlayer", nullptr);

    mRock = GetWorld()->ActorCreate<Rock>("Rock", nullptr);
    mRock->GetTransform()->SetWorldPosition(R32V3{ 10.0f, 0.0f, 10.0f });
    mRock->GetTransform()->SetWorldScale(R32V3{ 0.1f, 0.1f, 0.1f });

    mMarauder = GetWorld()->ActorCreate<Marauder>("Marauder", nullptr);
    mMarauder->GetTransform()->SetWorldPosition(R32V3{ 100.f, 0.0f, 100.0f });
    mMarauder->GetTransform()->SetWorldScale(R32V3{ 0.1f, 0.1f, 0.1f });

    mPlayer->GetTransform()->SetWorldPosition(R32V3{ 0.0f, 0.0f, -15.0f });

    mRoot = GetWorld()->ActorCreate<Box>("Root", nullptr);

    mBody = GetWorld()->ActorCreate<Box>("Body", mRoot);
    mBody->GetTransform()->SetLocalPosition(R32V3{ 0.0f, 10.0f, 0.0f });
    mBody->GetTransform()->SetLocalScale(R32V3{ 3.0f, 5.0f, 1.0f });

    mLeftUpperArmJoint = GetWorld()->ActorCreate<Box>("LeftUpperArmJoint", mBody);
    mLeftUpperArmJoint->GetTransform()->SetLocalPosition(R32V3{ -2.0f, 2.0f, 0.0f });

    mLeftUpperArm = GetWorld()->ActorCreate<Box>("LeftUpperArm", mLeftUpperArmJoint);
    mLeftUpperArm->GetTransform()->SetLocalPosition(R32V3{ 0.0, 4.0f, 0.0f });
    mLeftUpperArm->GetTransform()->SetLocalScale(R32V3{ 1.0f, 3.0f, 1.0f });

    mRightUpperArmJoint = GetWorld()->ActorCreate<Box>("RightUpperArmJoint", mBody);
    mRightUpperArmJoint->GetTransform()->SetLocalPosition(R32V3{ 2.0f, 2.0f, 0.0f });

    mRightUpperArm = GetWorld()->ActorCreate<Box>("RightUpperArm", mRightUpperArmJoint);
    mRightUpperArm->GetTransform()->SetLocalPosition(R32V3{ 0.0f, 4.0f, 0.0f });
    mRightUpperArm->GetTransform()->SetLocalScale(R32V3{ 1.0f, 3.0f, 1.0f });

    mLeftUpperLegJoint = GetWorld()->ActorCreate<Box>("LeftUpperLegJoint", mBody);
    mLeftUpperLegJoint->GetTransform()->SetLocalPosition(R32V3{ -1.0f, -3.0f, 0.0f });

    mLeftUpperLeg = GetWorld()->ActorCreate<Box>("LeftUpperLeg", mLeftUpperLegJoint);
    mLeftUpperLeg->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -1.0f, 0.0f });
    mLeftUpperLeg->GetTransform()->SetLocalScale(R32V3{ 1.0f, 3.0f, 1.0f });

    mRightUpperLegJoint = GetWorld()->ActorCreate<Box>("RightUpperLegJoint", mBody);
    mRightUpperLegJoint->GetTransform()->SetLocalPosition(R32V3{ 1.0f, -3.0f, 0.0f });

    mRightUpperLeg = GetWorld()->ActorCreate<Box>("RightUpperLeg", mRightUpperLegJoint);
    mRightUpperLeg->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -1.0f, 0.0f });
    mRightUpperLeg->GetTransform()->SetLocalScale(R32V3{ 1.0f, 3.0f, 1.0f });

    mHead = GetWorld()->ActorCreate<Box>("Head", mBody);
    mHead->GetTransform()->SetLocalPosition(R32V3{ 0.0f, 3.0f, 0.0f });
    mHead->GetTransform()->SetLocalScale(R32V3{ 1.0f, 1.0f, 1.0f });

    mLeftLowerArm = GetWorld()->ActorCreate<Box>("LeftLowerArm", mLeftUpperArm);
    mLeftLowerArm->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -3.0f, 0.0f });
    mLeftLowerArm->GetTransform()->SetLocalScale(R32V3{ 1.0f, 3.0f, 1.0f });

    mRightLowerArm = GetWorld()->ActorCreate<Box>("RightLowerArm", mRightUpperArm);
    mRightLowerArm->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -3.0f, 0.0f });
    mRightLowerArm->GetTransform()->SetLocalScale(R32V3{ 1.0f, 3.0f, 1.0f });

    mLeftLowerLeg = GetWorld()->ActorCreate<Box>("LeftLowerLeg", mLeftUpperLeg);
    mLeftLowerLeg->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -3.0f, 0.0f });
    mLeftLowerLeg->GetTransform()->SetLocalScale(R32V3{ 1.0f, 3.0f, 1.0f });

    mRightLowerLeg = GetWorld()->ActorCreate<Box>("RightLowerLeg", mRightUpperLeg);
    mRightLowerLeg->GetTransform()->SetLocalPosition(R32V3{ 0.0f, -3.0f, 0.0f });
    mRightLowerLeg->GetTransform()->SetLocalScale(R32V3{ 1.0f, 3.0f, 1.0f });

    //mRoot->GetTransform()->SetWorldScale(R32V3{ 0.2f, 0.2f, 0.2f });
    mRoot->GetTransform()->SetLocalScale(R32V3{ 10.0f, 10.0f, 10.0f });

    GetWorld()->SetMainGameActor(mPlayer);
  }

  virtual ~Sandbox()
  {
    GetWorld()->SetMainGameActor(nullptr);

    GetWorld()->ActorDestroy(mPlayer);

    GetWorld()->ActorDestroy(mRock);

    GetWorld()->ActorDestroy(mMarauder);

    GetWorld()->ActorDestroy(mRoot);

    GetWorld()->ActorDestroy(mBody);

    GetWorld()->ActorDestroy(mLeftUpperArmJoint);
    GetWorld()->ActorDestroy(mRightUpperArmJoint);

    GetWorld()->ActorDestroy(mLeftUpperArm);
    GetWorld()->ActorDestroy(mRightUpperArm);

    GetWorld()->ActorDestroy(mLeftUpperLegJoint);
    GetWorld()->ActorDestroy(mRightUpperLegJoint);

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

    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 2.0f, 0.0f, 0.0f }, R32V4{ 1.0f, 0.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 2.0f, 0.0f }, R32V4{ 0.0f, 1.0f, 0.0f, 1.0f });
    GetWorld()->DebugLine(R32V3{ 0.0f, 0.0f, 0.0f }, R32V3{ 0.0f, 0.0f, 2.0f }, R32V4{ 0.0f, 0.0f, 1.0f, 1.0f });

    mRoot->GetTransform()->SetWorldPosition(R32V3{ 5.0f, 0.0f, 0.0f });
    mRoot->GetTransform()->AddWorldRotation(R32V3{ 0.0f, 0.1f, 0.0f });

    mRoot->GetTransform()->AddLocalRotation(R32V3{ 0.0f, 0.2f, 0.0f });

    static R32 pitch{};
    pitch += timeDelta;

    mMarauder->GetTransform()->SetWorldPosition(R32V3{ glm::sin(pitch) * 10.0f, 0.0f, glm::cos(pitch) * 10.0f });

    mLeftUpperArm->GetTransform()->AddLocalRotation(R32V3{ glm::sin(pitch) * 90.0f, 0.0f, 0.0f });
    mRightUpperArm->GetTransform()->AddLocalRotation(R32V3{ -glm::sin(pitch) * 90.0f, 0.0f, 0.0f });

    mLeftUpperLeg->GetTransform()->AddLocalRotation(R32V3{ -glm::sin(pitch) * 45.0f, 0.0f, 0.0f });
    mRightUpperLeg->GetTransform()->AddLocalRotation(R32V3{ glm::sin(pitch) * 45.0f, 0.0f, 0.0f });
  }

private:
  Player* mPlayer{};

  Rock* mRock{};

  Marauder* mMarauder{};

  Box* mRoot{};

  Box* mBody{};

  Box* mLeftUpperArmJoint{};
  Box* mRightUpperArmJoint{};

  Box* mLeftUpperArm{};
  Box* mRightUpperArm{};

  Box* mLeftUpperLegJoint{};
  Box* mRightUpperLegJoint{};

  Box* mLeftUpperLeg{};
  Box* mRightUpperLeg{};

  Box* mHead{};

  Box* mLeftLowerArm{};
  Box* mRightLowerArm{};

  Box* mLeftLowerLeg{};
  Box* mRightLowerLeg{};
};

DECLARE_MODULE_IMPL(Sandbox);