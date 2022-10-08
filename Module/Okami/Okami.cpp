#include <Redshift/Module.h>
#include <Redshift/World.h>

using namespace rsh;

///////////////////////////////////////////////////////////
// Okami implementation
///////////////////////////////////////////////////////////

class Okami : public Module
{
public:
  Okami(World* world) : Module{ world }
  {
    
  }

  virtual ~Okami()
  {

  }
};

DECLARE_MODULE_IMPL(Okami);