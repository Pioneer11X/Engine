//
//  Game.cpp
//  Engine
//
//  Created by Sravan Karuturi on 10/24/17.
//

#pragma once
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

	// Allocate the vertex buffer memory

	int vertexSize = 8;

	int pointsSize = vertexSize * sizeof(BasicVertex);

	// BasicVertex * vertexData = new BasicVertex[4];

	std::vector<BasicVertex> vertexData = std::vector<BasicVertex>();
	vertexData.push_back(BasicVertex(-3.f, -3.f, 3.f, 1.f, 0.f, 0.f, 0.f, 1.f));
	vertexData.push_back(BasicVertex(3.f, -3.f, 3.f, 0.f, 1.f, 0.f, 1.f, 1.f));
	vertexData.push_back(BasicVertex(-3.f, 3.f, 3.f, 0.f, 0.f, 1.f, 0.f, 0.f));
	vertexData.push_back(BasicVertex(3.f, 3.f, 3.f, 0.5f, 0.5f, 0.5f, 1.f, 0.f));
	vertexData.push_back(BasicVertex(-3.f, -3.f, -3.f, 1.f, 0.f, 1.f, 1.f, 0.f));
	vertexData.push_back(BasicVertex(3.f, -3.f, -3.f, 0.f, 1.f, 1.f, 0.f, 0.f));
	vertexData.push_back(BasicVertex(-3.f, 3.f, -3.f, 0.f, 0.f, 0.f, 1.f, 1.f));
	vertexData.push_back(BasicVertex(3.f, 3.f, -3.f, 0.5f, 0.5f, 0.5f, 0.f, 1.f));

	std::vector<uint32_t> indexData = std::vector<uint32_t>();
	indexData.push_back(0);
	indexData.push_back(1);
	indexData.push_back(2);
	indexData.push_back(1);
	indexData.push_back(3);
	indexData.push_back(2);

	indexData.push_back(1);
	indexData.push_back(5);
	indexData.push_back(7);
	indexData.push_back(7);
	indexData.push_back(3);
	indexData.push_back(1);

	indexData.push_back(2);
	indexData.push_back(6);
	indexData.push_back(4);
	indexData.push_back(4);
	indexData.push_back(0);
	indexData.push_back(2);

	indexData.push_back(4);
	indexData.push_back(5);
	indexData.push_back(7);
	indexData.push_back(7);
	indexData.push_back(6);
	indexData.push_back(4);

	indexData.push_back(7);
	indexData.push_back(3);
	indexData.push_back(2);
	indexData.push_back(2);
	indexData.push_back(6);
	indexData.push_back(7);

	indexData.push_back(5);
	indexData.push_back(4);
	indexData.push_back(0);
	indexData.push_back(0);
	indexData.push_back(1);
	indexData.push_back(5);

	Mesh * m = new Mesh(vertexData,indexData);

	// meshes.push_back(m);

	// Entity * e = new Entity(m, vec3(10.0f, 0.0f, -35.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));
	Entity * e2 = new Entity(m, vec3(-1.0f, 0.0f, -35.f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));

	std::vector<Entity*> entities;
	std::vector<Mesh*> meshes;

	// entities.push_back(e);
	entities.push_back(e2);

	meshes.push_back(m);

	this->scene = new Scene(entities, meshes);

}

void Game::handleUserEvents(){
    
}

void Game::Cleanup(){

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );

	// delete playerEntity;

	//for (std::vector<Entity *>::iterator it = platformEntites.begin(); it != platformEntites.end(); it++) {
	//	delete (*it);
	//}

	for (std::vector<Mesh *>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		delete (*it);
	}

	//if (playerMesh)
	//	delete playerMesh;

	//if (blockMesh)
	//	delete blockMesh;
    
    //    return EXIT_SUCCESS;
    
}
