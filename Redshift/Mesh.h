#ifndef RSH_MESH_H
#define RSH_MESH_H

#include <string>

#include <Redshift/Types.h>
#include <Redshift/Vertex.h>
#include <Redshift/Importer.h>

#include <Vendor/Glad/glad.h>

///////////////////////////////////////////////////////////
// Mesh definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class Mesh
  {
  public:
    enum RenderMode
    {
      eRenderModeLines = 1,
      eRenderModeTriangles = 4,
    };

  public:
    template<typename V, typename E>
    Mesh& Create(V* vertexBuffer, U32 vertexCount, E* elementBuffer, U32 elementCount);

    template<typename V, typename E>
    Mesh& Create(std::string const& meshFile);

    void Destroy();


  public:
    U32 Valid() const;
    void Bind() const;
    void Render(RenderMode renderMode) const;
    void UnBind() const;

  public:
    template<typename V>
    void UploadVertices(V* vertexBuffer, U32 vertexCount);
    template<typename E>
    void UploadElements(E* elementBuffer, U32 elementCount);

  private:
    U32 mVao{};
    U32 mVbo{};
    U32 mEbo{};

    U32 mElementCount{};
  };
}

///////////////////////////////////////////////////////////
// Mesh implementation
///////////////////////////////////////////////////////////

template<typename V, typename E>
rsh::Mesh& rsh::Mesh::Create(V* vertexBuffer, U32 vertexCount, E* elementBuffer, U32 elementCount)
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
    case VertexType::eVertexTypePhysicalBased:
    {
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
      glEnableVertexAttribArray(3);
      glEnableVertexAttribArray(4);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPhysicalBased), (void*)(0));
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPhysicalBased), (void*)(sizeof(R32V3)));
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPhysicalBased), (void*)(sizeof(R32V3) + sizeof(R32V3)));
      glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPhysicalBased), (void*)(sizeof(R32V3) + sizeof(R32V3) + sizeof(R32V2)));
      glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPhysicalBased), (void*)(sizeof(R32V3) + sizeof(R32V3) + sizeof(R32V2) + sizeof(R32V4)));
      break;
    }
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(E), elementBuffer, GL_STATIC_READ | GL_STATIC_DRAW);

  glBindVertexArray(0);

  return *this;
}

template<typename V, typename E>
rsh::Mesh& rsh::Mesh::Create(std::string const& meshFile)
{
  std::vector<V> vertices{};
  std::vector<E> elements{};

  switch (V::Type)
  {
    case VertexType::eVertexTypePhysicalBased:
    {
      if (Importer::LoadFbx(meshFile, vertices, elements))
      {
        Create(&vertices[0], (U32)vertices.size(), &elements[0], (U32)elements.size());

        mElementCount = (U32)elements.size();
      }
    }
  }

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

  mElementCount = elementCount;
}

#endif