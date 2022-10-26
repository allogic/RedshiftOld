#ifndef RSH_MODEL_H
#define RSH_MODEL_H

#include <string>
#include <vector>

#include <Redshift/Types.h>
#include <Redshift/Component.h>
#include <Redshift/Mesh.h>
#include <Redshift/Texture.h>
#include <Redshift/Material.h>
#include <Redshift/Shader.h>

///////////////////////////////////////////////////////////
// Model definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;
  class Actor;

  class Model : public Component
  {
  public:
    Model(World* world, Actor* actor, std::string const& meshName, std::string const& meshFile, std::string const& shaderName);

  public:
    inline std::string const& GetMeshName() const { return mMeshName; }
    inline std::string const& GetMeshFile() const { return mMeshFile; }
    inline Mesh const* GetMesh() const { return &mMesh; }
    inline Shader const* GetShader() const { return &mShader; }

  private:
    std::string mMeshName{};
    std::string mMeshFile{};

    std::vector<Mesh&> mMeshes{};
    std::vector<Material&> mMaterials{};
    std::vector<Texture&> mTextures{};
    std::vector<Shader&> mShaders{};
  };
}

#endif