#pragma once

#include "Shader.h"
#include "Scene.h"
#include "Camera.h"

#include <vector>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

// GLFW
#include <GLFW/glfw3.h>

class RenderManager {


private:

	unsigned int transformLoc;

	float ScreenWidth;
	float ScreenHeight;

	int realScreenWidth = 0, realScreenHeight = 0;

public:

	GLFWwindow * window;

	Shader playerShader;
	Shader blockShader;

	Camera camera;

	// Entity * playerEntity;
	std::vector<Entity *> scene;

	Scene * glScene;

	RenderManager(float width, float height) {

		ScreenWidth = width;
		ScreenHeight = height;

		// Init calls for OpenGL.
		
		// Init GLFW
		glfwInit();

		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Create a GLFWwindow object that we can use for GLFW's functions
		window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Engine", nullptr, nullptr);

		if (nullptr == window)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();

			// return EXIT_FAILURE;
			return;
		}

		glfwGetFramebufferSize(window, &realScreenWidth, &realScreenHeight);

		glfwMakeContextCurrent(window);

		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;
		// Initialize GLEW to setup the OpenGL Function pointers
		if (GLEW_OK != glewInit())
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			// return EXIT_FAILURE;
			return;
		}


	};

	~RenderManager() {

	};

	void Init(Scene * scene)  {

		glViewport(0, 0, realScreenWidth, realScreenHeight);

		glDepthRangef(0.1f, 10.0f);

        
#ifdef __APPLE__
        
        playerShader.Init("../../PCSource/Source/Shaders/core.vs", "../../PCSource/Source/Shaders/core.frag");
        blockShader.Init("../../PCSource/Source/Shaders/platform.vs", "../../PCSource/Source/Shaders/platform.frag");

#else
        playerShader.Init("../Source/Shaders/core.vs", "../Source/Shaders/core.frag");
        blockShader.Init("../Source/Shaders/platform.vs", "../Source/Shaders/platform.frag");

#endif
        
		camera = Camera();

		glScene = scene;

		return;

	}

	void drawScene() {
		
		playerShader.Use();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		for (std::vector<Entity *>::iterator it = glScene->entities.begin(); it != glScene->entities.end(); it++) {
			drawEntity(*it, blockShader);
		}

		glfwSwapBuffers(window);

	}

	void drawEntity(Entity * e, Shader _shader) {
		e->RecalculateWorldMatrix();

		// Set it in there
		// _shader.setMat4("transform", glm::transpose(e->worldMatrix));
		_shader.setMat4("transform", e->worldMatrix);
		_shader.setMat4("projection", glm::perspective(glm::radians(camera.Zoom), float(ScreenHeight / ScreenWidth), 0.1f, 100.0f));
		_shader.setMat4("view", camera.GetViewMatrix());
		
		// Per Entity Draw Call.
		for (std::vector<Mesh *>::iterator it = e->meshes.begin(); it != e->meshes.end(); it++) {

			glBindVertexArray((*it)->VAO);
			glDrawElements(GL_TRIANGLES, (*it)->indices.size(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);

			// always good practice to set everything back to defaults once configured.
			glActiveTexture(GL_TEXTURE0);

		}

	}

};
