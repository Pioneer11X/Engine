//
//  Game.cpp
//  Engine
//
//  Created by Sravan Karuturi on 10/24/17.
//

// #pragma once
#include <stdio.h>
#include <iostream>
#include "Game.h"


using namespace std;

Game::Game(){
    
    // Window dimensions
    WIDTH = 800;
    HEIGHT = 600;

	window = nullptr;

}

void Game::Init(){
   
    
	renderer = new RenderManager(WIDTH, HEIGHT);

	this->window = renderer->window;

	InitScene();

	renderer->Init(scene);

	gameCamera = Camera(vec3(0.0f, 0.0f, 3.0f));
   
    // return EXIT_SUCCESS;
	return;
    
}

void Game::Update(){

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Timer logic
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		renderer->drawScene();
		
		processInput(window);
	}
    
}


void Game::Draw(){
    
}

void Game::processInput(GLFWwindow * window)
{
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		gameCamera.Position.z += 1;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		scene->entities[0]->RotateY(50);
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		scene->entities[0]->RotateZ(50);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		scene->entities[0]->rotation.x += 0.1;
		scene->entities[0]->dirty = true;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		scene->entities[0]->RotateY(-50);
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		scene->entities[0]->RotateZ(-50);
	}
		

	joyStickNumber = glfwJoystickPresent(GLFW_JOYSTICK_1);

	// std::cout << joyStickNumber << std::endl;

	if (joyStickNumber != 0) {

		int axesCount;
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

		// playerEntity->MoveRight(axes[0]);
        
        int buttonCount;
        const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
        
#ifdef _WIN32
		// playerEntity->MoveUp(axes[1]);
		
		if (axes[3] > 0.2f) {
			gameCamera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
		}
		else if (axes[3] < -0.2f) {
			gameCamera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		}

		if (axes[3] > 0.0f) {
			scene->entities[0]->RotateZ(100.0f);
		}

		gameCamera.ProcessMouseMovement(axes[2] * 5.0f, 0, GL_FALSE);

        // Press B to Close the Application for Now.
        if (GLFW_PRESS == buttons[1]) {
            glfwSetWindowShouldClose(window, true);
        }

		// Up
		if (GLFW_PRESS == buttons[10]) {
			scene->entities[0]->RotateZ(-100.0f);
		}

		// Down
		if (GLFW_PRESS == buttons[12]) {
			scene->entities[0]->RotateZ(100.0f);
		}

		// Left
		if (GLFW_PRESS == buttons[13]) {
			scene->entities[0]->RotateY(-100.0f);
		}

		// Right
		if (GLFW_PRESS == buttons[11]) {
			scene->entities[0]->RotateY(100.0f);
		}



#endif

		
        
#ifdef __APPLE__
        scene->entities[0]->MoveUp( -1.0f * axes[1]);
        // Press 'O' to Close the Application for Now.
        if (GLFW_PRESS == buttons[2]) {
            glfwSetWindowShouldClose(window, true);
        }
#endif




	}

}

void Game::InitScene()
{

	Mesh * m = new Mesh("cube.obj");
	Mesh * planeMesh = new Mesh("plane.obj");

	Entity * e = new Entity(m, vec3(-1.0f, 0.0f, -35.f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));
	Entity * planeEnt = new Entity(planeMesh, vec3(-1.0f, -5.0f, -35.f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));

	e->AddPhysicsBody(&world, true);
	planeEnt->AddPhysicsBody(&world, false);

	std::vector<Entity*> entities;
	std::vector<Mesh*> meshes;

	entities.push_back(e);
	entities.push_back(planeEnt);

	meshes.push_back(m);
	meshes.push_back(planeMesh);

	this->scene = new Scene(entities, meshes);

}

void Game::handleUserEvents(){
    // TODO: Populate this with the GLFW commands.
}

Game::~Game()
{
}

void Game::Cleanup(){

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );

	delete scene;
	delete renderer;
    
}
