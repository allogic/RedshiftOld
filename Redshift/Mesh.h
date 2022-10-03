#ifndef RSH_MESH_H
#define RSH_MESH_H

#include <Redshift/Types.h>
#include <Redshift/Vertex.h>

#include <Vendor/Glad/glad.h>

///////////////////////////////////////////////////////////
// Mesh definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class Mesh
  {
  public:
    template<typename V, typename E>
    Mesh& Create(U32 vertexCount, V* vertexBuffer, U32 elementCount, E* elementBuffer);
    U32 Valid();
    void Bind();
    void Render(U32 elementCount);
    void UnBind();
    void Destroy();

  public:
    template<typename V>
    void UploadVertices(V* vertexBuffer, U32 vertexCount);
    template<typename E>
    void UploadElements(E* elementBuffer, U32 elementCount);

  private:
    U32 mVao{};
    U32 mVbo{};
    U32 mEbo{};
  };
}

///////////////////////////////////////////////////////////
// Inline mesh implementation
///////////////////////////////////////////////////////////

template<typename V, typename E>
rsh::Mesh& rsh::Mesh::Create(U32 vertexCount, V* vertexBuffer, U32 elementCount, E* elementBuffer)
{
  glGenVertexArrays(1, &mVao);

  glGenBuffers(1, &mVbo);
  glGenBuffers(1, &mEbo);

  glBindVertexArray(mVao);

  glBindBuffer(GL_ARRAY_BUFFER, mVbo);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(V), vertexBuffer, GL_STATIC_READ | GL_STATIC_DRAW);

  switch (V::Type)
  {
    case VertexType::eVertexTypeDebug:
    {
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDebug), (void*)(0));
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexDebug), (void*)(sizeof(R32V3)));
      break;
    }
    case VertexType::eVertexTypePbr:
    {
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
      glEnableVertexAttribArray(3);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPbr), (void*)(0));
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPbr), (void*)(sizeof(R32V3)));
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPbr), (void*)(sizeof(R32V3) + sizeof(R32V3)));
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPbr), (void*)(sizeof(R32V3) + sizeof(R32V3) + sizeof(R32V2)));
      break;
    }
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(E), elementBuffer, GL_STATIC_READ | GL_STATIC_DRAW);

  glBindVertexArray(0);

  return *this;
}

template<typename V>
void rsh::Mesh::UploadVertices(V* vertexBuffer, U32 vertexCount)
{
  glBindBuffer(GL_ARRAY_BUFFER, mVbo);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(V), vertexBuffer, GL_STATIC_READ | GL_STATIC_DRAW);
}

template<typename E>
void rsh::Mesh::UploadElements(E* elementBuffer, U32 elementCount)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(E), elementBuffer, GL_STATIC_READ | GL_STATIC_DRAW);
}

#endif