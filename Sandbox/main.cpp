#include <vector>

#include <Redshift/World.h>
#include <Redshift/Scene.h>
#include <Redshift/Debug.h>
#include <Redshift/Actor.h>

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
    //mWorld->DebugPushMatrix();
    mWorld->DebugBox(mTransform->GetPosition(), mTransform->GetScale(), R32V4{1.0f, 0.0f, 0.0f, 1.0f});
    //mWorld->DebugPopMatrix();
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
    mTransform->SetRotation(R32V3{ 0.0f, 0.0f, 0.0f });

    R32V3 p{ mTransform->GetPosition() };
    R32Q r{ mTransform->GetRotation() };

    p = r * p;

    //mTransform->AddRotation(R32V3{ 0.0f, 0.00001f, 0.0f });
    //mTransform->SetPosition(p);
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
    mPlayer->GetComponent<Transform>()->SetPosition(R32V3{ 0.0f, 0.0f, -10.0f });

    {
      Box* boxPrev{};
      for (U32 i{}; i < 8; i++)
      {
        Box* box{ mWorld->ActorCreate<Box>(std::string{ "BoxLeft" } + std::to_string(i), boxPrev) };
        box->GetComponent<Transform>()->SetPosition(R32V3{ -5.0f, i * 2, 20.0f });
        mBoxes.emplace_back(box);
        boxPrev = box;
      }
    }

    {
      Box* boxPrev{};
      for (U32 i{}; i < 8; i++)
      {
        Box* box{ mWorld->ActorCreate<Box>(std::string{ "BoxRight" } + std::to_string(i), boxPrev) };
        box->GetComponent<Transform>()->SetPosition(R32V3{ 5.0f, i * 2, 20.0f });
        mBoxes.emplace_back(box);
        boxPrev = box;
      }
    }

    mBoxes[0]->GetComponent<Transform>()->SetRotation(R32V3{ 0.0f, 45.0f, 0.0f });
    mBoxes[8]->GetComponent<Transform>()->SetRotation(R32V3{ 45.0f, 0.0f, 0.0f });

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
  }

private:
  Player* mPlayer{};

  std::vector<Box*> mBoxes{};
};

DECLARE_SCENE_IMPL(Sandbox);