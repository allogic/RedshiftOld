#ifndef RSH_PB_RENDERER_H
#define RSH_PB_RENDERER_H

#include <queue>

#include <Redshift/Types.h>

///////////////////////////////////////////////////////////
// PbRenderer definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;
  class Transform;
  class Mesh;
  class Shader;

  class PbRenderer
  {
  private:
    struct RenderTask
    {
      Transform* Transform;
      Mesh* Mesh;
      Shader* Shader;
    };

  public:
    PbRenderer(World* world);

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