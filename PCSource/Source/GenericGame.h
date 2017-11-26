#pragma once
#include "Entity.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <limits>
#include "Camera.h"

class GenericGame
{

public:
    
    // Camera gameCamera;

	GenericGame();
	~GenericGame();

    // Abstracting the Class. The = 0 makes it pure virtual, which makes this class Abstract.
	virtual void Init() = 0;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void handleUserEvents() = 0;

};

