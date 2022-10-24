#ifndef RSH_MODEL_H
#define RSH_MODEL_H

#include <string>

#include <Redshift/Types.h>
#include <Redshift/Component.h>
#include <Redshift/Mesh.h>
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
    inline Mesh* GetMeshPtr() const { return &mMesh; }
    inline Shader* GetShaderPtr() const { return &mShader; }

  private:
    std::string mMeshName{};
    std::string mMeshFile{};

    Mesh& mMesh;
    Shader& mShader;
  };
}

#endif