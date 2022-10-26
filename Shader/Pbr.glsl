@vertex
#version 450 core

layout (location = 0) in vec3 InputPosition;
layout (location = 1) in vec3 InputNormal;
layout (location = 2) in vec2 InputUv;
layout (location = 3) in vec4 InputColor;
layout (location = 4) in vec3 InputTangent;

layout (location = 0) out Vertex
{
  vec3 Position;
  vec3 Normal;
  vec2 Uv;
  vec4 Color;
} vertex;

uniform mat4 UniformProjectionMatrix;
uniform mat4 UniformViewMatrix;
uniform mat4 UniformModelMatrix;

void main()
{
  vertex.Position = InputPosition;
  vertex.Normal = InputNormal;
  vertex.Uv = InputUv;
  vertex.Color = InputColor;

  gl_Position = UniformProjectionMatrix * UniformViewMatrix * UniformModelMatrix * vec4(InputPosition, 1.0);
}

@fragment
#version 450 core

layout (location = 0) in Vertex
{
  vec3 Position;
  vec3 Normal;
  vec2 Uv;
  vec4 Color;
} vertex;

layout (location = 0) out vec4 OutputColor;

void main()
{
  OutputColor = vec4(0.0, 1.0, 0.0, 1.0);
}