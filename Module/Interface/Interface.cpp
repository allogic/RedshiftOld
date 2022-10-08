#include <Redshift/Module.h>
#include <Redshift/World.h>

#include <Vendor/ImGui/imgui.h>

using namespace rsh;

///////////////////////////////////////////////////////////
// Editor implementation
///////////////////////////////////////////////////////////

class Editor : public Module
{
public:
  Editor(World* world) : Module{ world }
  {
    
  }

  virtual ~Editor()
  {

  }

public:
  void Update(R32 timeDelta) override
  {
    Module::Update(timeDelta);

    ImGui::Begin("Foo");
    ImGui::End();
  }
};

DECLARE_MODULE_IMPL(Editor);