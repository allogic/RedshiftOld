#include <fstream>

#include <Redshift/Importer.h>

#include <Redshift/Utils/FileReader.h>

#include <Vendor/OpenFbx/ofbx.h>

///////////////////////////////////////////////////////////
// Importer implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  U8 Importer::LoadFbx(std::string const& fbxFile, std::vector<VertexPb>& vertices, std::vector<U32>& elements)
  {
    std::vector<U8> bytes{};

    if (FileReader::ReadBytes(bytes, fbxFile))
    {
      ofbx::IScene* scene{ ofbx::load(&bytes[0], (U32)bytes.size(), (U64)ofbx::LoadFlags::TRIANGULATE) };
      if (scene)
      {
        ofbx::Mesh const* mesh{ scene->getMesh(0) };
        ofbx::Geometry const* geometry{ mesh->getGeometry() };

        ofbx::Vec3 const* vertexPtr{ geometry->getVertices() };
        ofbx::Vec3 const* normalPtr{ geometry->getNormals() };
        ofbx::Vec2 const* uvPtr{ geometry->getUVs() };
        ofbx::Vec4 const* colorPtr{ geometry->getColors() };
        I32 const* indexPtr{ geometry->getFaceIndices() };

        vertices.resize(geometry->getVertexCount());

        for (U32 j{}; j < (U32)geometry->getVertexCount(); j++)
        {
          if (vertexPtr) vertices[j].Position = R32V3{vertexPtr[j].x, vertexPtr[j].y, vertexPtr[j].z};
          if (normalPtr) vertices[j].Normal = R32V3{ normalPtr[j].x, normalPtr[j].y, normalPtr[j].z };
          if (uvPtr)     vertices[j].Uv = R32V2{ uvPtr[j].x, uvPtr[j].y };
          if (colorPtr)  vertices[j].Color = R32V4{ colorPtr[j].x, colorPtr[j].y, colorPtr[j].z, colorPtr[j].w };
        }

        elements.resize(geometry->getIndexCount());

        for (U32 j{}; j < (U32)geometry->getIndexCount(); j++)
        {
          elements[j] = (indexPtr[j] < 0) ? (-indexPtr[j]) : (indexPtr[j] + 1);
        }

        return (vertices.size() > 0) && (elements.size() > 0);
      }
    }

    return 0;
  }
}