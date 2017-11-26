#include "Scene.h"

Scene::Scene(std::vector<Entity*> _entities, std::vector<Mesh *> _meshes) : entities(_entities), meshes(_meshes)
{

}

Scene::~Scene()
{
	for (std::vector<Entity *>::iterator it = entities.begin(); it != entities.end(); ++it)
		if (nullptr != *it)
			delete *it;

	for (std::vector<Mesh *>::iterator it = meshes.begin(); it != meshes.end(); ++it)
		if (nullptr != *it)
			delete *it;
}

void Scene::add(std::vector<Entity*> _ents)
{

	if (entities.size() < 1) {
		entities = _ents;
	}
	else {
		entities.insert(entities.end(), _ents.begin(), _ents.end());
	}

}

void Scene::add(std::vector<Mesh*> _meshes)
{

	if (meshes.size() < 1) {
		meshes = _meshes;
	}
	else {
		meshes.insert(meshes.end(), _meshes.begin(), _meshes.end());
	}

}
