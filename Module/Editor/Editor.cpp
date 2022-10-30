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
    if (GetWorld()->KeyHeld(Event::eKeyCodeD)) GetTransform()->AddWorldPosition(-GetTransform()->GetLocalRight() * mKeyboardMovementSpeed);
    if (GetWorld()->KeyHeld(Event::eKeyCodeA)) GetTransform()->AddWorldPosition(GetTransform()->GetLocalRight() * mKeyboardMovementSpeed);

    if (GetWorld()->KeyHeld(Event::eKeyCodeE)) GetTransform()->AddWorldPosition(GetTransform()->GetWorldUp() * mKeyboardMovementSpeed);
    if (GetWorld()->KeyHeld(Event::eKeyCodeQ)) GetTransform()->AddWorldPosition(-GetTransform()->GetWorldUp() * mKeyboardMovementSpeed);

    if (GetWorld()->KeyHeld(Event::eKeyCodeW)) GetTransform()->AddWorldPosition(GetTransform()->GetLocalFront() * mKeyboardMovementSpeed);
    if (GetWorld()->KeyHeld(Event::eKeyCodeS)) GetTransform()->AddWorldPosition(-GetTransform()->GetLocalFront() * mKeyboardMovementSpeed);

    static R32V2 mousePositionStart{};
    static R32V2 mousePositionDelta{};
    if (GetWorld()->MouseDown(Event::eMouseCodeRight))
    {
      mousePositionStart = GetWorld()->GetMousePosition();
    }
    if (GetWorld()->MouseHeld(Event::eMouseCodeRight) && GetWorld()->MouseHeld(Event::eMouseCodeLeft))
    {
      mousePositionDelta = mousePositionStart - GetWorld()->GetMousePosition();
      R32V3 worldPosition{ GetTransform()->GetWorldPosition() };
      worldPosition += GetTransform()->GetLocalRight() * mousePositionDelta.x * mMouseMovementSpeed;
      worldPosition += GetTransform()->GetWorldUp() * mousePositionDelta.y * mMouseMovementSpeed;
      GetTransform()->SetWorldPosition(worldPosition);
    }
    else if (GetWorld()->MouseHeld(Event::eMouseCodeRight))
    {
      mousePositionDelta = mousePositionStart - GetWorld()->GetMousePosition();
      R32V3 worldRotation{ GetTransform()->GetWorldRotation() };
      worldRotation.x -= mousePositionDelta.y * mMouseRotationSpeed;
      worldRotation.y += mousePositionDelta.x * mMouseRotationSpeed;
      if (worldRotation.x < -90.0f) worldRotation.x = -90.0f;
      if (worldRotation.x > 90.0f) worldRotation.x = 90.0f;
      GetTransform()->SetLocalRotation(worldRotation);
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

    DebugAssets();
    DebugActors();
    DebugComponents();
  }

private:
  void DebugAssets()
  {
    ImGui::Begin("Assets");

    if (ImGui::BeginTable("Instances", 2, ImGuiTableFlags_Reorderable | ImGuiTableFlags_RowBg | ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersInnerV))
    {
      ImGui::TableSetupColumn("Type");
      ImGui::TableSetupColumn("Name");
      ImGui::TableSetupScrollFreeze(0, 1);
      ImGui::TableHeadersRow();

      for (auto const& [name, shader] : GetWorld()->GetShaders())
      {
        ImGui::TableNextColumn();
        ImGui::Text("Shader");
        ImGui::TableNextColumn();
        ImGui::Text("%s", name.c_str());
      }

      for (auto const& [name, material] : GetWorld()->GetMaterials())
      {
        ImGui::TableNextColumn();
        ImGui::Text("Material");
        ImGui::TableNextColumn();
        ImGui::Text("%s", name.c_str());
      }

      for (auto const& [name, mesh] : GetWorld()->GetMeshes())
      {
        ImGui::TableNextColumn();
        ImGui::Text("Mesh");
        ImGui::TableNextColumn();
        ImGui::Text("%s", name.c_str());
      }

      for (auto const& [name, mesh] : GetWorld()->GetTextures())
      {
        ImGui::TableNextColumn();
        ImGui::Text("Texture");
        ImGui::TableNextColumn();
        ImGui::Text("%s", name.c_str());
      }

      ImGui::EndTable();
    }

    ImGui::End();
  }
  void DebugActors()
  {
    ImGui::Begin("Actors");

    for (auto const& actor : GetWorld()->GetActors())
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
        if (hash == typeid(Transform).hash_code() && component)
        {
          Transform* transform{ (Transform*)component };

          if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_SpanFullWidth))
          {
            ImGui::PushItemWidth(ImGui::GetWindowWidth() - ImGui::GetTreeNodeToLabelSpacing() - 100.0f);

            ImGui::Text("World Space");
            ImGui::PushID("World Space");

            R32V3 worldPosition{ transform->GetPosition() };
            if (ImGui::DragFloat3("Position", &worldPosition[0], 0.1f))
            {
              transform->SetWorldPosition(worldPosition);
            }

            R32V3 worldRotation{ transform->GetRotation() };
            if (ImGui::DragFloat3("Rotation", &worldRotation[0], 0.1f))
            {
              transform->SetWorldRotation(worldRotation);
            }

            R32V3 worldScale{ transform->GetScale() };
            if (ImGui::DragFloat3("Scale", &worldScale[0], 0.1f))
            {
              transform->SetWorldScale(worldScale);
            }

            ImGui::PopID();
            ImGui::Text("Local Space");
            ImGui::PushID("Local Space");

            R32V3 localPosition{ transform->GetPosition() };
            if (ImGui::DragFloat3("Position", &localPosition[0], 0.1f))
            {
              transform->SetLocalPosition(localPosition);
            }

            R32V3 localRotation{ transform->GetRotation() };
            if (ImGui::DragFloat3("Rotation", &localRotation[0], 0.1f))
            {
              transform->SetLocalRotation(localRotation);
            }

            R32V3 localScale{ transform->GetScale() };
            if (ImGui::DragFloat3("Scale", &localScale[0], 0.1f))
            {
              transform->SetLocalScale(localScale);
            }

            ImGui::PopID();
            ImGui::PopItemWidth();
            ImGui::TreePop();
          }
        }
        else if (hash == typeid(Camera).hash_code() && component)
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
        else if (hash == typeid(Model).hash_code() && component)
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
        else if (component)
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