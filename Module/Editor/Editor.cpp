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

class Player : public Actor
{
public:
  Player(World* world, std::string const& name) : Actor{ world, name }
  {

  }

public:
  void Update(R32 timeDelta) override
  {
    if (GetWorld()->KeyHeld(World::eKeyCodeD)) GetTransform()->AddWorldPosition(GetTransform()->GetLocalRight() * mKeyboardMovementSpeed);
    if (GetWorld()->KeyHeld(World::eKeyCodeA)) GetTransform()->AddWorldPosition(-GetTransform()->GetLocalRight() * mKeyboardMovementSpeed);

    if (GetWorld()->KeyHeld(World::eKeyCodeE)) GetTransform()->AddWorldPosition(GetTransform()->GetWorldUp() * mKeyboardMovementSpeed);
    if (GetWorld()->KeyHeld(World::eKeyCodeQ)) GetTransform()->AddWorldPosition(-GetTransform()->GetWorldUp() * mKeyboardMovementSpeed);

    if (GetWorld()->KeyHeld(World::eKeyCodeW)) GetTransform()->AddWorldPosition(GetTransform()->GetLocalFront() * mKeyboardMovementSpeed);
    if (GetWorld()->KeyHeld(World::eKeyCodeS)) GetTransform()->AddWorldPosition(-GetTransform()->GetLocalFront() * mKeyboardMovementSpeed);

    static R32V2 mousePositionStart{};
    static R32V2 mousePositionDelta{};
    if (GetWorld()->MouseDown(World::eMouseCodeRight))
    {
      mousePositionStart = GetWorld()->GetMousePosition();
    }
    if (GetWorld()->MouseHeld(World::eMouseCodeRight) && GetWorld()->MouseHeld(World::eMouseCodeLeft))
    {
      mousePositionDelta = mousePositionStart - GetWorld()->GetMousePosition();
      R32V3 worldPosition{ GetTransform()->GetWorldPosition() };
      worldPosition -= GetTransform()->GetLocalRight() * mousePositionDelta.x * mMouseMovementSpeed;
      worldPosition += GetTransform()->GetWorldUp() * mousePositionDelta.y * mMouseMovementSpeed;
      GetTransform()->SetWorldPosition(worldPosition);
    }
    else if (GetWorld()->MouseHeld(World::eMouseCodeRight))
    {
      mousePositionDelta = mousePositionStart - GetWorld()->GetMousePosition();
      R32V3 localRotation{ GetTransform()->GetLocalRotation() };
      localRotation.x -= mousePositionDelta.y * mMouseRotationSpeed;
      localRotation.y += mousePositionDelta.x * mMouseRotationSpeed;
      if (localRotation.x < -90.0f) localRotation.x = -90.0f;
      if (localRotation.x > 90.0f) localRotation.x = 90.0f;
      GetTransform()->SetLocalRotation(localRotation);
    }
    mousePositionStart -= mousePositionDelta * mMouseDragDamping;
  }

private:
  Camera* mCamera{ ComponentAttach<Camera>() };

  R32 mKeyboardMovementSpeed{ 0.05f };
  R32 mMouseMovementSpeed{ 0.005f };

  R32 mMouseRotationSpeed{ 0.045f };

  R32 mMouseDragDamping{ 0.2f };
};

///////////////////////////////////////////////////////////
// Editor implementation
///////////////////////////////////////////////////////////

class Editor : public Module
{
public:
  Editor(World* world) : Module{ world }
  {
    mPlayer = GetWorld()->ActorCreate<Player>("EditorPlayer", nullptr);

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

          if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_SpanFullWidth))
          {
            ImGui::PushItemWidth(ImGui::GetWindowWidth() - ImGui::GetTreeNodeToLabelSpacing() - 100.0f);

            ImGui::Text("World Space");
            ImGui::PushID("World Space");

            R32V3 worldPosition{ transform->GetWorldPositionInternal() };
            if (ImGui::DragFloat3("Position", &worldPosition[0], 0.1f))
            {
              transform->SetWorldPosition(worldPosition);
            }

            R32V3 worldRotation{ transform->GetWorldRotationInternal() };
            if (ImGui::DragFloat3("Rotation", &worldRotation[0], 0.1f))
            {
              transform->SetWorldRotation(worldRotation);
            }

            R32V3 worldScale{ transform->GetWorldScaleInternal() };
            if (ImGui::DragFloat3("Scale", &worldScale[0], 0.1f))
            {
              transform->SetWorldScale(worldScale);
            }

            ImGui::PopID();
            ImGui::Text("Local Space");
            ImGui::PushID("Local Space");

            R32V3 localPosition{ transform->GetLocalPosition() };
            if (ImGui::DragFloat3("Position", &localPosition[0], 0.1f))
            {
              transform->SetLocalPosition(localPosition);
            }

            R32V3 localRotation{ transform->GetLocalRotation() };
            if (ImGui::DragFloat3("Rotation", &localRotation[0], 0.1f))
            {
              transform->SetLocalRotation(localRotation);
            }

            R32V3 localScale{ transform->GetLocalScale() };
            if (ImGui::DragFloat3("Scale", &localScale[0], 0.1f))
            {
              transform->SetLocalScale(localScale);
            }

            ImGui::PopID();
            ImGui::PopItemWidth();
            ImGui::TreePop();
          }
        }
        else if (hash == typeid(Camera).hash_code())
        {
          Camera* camera{ (Camera*)component };

          if (ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_SpanFullWidth))
          {
            ImGui::PushItemWidth(ImGui::GetWindowWidth() - ImGui::GetTreeNodeToLabelSpacing() - 100.0f);

            R32 fov{ camera->GetFov() };
            if (ImGui::DragFloat("Fov", &fov))
            {
              camera->SetFov(fov);
            }

            R32 near{ camera->GetNear() };
            if (ImGui::DragFloat("Near", &near))
            {
              camera->SetNear(near);
            }

            R32 far{ camera->GetFar() };
            if (ImGui::DragFloat("Far", &far))
            {
              camera->SetFar(far);
            }

            ImGui::PopItemWidth();
            ImGui::TreePop();
          }
        }
        else if (hash == typeid(Model).hash_code())
        {
          Model* model{ (Model*)component };

          if (ImGui::TreeNodeEx("Model", ImGuiTreeNodeFlags_SpanFullWidth))
          {
            ImGui::PushItemWidth(ImGui::GetWindowWidth() - ImGui::GetTreeNodeToLabelSpacing() - 100.0f);

            ImGui::Text(model->GetMeshName().c_str());
            ImGui::Text(model->GetMeshFile().c_str());

            ImGui::PopItemWidth();
            ImGui::TreePop();
          }
        }
        else
        {
          if (ImGui::TreeNodeEx("Unknown", ImGuiTreeNodeFlags_SpanFullWidth))
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
    U32 flags{ ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth };

    if (actor == mSelectedActor) flags |= ImGuiTreeNodeFlags_Selected;
    if (!actor->HasChildren()) flags |= ImGuiTreeNodeFlags_Leaf;

    U8 opened{ ImGui::TreeNodeEx(actor->GetName().c_str(), flags) };

    if (ImGui::IsItemClicked())
    {
      mSelectedActor = actor;
    }

    if (opened)
    {
      for (Actor* child : actor->GetChildren())
      {
        DebugActor(child);
      }

      if (opened)
      {
        ImGui::TreePop();
      }
    }
  }

private:
  Player* mPlayer{};

  Actor* mSelectedActor{};
};

DECLARE_MODULE_IMPL(Editor);