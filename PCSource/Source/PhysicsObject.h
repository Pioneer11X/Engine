#pragma once

#include "Box2D\Box2D.h"
#include <string>

class PhysicsObject
{

public:

	PhysicsObject(b2World * _world, bool _isDynammic, float _posX, float _posY, float _sizeX, float _sizeY);

	b2Body * GetPhysicsBody();

	~PhysicsObject();

private:

	b2Body * physicsBodyPtr;
	b2World * world;

	bool isDynamic;
	float posX, posY, sizeX, sizeY;

};

