#include <Redshift/Module.h>
#include <Redshift/World.h>

#include <Vendor/Glad/glad.h>

#include <Vendor/ImGui/imgui.h>

///////////////////////////////////////////////////////////
// Module implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Module::Module(class World* world)
    : mWorld{ world }
  {
    gladLoadGL();
  }

  Module::~Module()
  {

  }

  void Module::Update(R32 timeDelta)
  {
    gladLoadGL();

    ImGui::SetCurrentContext(mWorld->GetImGuiContext());
    //ImGui::SetAllocatorFunctions(nullptr, nullptr);
  }
}