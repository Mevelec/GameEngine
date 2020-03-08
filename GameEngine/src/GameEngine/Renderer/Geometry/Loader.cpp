#include "hzpch.h"
#include "Loader.h"

namespace GameEngine {
	const bool Loader::loadOBJ(const char* path,
		std::vector < glm::vec3 >& out_vertices,
		std::vector < glm::vec2 >& out_uvs,
		std::vector < glm::vec3 >& out_normals,
		std::vector < int >& out_indices

	)
	{
		std::ifstream in(path, std::ios::in);
		if (!in)
		{
			GE_ASSERT(false, "Could not open the file {0}", path)
				return false;

		}

		std::string line;
		while (std::getline(in, line))
		{
			//check v for vertices
			if (line.substr(0, 2) == "v ") {
				std::istringstream v(line.substr(2));
				glm::vec3 vert;
				double x, y, z;
				v >> x; v >> y; v >> z;
				vert = glm::vec3(x, y, z);
				out_vertices.push_back(vert);
			}
			//check for texture co-ordinate
			else if (line.substr(0, 2) == "vt") {

				std::istringstream v(line.substr(3));
				glm::vec2 tex;
				int U, V;
				v >> U; v >> V;
				tex = glm::vec2(U, V);
				out_uvs.push_back(tex);
			}
			//check for normals
			else if (line.substr(0, 2) == "vn") {

				std::istringstream v(line.substr(2));
				glm::vec3 norm;
				double x, y, z;
				v >> x; v >> y; v >> z;
				norm = glm::vec3(x, y, z);
				out_normals.push_back(norm);
			}
			//check for faces
			else if (line.substr(0, 2) == "f ") {
				int S1a, S1b, S1c, S2a, S2b, S2c, S3a, S3b, S3c;

				const char* chh = line.c_str();
				sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &S1a, &S1b, &S1c, &S2a, &S2b, &S2c, &S3a, &S3b, &S3c); //here it read the line start with f and store the corresponding values in the variables

				S1a--; S1b--; S1c--;
				S2a--; S2b--; S2c--;
				S3a--; S3b--; S3c--;

				out_indices.push_back(S1a);
				out_indices.push_back(S1b);
				out_indices.push_back(S1c);

				out_indices.push_back(S2a);
				out_indices.push_back(S2b);
				out_indices.push_back(S2c);

				out_indices.push_back(S3a);
				out_indices.push_back(S3b);
				out_indices.push_back(S3c);
			}
		}
	}
}