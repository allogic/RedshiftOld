#include <Redshift/World.h>
#include <Redshift/Mesh.h>
#include <Redshift/Shader.h>

#include <Redshift/Renderer/PhysicalBasedRenderer.h>

#include <Redshift/Components/Transform.h>
#include <Redshift/Components/Camera.h>
#include <Redshift/Components/Model.h>

///////////////////////////////////////////////////////////
// PhysicalBasedRenderer implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  PhysicalBasedRenderer::PhysicalBasedRenderer(World* world)
    : mWorld{ world }
  {

  }

  void PhysicalBasedRenderer::Render()
  {
    TraverseActorHierarchy();

    RenderPass();
    LightPass();
  }

  void PhysicalBasedRenderer::TraverseActorHierarchy()
  {
    for (auto actor : mWorld->GetActors())
    {
      Model* model{ actor->GetComponent<Model>() };
      if (model)
      {
        mRenderQueue.emplace(RenderTask{ actor->GetTransform(), model->GetMesh(), model->GetShader() });
      }
    }
  }

  void PhysicalBasedRenderer::RenderPass()
  {
    while (!mRenderQueue.empty())
    {
      RenderTask& task{ mRenderQueue.front() };

      Camera* camera{ mWorld->GetMainCamera() };

      if (camera)
      {
        if (task.ShaderPtr->Valid())
        {
          task.ShaderPtr->Bind();
          
          task.ShaderPtr->SetUniformR32M4("UniformProjectionMatrix", camera->GetProjectionMatrix());
          task.ShaderPtr->SetUniformR32M4("UniformViewMatrix", camera->GetViewMatrix());
          task.ShaderPtr->SetUniformR32M4("UniformModelMatrix", task.TransformPtr->GetModelMatrix());

          task.MeshPtr->Bind();

          task.MeshPtr->Render(Mesh::eRenderModeTriangles);

          task.MeshPtr->UnBind();
          task.ShaderPtr->UnBind();
        }
      }

      mRenderQueue.pop();
    }
  }

  void PhysicalBasedRenderer::LightPass()
  {

  }
}