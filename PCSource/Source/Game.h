//
//  Game.h
//  Engine
//
//  Created by Sravan Karuturi on 10/24/17.
//


#ifndef Game_h
#define Game_h

#include "RenderManager.h"
#include "Scene.h"

static b2Vec2 gravity(0.0f, -10.0f);
static b2World world(gravity);

class Game {
    
	GLFWwindow * window;

	void CreateMeshes();
    
    void Draw();

	void processInput(GLFWwindow *window);

	int joyStickNumber;

	float startTime = 0.0f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float currentFrame = 0.0f;

	void InitScene();
    
public:

	Scene * scene;

	RenderManager * renderer;

	GLuint WIDTH, HEIGHT;

	Mesh * playerMesh;
	Mesh * blockMesh;

	Camera gameCamera;

	// Entity * playerEntity;
	// std::vector<Entity * > platformEntites;
    
    Game();
    
    void Init();
    
    void Update();
    
    void Cleanup();
    
    void handleUserEvents();
    
    ~Game();
    
};

#endif /* Game_h */
