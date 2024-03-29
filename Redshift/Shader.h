#ifndef RSH_SHADER_H
#define RSH_SHADER_H

#include <string>

#include <Redshift/Types.h>

///////////////////////////////////////////////////////////
// Shader definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class Shader
  {
  public:
    U32 Create(std::string const& vertexShader, std::string const& fragmentShader);
    void Destroy();

  public:
    U32 Valid() const;
    void Bind() const;
    void UnBind() const;

  public:
    static U32 ExtractShaderStages(std::string const& shaderFile, std::string& vertexShader, std::string& fragmentShader);
    static U32 CheckCompileStatus(U32 sid);
    static U32 CheckLinkStatus(U32 pid);

  public:
    void SetUniformR32(std::string const& name, R32 value) const;
    void SetUniformR32M4(std::string const& name, R32M4 value) const;

  private:
    U32 mProgram{};
  };
}

#endif