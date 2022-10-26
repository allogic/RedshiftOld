#ifndef RSH_PHYSICAL_BASED_RENDERER_H
#define RSH_PHYSICAL_BASED_RENDERER_H

#include <queue>

#include <Redshift/Types.h>

///////////////////////////////////////////////////////////
// PhysicalBasedRenderer definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;
  class Transform;
  class Mesh;
  class Shader;

  class PhysicalBasedRenderer
  {
  private:
    struct RenderTask
    {
      Transform const* TransformPtr;
      Mesh const* MeshPtr;
      Shader const* ShaderPtr;
    };

  public:
    PhysicalBasedRenderer(World* world);

  public:
    void Render();

  private:
    void TraverseActorHierarchy();

    void RenderPass();
    void LightPass();

  private:
    World* mWorld{};

    std::queue<RenderTask> mRenderQueue{};
  };
}

#endif