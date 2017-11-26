#pragma once
#include <vector>
#include "Entity.h"

class Scene
{

public:

	std::vector<Entity *> entities;
	std::vector<Mesh *> meshes;

	Scene(std::vector<Entity *> _entities, std::vector<Mesh *> _meshes);
	~Scene();

	void add(std::vector<Entity*> _ents);
	void add(std::vector<Mesh*> _meshes);
};

