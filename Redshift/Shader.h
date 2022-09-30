#ifndef RSH_SHADER_H
#define RSH_SHADER_H

#include <Redshift/Types.h>

namespace rsh
{
  class Shader
  {
  public:
    static U32 ExtractShaderStages(std::string const& shaderFile, std::string& vertexShader, std::string& fragmentShader);

  public:
    static U32 Create(std::string const& vertexShader, std::string const& fragmentShader);
    static void Destroy(U32 shader);

  private:
    static U32 CheckCompileStatus(U32 sid);
    static U32 CheckLinkStatus(U32 pid);
  };
}

#endif