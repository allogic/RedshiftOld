#include <Redshift/Module.h>

#include <Vendor/Glad/glad.h>

///////////////////////////////////////////////////////////
// Module implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Module::Module(class World* world)
    : mWorld{ world }
  {

  }

  Module::~Module()
  {

  }

  void Module::Update(R32 timeDelta)
  {
    gladLoadGL();
  }
}