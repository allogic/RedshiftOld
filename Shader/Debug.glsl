@vertex
#version 450 core

layout (location = 0) in vec4 InputPosition;
layout (location = 1) in vec4 InputColor;

layout (location = 0) out Vertex
{
  vec3 Position;
  vec4 Color;
} vertex;

uniform mat4 UniformProjectionMatrix;
uniform mat4 UniformViewMatrix;

void main()
{
  vertex.Color = InputColor;
  gl_Position = UniformProjectionMatrix * UniformViewMatrix * InputPosition;
}

@fragment
#version 450 core

layout (location = 0) in Vertex
{
  vec3 Position;
  vec4 Color;
} vertex;

layout (location = 0) out vec4 OutputColor;

void main()
{
  OutputColor = vertex.Color;
}