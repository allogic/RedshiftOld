@vertex
#version 450 core

layout (location = 0) in vec3 InputPosition;
layout (location = 1) in vec3 InputNormal;
layout (location = 2) in vec2 InputUv;
layout (location = 3) in vec4 InputColor;

layout (location = 0) out Vertex
{
  vec3 Position;
  vec3 Normal;
  vec2 Uv;
  vec4 Color;
} vertex;

uniform mat4 UniformProjection;
uniform mat4 UniformView;
uniform mat4 UniformModel;

void main()
{
  vertex.Position = InputPosition;
  vertex.Normal = InputNormal;
  vertex.Uv = InputUv;
  vertex.Color = InputColor;
  gl_Position = UniformProjection * UniformView * UniformModel * vec4(InputPosition, 1.0);
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
  OutputColor = vertex.Color;
}