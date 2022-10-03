#include <string>
#include <cstring>
#include <fstream>
#include <regex>

#include <Redshift/Debug.h>
#include <Redshift/Shader.h>

#include <Vendor/Glad/glad.h>

///////////////////////////////////////////////////////////
// Shader implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  U32 Shader::Create(std::string const& vertexShader, std::string const& fragmentShader)
  {
    mProgram = glCreateProgram();

    U32 vid{ glCreateShader(GL_VERTEX_SHADER) };
    U32 fid{ glCreateShader(GL_FRAGMENT_SHADER) };

    char const* vs{ &vertexShader[0] };
    glShaderSource(vid, 1, &vs, nullptr);
    glCompileShader(vid);
    U32 vsCompileStatus{ CheckCompileStatus(vid) };

    char const* fs{ &fragmentShader[0] };
    glShaderSource(fid, 1, &fs, nullptr);
    glCompileShader(fid);
    U32 fsCompileStatus{ CheckCompileStatus(fid) };

    U32 shaderLinkStatus{};
    if (vsCompileStatus && fsCompileStatus)
    {
      glAttachShader(mProgram, vid);
      glAttachShader(mProgram, fid);
      glLinkProgram(mProgram);
      shaderLinkStatus = CheckLinkStatus(mProgram);
    }

    glDeleteShader(vid);
    glDeleteShader(fid);

    if (!shaderLinkStatus)
    {
      glDeleteProgram(mProgram);
      mProgram = 0;
    }

    return mProgram;
  }

  U32 Shader::Valid()
  {
    return mProgram;
  }

  void Shader::Bind()
  {
    glUseProgram(mProgram);
  }

  void Shader::UnBind()
  {
    glUseProgram(0);
  }

  void Shader::Destroy()
  {
    glDeleteProgram(mProgram);
    mProgram = 0;
  }

  U32 Shader::ExtractShaderStages(std::string const& shaderFile, std::string& vertexShader, std::string& fragmentShader)
  {
    std::ifstream stream{ shaderFile, std::ios::ate };
    std::string shaderSource{};

    if (stream.is_open())
    {
      shaderSource.resize(stream.tellg());
      stream.seekg(std::ios::beg);

      stream.read(&shaderSource[0], shaderSource.size());

      stream.close();
    }

    std::regex regex{ "([^@]*[^@])" };
    std::smatch matches{};

    while (std::regex_search(shaderSource, matches, regex))
    {
      if (matches.size() == 2)
      {
        if (std::strncmp(matches[0].str().c_str(), "vertex", 6) == 0)
        {
          vertexShader = matches[0].str().substr(7);
        }

        if (std::strncmp(matches[0].str().c_str(), "fragment", 8) == 0)
        {
          fragmentShader = matches[0].str().substr(9);
        }
      }

      shaderSource = matches.suffix();
    }

    return vertexShader.size() && fragmentShader.size();
  }

  U32 Shader::CheckCompileStatus(U32 sid)
  {
    I32 compileStatus{};
    I32 infoLogLength{};

    std::string log{};

    glGetShaderiv(sid, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == 0)
    {
      glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &infoLogLength);
      if (infoLogLength > 0)
      {
        log.resize(infoLogLength);

        glGetShaderInfoLog(sid, infoLogLength, &infoLogLength, &log[0]);

        RSH_LOG("%s\n", &log[0]);

        return 0;
      }
    }

    return 1;
  }

  U32 Shader::CheckLinkStatus(U32 pid)
  {
    I32 compileStatus{};
    I32 infoLogLength{};

    std::string log{};

    glGetProgramiv(pid, GL_LINK_STATUS, &compileStatus);
    if (compileStatus == 0)
    {
      glGetProgramiv(pid, GL_INFO_LOG_LENGTH, &infoLogLength);
      if (infoLogLength > 0)
      {
        log.resize(infoLogLength);

        glGetProgramInfoLog(pid, infoLogLength, &infoLogLength, &log[0]);

        RSH_LOG("%s\n", &log[0]);

        return 0;
      }
    }

    return 1;
  }

  void Shader::SetUniformR32(std::string const& name, R32 value)
  {
    glUniform1f(
      glGetUniformLocation(mProgram, name.c_str()),
      value
    );
  }

  void Shader::SetUniformR32M4(std::string const& name, R32M4 value)
  {
    glUniformMatrix4fv(
      glGetUniformLocation(mProgram, name.c_str()),
      1,
      0,
      &value[0][0]
    );
  }
}