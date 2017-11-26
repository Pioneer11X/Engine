#pragma once
#include "BasicVertex.h"

#include "Mesh.h"

#include "Shader.h"

#include <vector>
#include "Camera.h"

#include "Physics.h"

using namespace std;
using namespace glm;

class Entity
{

	mat4x4 transMatrix;
	mat4x4 rotatMatrix;
	mat4x4 scaleMatrix;

public:

	std::vector<Mesh *> meshes;

	mat4x4 worldMatrix;

	vec3 translation;
	vec3 rotation;
	vec3 scaling;

	bool dirty;

public:

	Entity(std::vector<Mesh *> _meshes, vec3 _trans, vec3 _rot, vec3 _scal);
	Entity(Mesh * _mesh, vec3 _trans, vec3 _rot, vec3 _scal);
	~Entity();

	void MoveRight(float factor);
	void MoveUp(float factor);
	void MoveRightUsingMatrix(float factor);
	void MoveUpUsingMatrix(float factor);

	void RotateZ(float factor);
	void RotateY(float factor);

	void ScaleBumpy();

	void RecalculateWorldMatrix();

	// void GLDraw(GL_Shader _shader, Camera gameCamera);
	// void Draw(Shader _shader, Camera gameCamera);

	void inline setTranslate(vec3 _translate) { translation = _translate; dirty = true; }

};
