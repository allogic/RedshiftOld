#ifndef RSH_MODEL_H
#define RSH_MODEL_H

#include <string>
#include <vector>
#include <map>

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
    Model(World* world, Actor* actor, std::string const& modelFile, std::string const& shaderName);

  public:
    inline std::string const& GetMeshName() const { return ""; }
    inline std::string const& GetMeshFile() const { return ""; }
    inline Mesh const* GetMesh() const { return nullptr; }
    inline Shader const* GetShader() const { return nullptr; }

  private:
    std::vector<Mesh*> mMeshes{};
    std::map<std::string, std::vector<Material*>> mMaterials{};
    std::map<std::string, std::vector<Texture*>> mTextures{};

    Shader& mShader;
  };
}

#endif