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

class Player : public Actor
{
public:
  Player(World* world, std::string const& name) : Actor{ world, name }
  {

  }

public:
  void Update(R32 timeDelta) override
  {
    if (GetWorld()->KeyHeld(World::eKeyCodeD)) GetTransform()->AddWorldPosition(GetTransform()->GetLocalRight() * mMovementSpeed);
    if (GetWorld()->KeyHeld(World::eKeyCodeA)) GetTransform()->AddWorldPosition(-GetTransform()->GetLocalRight() * mMovementSpeed);

    if (GetWorld()->KeyHeld(World::eKeyCodeE)) GetTransform()->AddWorldPosition(GetTransform()->GetLocalUp() * mMovementSpeed);
    if (GetWorld()->KeyHeld(World::eKeyCodeQ)) GetTransform()->AddWorldPosition(-GetTransform()->GetLocalUp() * mMovementSpeed);

    if (GetWorld()->KeyHeld(World::eKeyCodeW)) GetTransform()->AddWorldPosition(GetTransform()->GetLocalFront() * mMovementSpeed);
    if (GetWorld()->KeyHeld(World::eKeyCodeS)) GetTransform()->AddWorldPosition(-GetTransform()->GetLocalFront() * mMovementSpeed);
  }

private:
  Camera* mCamera{ ComponentAttach<Camera>() };

  R32 mMovementSpeed{ 0.1f };
};

///////////////////////////////////////////////////////////
// Editor implementation
///////////////////////////////////////////////////////////

class Editor : public Module
{
public:
  Editor(World* world) : Module{ world }
  {
    mPlayer = GetWorld()->ActorCreate<Player>("EditorPlayer");

    mPlayer->GetTransform()->SetWorldPosition(R32V3{ 0.0f, 15.0f, -15.0f });

    GetWorld()->SetMainEditorActor(mPlayer);
  }

  virtual ~Editor()
  {
    GetWorld()->SetMainEditorActor(nullptr);

    GetWorld()->ActorDestroy(mPlayer);
  }

public:
  void Update(R32 timeDelta) override
  {
    Module::Update(timeDelta);

    DebugActors();
  }

private:
  void DebugActors()
  {
    ImGui::Begin("Actors");

    for (auto const& [name, actor] : GetWorld()->GetActors())
    {
      if (!actor->GetParent())
      {
        DebugActor(actor);
      }
    }

    ImGui::End();
  }

private:
  void DebugActor(Actor* actor)
  {
    if (ImGui::CollapsingHeader(actor->GetName().c_str()))
    {
      for (Actor* child : actor->GetChildren())
      {
        DebugActor(child);
      }
    }
  }

private:
  Player* mPlayer{};
};

DECLARE_MODULE_IMPL(Editor);