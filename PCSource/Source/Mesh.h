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
        // We no longer need the input vertices and indices pointer.
		// Delete them.
		delete _vertices;
		delete _indices;
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
