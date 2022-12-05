#include "src/incl.h"
#include "src/playstate.h"


int main(int argc, char** argv){

    Init();
    // If any of p1, p2 or b is NULL, then initialization failed, so exit
    if (!(p1 && p2 && b)){
        Exit();
        return 1;
    }

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    int running = 1;
    Uint32 startTicks;
    Uint32 endTicks;
    float timeElasped = 0;
    while (running){
        startTicks = SDL_GetTicks();

        // Check for various events
        CheckEvents();

        // Update and render
		Update(timeElasped);
		Render();

        // Window and renderer should be null after calling Exit()
        // Check if Exit was called in CheckEvents, Update or Render
        if (!(window && renderer)){ 
				printf("Exiting");
				return 1;
		}

        // Change the endTicks and elaspedTime
        endTicks = SDL_GetTicks();
        timeElasped = endTicks - startTicks;
    }

    Exit();

    return 0;
}
