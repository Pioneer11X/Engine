//
//  Mesh.h
//  Engine
//
//  Created by Sravan Karuturi on 10/26/17.
//

#ifndef Mesh_h
#define Mesh_h

#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif // !GLEW_STATIC

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "BasicVertex.h"

using namespace std;

class Mesh {
public:
	/*  Mesh Data  */
	vector<BasicVertex> vertices;
	vector<uint32_t> indices;
	unsigned int VAO;

	/*  Functions  */
	// constructor
	Mesh(vector<BasicVertex> vertices, vector<uint32_t> indices)
	{
		this->vertices = vertices;
		this->indices = indices;

		// now that we have all the required data, set the vertex buffers and its attribute pointers.
		setupMesh();
	}

	~Mesh() {
		// Delete the stuff..
	}
    
    Mesh(BasicVertex * _vertices, uint16_t vertexCount, uint32_t * _indices, uint16_t indexCount){
        
        for ( uint16_t i = 0 ; i < vertexCount ; i++){
             this->vertices.push_back(_vertices[i]);
        }
        
        for ( uint16_t i = 0 ; i < indexCount ; i++){
            this->indices.push_back(_indices[i]);
        }
        
        setupMesh();
		
    }

	Mesh(char * _fileName) {
		
		std::ifstream obj(_fileName);

		if (!obj.is_open())
			return;

		std::vector<vec3> positions;
		std::vector<vec3> normals;
		std::vector<vec2> uvs;

		uint32_t vertCounter = 0;

		char chars[100];

		while (obj.good())
		{
			obj.getline(chars, 100);

			// Check the type of line
			if (chars[0] == 'v' && chars[1] == 'n')
			{
				// Read the 3 numbers directly into an XMFLOAT3
				vec3 norm;
				sscanf_s(
					chars,
					"vn %f %f %f",
					&norm.x, &norm.y, &norm.z);

				// Add to the list of normals
				normals.push_back(norm);
			}
			else if (chars[0] == 'v' && chars[1] == 't')
			{
				// Read the 2 numbers directly into an XMFLOAT2
				vec2 uv;
				sscanf_s(
					chars,
					"vt %f %f",
					&uv.x, &uv.y);

				// Add to the list of uv's
				uvs.push_back(uv);
			}
			else if (chars[0] == 'v')
			{
				// Read the 3 numbers directly into an XMFLOAT3
				vec3 pos;
				sscanf_s(
					chars,
					"v %f %f %f",
					&pos.x, &pos.y, &pos.z);

				// Add to the positions
				positions.push_back(pos);
			}
			else if (chars[0] == 'f')
			{
				// Read the face indices into an array
				unsigned int i[12];
				int facesRead = sscanf_s(
					chars,
					"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
					&i[0], &i[1], &i[2],
					&i[3], &i[4], &i[5],
					&i[6], &i[7], &i[8],
					&i[9], &i[10], &i[11]);

				// - Create the verts by looking up
				//    corresponding data from vectors
				// - OBJ File indices are 1-based, so
				//    they need to be adusted
				BasicVertex v1;
				// v1.
				v1.position = positions[i[0] - 1];
				v1.uv = uvs[i[1] - 1];
				v1.normal = normals[i[2] - 1];

				BasicVertex v2;
				v2.position = positions[i[3] - 1];
				v2.uv = uvs[i[4] - 1];
				v2.normal = normals[i[5] - 1];

				BasicVertex v3;
				v3.position = positions[i[6] - 1];
				v3.uv = uvs[i[7] - 1];
				v3.normal = normals[i[8] - 1];

				// The model is most likely in a right-handed space,
				// especially if it came from Maya.  We want to convert
				// to a left-handed space for DirectX.  This means we 
				// need to:
				//  - Invert the Z position
				//  - Invert the normal's Z
				//  - Flip the winding order
				// We also need to flip the UV coordinate since DirectX
				// defines (0,0) as the top left of the texture, and many
				// 3D modeling packages use the bottom left as (0,0)

				//// Flip the UV's since they're probably "upside down"
				//v1.uv.y = 1.0f - v1.uv.y;
				//v2.uv.y = 1.0f - v2.uv.y;
				//v3.uv.y = 1.0f - v3.uv.y;

				//// Flip Z (LH vs. RH)
				//v1.position.z *= -1.0f;
				//v2.position.z *= -1.0f;
				//v3.position.z *= -1.0f;

				//// Flip normal Z
				//v1.normal.z *= -1.0f;
				//v2.normal.z *= -1.0f;
				//v3.normal.z *= -1.0f;

				// Add the verts to the vector (flipping the winding order)
				vertices.push_back(v1);
				vertices.push_back(v3);
				vertices.push_back(v2);

				// Add three more indices
				indices.push_back(vertCounter); vertCounter += 1;
				indices.push_back(vertCounter); vertCounter += 1;
				indices.push_back(vertCounter); vertCounter += 1;

				// Was there a 4th face?
				if (facesRead == 12)
				{
					// Make the last vertex
					BasicVertex v4;
					v4.position = positions[i[9] - 1];
					v4.uv = uvs[i[10] - 1];
					v4.normal = normals[i[11] - 1];

					// Flip the UV, Z pos and normal
					// v4.uv.y = 1.0f - v4.uv.y;
					// v4.position.z *= -1.0f;
					// v4.normal.z *= -1.0f;

					// Add a whole triangle (flipping the winding order)
					vertices.push_back(v1);
					vertices.push_back(v4);
					vertices.push_back(v3);

					// Add three more indices
					indices.push_back(vertCounter); vertCounter += 1;
					indices.push_back(vertCounter); vertCounter += 1;
					indices.push_back(vertCounter); vertCounter += 1;
				}
			}
		}

		setupMesh();

	}

	// render the mesh
	void Draw(Shader shader)
	{
		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}

private:
	/*  Render data  */
	unsigned int VBO, EBO;

	/*  Functions    */
	// initializes all the buffer objects/arrays
	void setupMesh()
	{
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(BasicVertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), (void*)offsetof(BasicVertex, normal.x));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BasicVertex), (void*)offsetof(BasicVertex, uv.x));

		glBindVertexArray(0);
	}
};

#endif /* Mesh_h */
