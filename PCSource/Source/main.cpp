#include <iostream>
#include <stdio.h>

#include "MapLoader.h"

#if defined(_WIN32)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// The MAIN function, from here we start the application and run the game loop
int main( )
{

#if defined(_WIN32)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	
	Game * glGame = new Game();

	glGame->Init();

    glGame->Update();
    
    glGame->Cleanup();

	delete glGame;
    
    return EXIT_SUCCESS;
    
}




