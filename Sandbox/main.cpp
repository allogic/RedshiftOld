#include <Redshift/World.h>
#include <Redshift/Scene.h>
#include <Redshift/Debug.h>
#include <Redshift/Actor.h>
#include <Redshift/Vertex.h>

#include <Redshift/Components/Transform.h>
#include <Redshift/Components/Camera.h>

///////////////////////////////////////////////////////////
// Custom actors
///////////////////////////////////////////////////////////

class Player : public rsh::Actor
{
public:
  Player(std::string const& name) : rsh::Actor{ name }
  {
    RSH_LOG("%llX\n", (rsh::U64)typeid(rsh::VertexGizmos).hash_code());
    RSH_LOG("%llX\n", (rsh::U64)typeid(rsh::VertexPbr).hash_code());
  }
};

class Camera : public rsh::Actor
{
public:
  Camera(std::string const& name) : rsh::Actor{ name }
  {

  }
};

///////////////////////////////////////////////////////////
// Sandbox implementation
///////////////////////////////////////////////////////////

class Sandbox : public rsh::Scene
{
public:
  Sandbox(rsh::World* world) : rsh::Scene{ world }
  {
    RSH_LOG("Created\n");

    mPlayer = CreateActor<Player>("Player");
    mPlayer->AttachComponent<rsh::Transform>(rsh::R32V3{ 0.0f, 0.0f, 0.0f }, rsh::R32V3{ 0.0f, 0.0f, 0.0f }, rsh::R32V3{ 1.0f, 1.0f, 1.0f });

    mCamera = CreateActor<Camera>("Camera", mPlayer);
    mCamera->AttachComponent<rsh::Transform>(rsh::R32V3{ 0.0f, 0.0f, 0.0f }, rsh::R32V3{ 0.0f, 0.0f, 0.0f }, rsh::R32V3{ 1.0f, 1.0f, 1.0f });
    mCamera->AttachComponent<rsh::Camera>(45.0f, 0.001f, 1000.0f);
  }
  virtual ~Sandbox()
  {
    RSH_LOG("Destroyed\n");
  }

protected:
  rsh::U32 Tick(rsh::R32 deltaTime) override
  {
    return 0;
  }

private:
  Player* mPlayer{};
  Camera* mCamera{};
};

DECLARE_SCENE_IMPL(Sandbox);