#include <Redshift/World.h>
#include <Redshift/Mesh.h>
#include <Redshift/Shader.h>

#include <Redshift/Renderer/PbRenderer.h>

#include <Redshift/Components/Transform.h>
#include <Redshift/Components/Camera.h>
#include <Redshift/Components/Model.h>

///////////////////////////////////////////////////////////
// PbRenderer implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  PbRenderer::PbRenderer(World* world)
    : mWorld{ world }
  {

  }

  void PbRenderer::Render()
  {
    TraverseActorHierarchy();

    RenderPass();
    LightPass();
  }

  void PbRenderer::TraverseActorHierarchy()
  {
    for (auto actor : mWorld->GetActors())
    {
      Model* model{ actor->GetComponent<Model>() };
      if (model)
      {
        mRenderQueue.emplace(RenderTask{ actor->GetTransform(), model->GetMeshPtr(), model->GetShaderPtr() });
      }
    }
  }

  void PbRenderer::RenderPass()
  {
    while (!mRenderQueue.empty())
    {
      RenderTask task{ mRenderQueue.front() };

      Camera* camera{ mWorld->GetMainCamera() };

      if (camera)
      {
        if (task.Shader->Valid())
        {
          task.Shader->Bind();
          
          task.Shader->SetUniformR32M4("UniformProjectionMatrix", camera->GetProjectionMatrix());
          task.Shader->SetUniformR32M4("UniformViewMatrix", camera->GetViewMatrix());
          task.Shader->SetUniformR32M4("UniformModelMatrix", task.Transform->GetModelMatrix());

          task.Mesh->Bind();

          task.Mesh->Render();

          task.Mesh->UnBind();
          task.Shader->UnBind();
        }
      }

      mRenderQueue.pop();
    }
  }

  void PbRenderer::LightPass()
  {

  }
}