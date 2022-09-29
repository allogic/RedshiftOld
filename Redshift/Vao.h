#ifndef RSH_VAO_H
#define RSH_VAO_H

#include <typeinfo>

#include <Redshift/Types.h>
#include <Redshift/Vertex.h>

#include <Vendor/Glad/glad.h>

namespace rsh
{
  class Vao
  {
  public:
    template<typename V, typename E>
    static U32 Create(U32 vertexCount, V* vertices, U32 elementCount, E* elements);

    static void Destroy(U32 vao);
  };

  template<typename V, typename E>
  U32 Vao::Create(U32 vertexCount, V* vertices, U32 elementCount, E* elements)
  {
    U32 vao{};
    U32 vbo{};
    U32 ebo{};

    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(V), vertices, GL_STATIC_READ | GL_STATIC_DRAW);

    switch (V::VertexType)
    {
      case VertexType::Gizmos:
      {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexGizmos), (void*)(0));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexGizmos), (void*)(sizeof(R32V3)));
        break;
      }
      case VertexType::Pbr:
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(E), elements, GL_STATIC_READ | GL_STATIC_DRAW);

    glBindVertexArray(0);

    return vao;
  }
}

#endif