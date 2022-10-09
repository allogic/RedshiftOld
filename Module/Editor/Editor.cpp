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

    if (GetWorld()->KeyHeld(World::eKeyCodeE)) GetTransform()->AddWorldPosition(GetTransform()->GetWorldUp() * mMovementSpeed);
    if (GetWorld()->KeyHeld(World::eKeyCodeQ)) GetTransform()->AddWorldPosition(-GetTransform()->GetWorldUp() * mMovementSpeed);

    if (GetWorld()->KeyHeld(World::eKeyCodeW)) GetTransform()->AddWorldPosition(GetTransform()->GetLocalFront() * mMovementSpeed);
    if (GetWorld()->KeyHeld(World::eKeyCodeS)) GetTransform()->AddWorldPosition(-GetTransform()->GetLocalFront() * mMovementSpeed);

    static R32V2 mousePositionStart{};
    static R32V2 mousePositionDelta{};
    if (GetWorld()->MouseDown(World::eMouseCodeRight))
    {
      mousePositionStart = GetWorld()->GetMousePosition();
    }
    if (GetWorld()->MouseHeld(World::eMouseCodeRight))
    {
      mousePositionDelta = mousePositionStart - GetWorld()->GetMousePosition();
      R32V3 localRotation{ GetTransform()->GetLocalRotation() };
      localRotation.x -= mousePositionDelta.y * mRotationSpeed;
      localRotation.y += mousePositionDelta.x * mRotationSpeed;
      if (localRotation.x < -90.0f) localRotation.x = -90.0f;
      if (localRotation.x > 90.0f) localRotation.x = 90.0f;
      mousePositionStart -= mousePositionDelta * mRotationDamping;
      GetTransform()->SetLocalRotation(localRotation);
    }
  }

private:
  Camera* mCamera{ ComponentAttach<Camera>() };

  R32 mMovementSpeed{ 0.05f };
  R32 mRotationSpeed{ 0.05f };

  R32 mRotationDamping{ 0.1f };
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

    mPlayer->GetTransform()->SetWorldPosition(R32V3{ 0.0f, 0.0f, -15.0f });

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
    DebugComponents();
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
  void DebugComponents()
  {
    ImGui::Begin("Components");

    if (mSelectedActor)
    {
      for (auto const& [hash, component] : mSelectedActor->GetComponents())
      {
        if (hash == typeid(Transform).hash_code())
        {
          Transform* transform{ (Transform*)component };

          if (ImGui::TreeNode("Transform"))
          {
            R32V3 worldPosition{ transform->GetWorldPosition() };
            ImGui::DragFloat3("##World Position", &worldPosition[0], 0.1f);
            transform->SetWorldPosition(worldPosition);

            R32V3 worldRotation{ transform->GetWorldRotation() };
            ImGui::DragFloat3("##World Rotation", &worldRotation[0], 0.1f);
            transform->SetWorldRotation(worldRotation);

            R32V3 worldScale{ transform->GetWorldScale() };
            ImGui::DragFloat3("##World Scale", &worldScale[0], 0.1f);
            transform->SetWorldScale(worldScale);

            R32V3 localPosition{ transform->GetLocalPosition() };
            ImGui::DragFloat3("##Local Position", &localPosition[0], 0.1f);
            transform->SetLocalPosition(localPosition);

            R32V3 localRotation{ transform->GetLocalRotation() };
            ImGui::DragFloat3("##Local Rotation", &localRotation[0], 0.1f);
            transform->SetLocalRotation(localRotation);

            R32V3 localScale{ transform->GetLocalScale() };
            ImGui::DragFloat3("##Local Scale", &localScale[0], 0.1f);
            transform->SetLocalScale(localScale);

            ImGui::TreePop();
          }
        }
        else if (hash == typeid(Camera).hash_code())
        {
          Camera* camera{ (Camera*)component };

          if (ImGui::TreeNode("Camera"))
          {
            R32 fov{ camera->GetFov() };
            ImGui::DragFloat("##Fov", &fov);
            camera->SetFov(fov);

            R32 near{ camera->GetNear() };
            ImGui::DragFloat("##Near", &near);
            camera->SetNear(near);

            R32 far{ camera->GetFar() };
            ImGui::DragFloat("##Far", &far);
            camera->SetFar(far);

            ImGui::TreePop();
          }
        }
        else
        {
          if (ImGui::TreeNode("Unknown"))
          {
            ImGui::TreePop();
          }
        }
      }
    }

    ImGui::End();
  }

private:
  void DebugActor(Actor* actor)
  {
    if (ImGui::TreeNode(actor->GetName().c_str()))
    {
      if (ImGui::Selectable(actor->GetName().c_str(), mSelectedActor == actor))
      {
        mSelectedActor = actor;
      }

      for (Actor* child : actor->GetChildren())
      {
        DebugActor(child);
      }
      ImGui::TreePop();
    }
  }

private:
  Player* mPlayer{};

  Actor* mSelectedActor{};
};

DECLARE_MODULE_IMPL(Editor);