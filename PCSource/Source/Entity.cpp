#include "Entity.h"


Entity::Entity(std::vector<Mesh *> _meshes, vec3 _trans, vec3 _rot, vec3 _scal)
{

	meshes = _meshes;

	translation = _trans;
	rotation = _rot;
	scaling = _scal;

	
	///*Physics Stuff*/

	//b2BodyDef bodyDef;
	//if (isDynamic) {
	//	bodyDef.type = b2_dynamicBody;
	//}
	//bodyDef.position.Set(translation.x * 100.0f, translation.y * 100.0f);

	//physicsBody = (*world).CreateBody(&bodyDef);

	///*Physics Stuff End*/



	worldMatrix = glm::mat4(1.0f);

	dirty = true;

}

Entity::Entity(Mesh * _mesh, vec3 _trans, vec3 _rot, vec3 _scal)
{

	// Make a single element Mesh and pass it to the constructor
	std::vector<Mesh *> _meshes;
	_meshes.push_back(_mesh);

	meshes = _meshes;
	translation = _trans;
	rotation = _rot;
	scaling = _scal;

	///*Physics Stuff*/

	//b2BodyDef bodyDef;
	//if (isDynamic) {
	//	bodyDef.type = b2_dynamicBody;
	//}
	//bodyDef.position.Set(translation.x * 100.0f, translation.y * 100.0f);

	//physicsBody = (*world).CreateBody(&bodyDef);

	///*Physics Stuff End*/

	dirty = true;

}

Entity::~Entity()
{
}

void Entity::MoveRight(float factor)
{

	// TODO: This is frame dependant. We need an independant timer to get a fixed rate.
	translation.x += factor * 0.001f;
	dirty = true;


}

void Entity::MoveUp(float factor)
{
	// TODO: This is frame dependant. We need an independant timer to get a fixed rate.
	translation.y += factor * 0.001f;
	dirty = true;
}

void Entity::RotateZ(float factor)
{

	/*rotation.setZ(rotation.getZ() + factor * 0.001f);*/
	rotation.z += factor * 0.001f;
	dirty = true;

}

void Entity::RotateY(float factor)
{
	rotation.y += factor * 0.001f;
	dirty = true;
}

void Entity::ScaleBumpy()
{
	/*scaling.setX(scaling.getX() + 0.05f);*/
	scaling.x += 0.05f;
	dirty = true;

}

void Entity::RecalculateWorldMatrix()
{

	if (dirty) {

		worldMatrix = transMatrix = rotatMatrix = scaleMatrix = glm::mat4(1.0f);

		transMatrix = glm::translate(transMatrix, translation);
		rotatMatrix = glm::rotate(rotatMatrix, rotation.z, vec3(0.0f, 0.0f, 1.0f));
		rotatMatrix = glm::rotate(rotatMatrix, rotation.y, vec3(0.0f, 1.0f, 0.0f));
		rotatMatrix = glm::rotate(rotatMatrix, rotation.x, vec3(1.0f, 0.0f, 0.0f));
		scaleMatrix = glm::scale(scaleMatrix, scaling);

		worldMatrix = transMatrix * rotatMatrix * scaleMatrix;
		// worldMatrix = scaleMatrix * rotatMatrix * transMatrix;

		dirty = false;

	}

}

//void Entity::Draw(Shader _shader, Camera gameCamera)
//{
//
//	RecalculateWorldMatrix();
//
//	// Draw the meshes with the transformation of the Entity
//	unsigned int tranformLoc = glGetUniformLocation(_shader.Program, "transform");
//
//	// glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, glm::value_ptr(glm::transpose(worldMatrix)));
//	glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, glm::value_ptr(glm::transpose(worldMatrix)));
//    
//    // camera/view transformation
//	// pass projection matrix to shader (note that in this case it could change every frame)
//	glm::mat4 projection = glm::perspective(glm::radians(gameCamera.Zoom), float(800/600), 0.1f, 100.0f);
//	_shader.setMat4("projection", projection);
//
//	// camera/view transformation
//	glm::mat4 view = gameCamera.GetViewMatrix();
//	_shader.setMat4("view", view);
//
//	for (std::vector<Mesh *>::iterator it = meshes.begin(); it != meshes.end(); it++) {
//
//		((Mesh *)(*it))->Draw(_shader);
//
//	}
//
//}
