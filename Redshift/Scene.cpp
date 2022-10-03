#include <Redshift/Scene.h>

#include <Vendor/Glad/glad.h>

///////////////////////////////////////////////////////////
// Scene implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Scene::Scene(class World* world)
    : mWorld{ world }
  {

  }

  Scene::~Scene()
  {

  }

  void Scene::Update(R32 timeDelta)
  {
    gladLoadGL();
  }
}