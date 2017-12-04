#include "PhysicsObject.h"
#include <iostream>

PhysicsObject::PhysicsObject(b2World * _world, bool _isDynammic, float _posX, float _posY, float _sizeX, float _sizeY) : 
	world(_world), isDynamic(_isDynammic), posX(_posX), posY(_posY), sizeX(_sizeX), sizeY(_sizeY)
{

	if (nullptr == _world) {
		std::cout << "Error loading the Physics World" << std::endl;
	}

	b2BodyDef PhysicsBodyDef;
	if (isDynamic) {
		PhysicsBodyDef.type = b2_dynamicBody;
	}
	PhysicsBodyDef.position.Set(posX, posY);

	physicsBodyPtr = (*world).CreateBody(&PhysicsBodyDef);

	b2PolygonShape PhysicsBox;
	PhysicsBox.SetAsBox(sizeX, sizeY);

	b2FixtureDef Fixdef;
	Fixdef.shape = &PhysicsBox;
	Fixdef.density = 1.0f;
	Fixdef.friction = 0.3f;

	physicsBodyPtr->CreateFixture(&Fixdef);

}

b2Body * PhysicsObject::GetPhysicsBody()
{
	return physicsBodyPtr;
}

PhysicsObject::~PhysicsObject()
{
}
