#include "hzpch.h"
#include "Loader.h"

#include <OBJ_Loader.h>

namespace GameEngine {
	const bool Loader::loadOBJ(const char* path,
		std::vector < float >& out_vertices,
		std::vector < glm::vec2 >& out_uvs,
		std::vector < glm::vec3 >& out_normals,
		std::vector < uint32_t >& out_indices
	)
	{
		// Initialize Loader
		objl::Loader Loader;

		// Load .obj File
		bool loadout = Loader.LoadFile(path);

		// Check to see if it loaded

		// If so continue
		if (loadout)
		{

			// Go through each loaded mesh and out its contents
			for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
			{
				// Copy one of the loaded meshes to be our current mesh
				objl::Mesh curMesh = Loader.LoadedMeshes[i];

				// Go through each vertex and print its number,
				//  position, normal, and texture coordinate
				for (int j = 0; j < curMesh.Vertices.size(); j++)
				{
					// Vertice Postion
					out_vertices.push_back(curMesh.Vertices[j].Position.X);
					out_vertices.push_back(curMesh.Vertices[j].Position.Y);
					out_vertices.push_back(curMesh.Vertices[j].Position.Z);

					out_vertices.push_back(1);
					out_vertices.push_back(1);
					out_vertices.push_back(1);
					out_vertices.push_back(1);

					out_vertices.push_back(1);
					out_vertices.push_back(1);

					out_vertices.push_back(1);

					/*
					// Vertice Normal
					out_vertices.push_back(curMesh.Vertices[j].Position.X);
					out_vertices.push_back(curMesh.Vertices[j].Position.Y);
					out_vertices.push_back(curMesh.Vertices[j].Position.Z);

					// Vertice TexCoordinate
					out_vertices.push_back(curMesh.Vertices[j].Position.X);
					out_vertices.push_back(curMesh.Vertices[j].Position.Y);
					out_vertices.push_back(curMesh.Vertices[j].Position.Z);
					*/
				}

				// Go through every 3rd index and print the
				//	triangle that these indices represent
				for (int j = 0; j < curMesh.Indices.size(); j += 3)
				{
					// indices
					out_indices.push_back(curMesh.Indices[j]);
					out_indices.push_back(curMesh.Indices[j+1]);
					out_indices.push_back(curMesh.Indices[j+2]);
				}
				/*
				// Print Material
				file << "Material: " << curMesh.MeshMaterial.name << "\n";
				file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
				file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
				file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
				file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
				file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
				file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
				file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
				file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
				file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
				file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
				file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
				file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";
				*/


			}
		}
		else
		{
			GE_ASSERT(false, "Could not parse file : {0}", path)
		}
		return true;
	}
}