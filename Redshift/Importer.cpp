#include <fstream>

#include <Redshift/World.h>
#include <Redshift/Importer.h>

#include <Redshift/Utils/FileReader.h>

#include <Vendor/OpenFbx/ofbx.h>

///////////////////////////////////////////////////////////
// Importer implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  U8 Importer::LoadFbx(World* world, std::filesystem::path const& fbxFile)
  {
    std::vector<U8> bytes{};

    if (FileReader::ReadBytes(bytes, fbxFile.string()))
    {
      ofbx::IScene* scene{ ofbx::load(&bytes[0], (U32)bytes.size(), (U64)ofbx::LoadFlags::TRIANGULATE) };
      if (scene)
      {
        std::string baseName{ fbxFile.stem().string() + "_" };

        for (U32 i{}; i < (U32)scene->getMeshCount(); i++)
        {
          ofbx::Mesh const* mesh{ scene->getMesh(i) };

          ofbx::Geometry const* geometry{ mesh->getGeometry() };

          ofbx::Vec3 const* vertex{ geometry->getVertices() };
          ofbx::Vec3 const* normal{ geometry->getNormals() };
          ofbx::Vec2 const* uv{ geometry->getUVs() };
          ofbx::Vec4 const* color{ geometry->getColors() };
          ofbx::Vec3 const* tangent{ geometry->getTangents() };
          I32 const* index{ geometry->getFaceIndices() };

          std::vector<VertexPhysicalBased> vertexBuffer{};
          vertexBuffer.resize(geometry->getVertexCount());

          for (U32 j{}; j < (U32)geometry->getVertexCount(); j++)
          {
            if (vertex)  vertexBuffer[j].Position = R32V3{ vertex[j].x, vertex[j].y, vertex[j].z };
            if (normal)  vertexBuffer[j].Normal   = R32V3{ normal[j].x, normal[j].y, normal[j].z };
            if (uv)      vertexBuffer[j].Uv       = R32V2{ uv[j].x, uv[j].y };
            if (color)   vertexBuffer[j].Color    = R32V4{ color[j].x, color[j].y, color[j].z, color[j].w };
            if (tangent) vertexBuffer[j].Tangent  = R32V3{ tangent[j].x, tangent[j].y, tangent[j].z };
          }

          std::vector<U32> elementBuffer{};
          elementBuffer.resize(geometry->getIndexCount());

          for (U32 j{}; j < (U32)geometry->getIndexCount(); j++)
          {
            elementBuffer[j] = (index[j] < 0) ? (-index[j]) : (index[j] + 1);
          }

          Mesh& worldMesh{ world->GetMesh(baseName + std::string{ mesh->name }) };
          worldMesh.Destroy();
          worldMesh.Create(&vertexBuffer[0], (U32)vertexBuffer.size(), &elementBuffer[0], (U32)elementBuffer.size());

          for (U32 j{}; j < (U32)mesh->getMaterialCount(); j++)
          {
            ofbx::Material const* material{ mesh->getMaterial(j) };

            Material& worldMaterial{ world->GetMaterial(baseName + std::string{ material->name }) };

            worldMaterial.SetDiffuseColor(R32V3{ material->getDiffuseColor().r, material->getDiffuseColor().g, material->getDiffuseColor().b });
            worldMaterial.SetSpecularColor(R32V3{ material->getSpecularColor().r, material->getSpecularColor().g, material->getSpecularColor().b });
            worldMaterial.SetReflectionColor(R32V3{ material->getReflectionColor().r, material->getReflectionColor().g, material->getReflectionColor().b });
            worldMaterial.SetAmbientColor(R32V3{ material->getAmbientColor().r, material->getAmbientColor().g, material->getAmbientColor().b });
            worldMaterial.SetEmissiveColor(R32V3{ material->getEmissiveColor().r, material->getEmissiveColor().g, material->getEmissiveColor().b });

            worldMaterial.SetDiffuseFactor((R32)material->getDiffuseFactor());
            worldMaterial.SetSpecularFactor((R32)material->getSpecularFactor());
            worldMaterial.SetReflectionFactor((R32)material->getReflectionFactor());
            worldMaterial.SetShininess((R32)material->getShininess());
            worldMaterial.SetShininessExponent((R32)material->getShininessExponent());
            worldMaterial.SetAmbientFactor((R32)material->getAmbientFactor());
            worldMaterial.SetBumpFactor((R32)material->getBumpFactor());
            worldMaterial.SetEmissiveFactor((R32)material->getEmissiveFactor());

            for (U32 k{}; k < ofbx::Texture::TextureType::COUNT; k++)
            {
              ofbx::Texture const* texture{ material->getTexture((ofbx::Texture::TextureType)k) };
              if (texture)
              {
                U8* pixelBuffer{ (U8*)texture->getEmbeddedData().begin };
                U32 pixelBufferSize{ (U32)(texture->getEmbeddedData().end - texture->getEmbeddedData().begin) };

                if (pixelBuffer && pixelBufferSize > 0)
                {
                  Texture& worldTexture{ world->GetTexture(baseName + std::string{ texture->name }) };
                  worldTexture.Destroy();
                  worldTexture.Create(pixelBuffer, pixelBufferSize);
                }
              }
            }
          }
        }

        return 1;
      }
    }

    return 0;
  }
}