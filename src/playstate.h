#ifndef playstate
#define playstate

    #include "incl.h"

    // Constans
    #define PADDLE_VELOCITY 1


    // Function declarations
    void Render();
    void Update(float timeElasped);


    // Function definitions
	void Render(){
	// Clear the screen, render the players and the ball and refresh the screen
		SDL_Rect p1r = {p1->x, p1->y, p1->w, p1->h};
		SDL_Rect p2r = {p2->x, p2->y, p2->w, p2->h};
		SDL_Rect br = {b->x, b->y, b->w, b->h};

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, p1->tex, NULL, &p1r);
		SDL_RenderCopy(renderer, p1->tex, NULL, &p2r);
		SDL_RenderCopy(renderer, p1->tex, NULL, &br);

		SDL_RenderPresent(renderer);
	}


	void Update(float timeElasped){
	// Check for changes and keypresses

        if (keyboardState[SDL_SCANCODE_W]){
            // printf("Pressed W");
            if (p1->y <= 0)
                p1->y = 0;
            else
                p1->y = p1->y - PADDLE_VELOCITY*timeElasped;
        }
        if (keyboardState[SDL_SCANCODE_S]){
            // printf("Pressed S");
            if (p1->y + p1->h >= WINDOW_HEIGHT)
                p1->y = WINDOW_HEIGHT - p1->h;
            else
                p1->y = p1->y + PADDLE_VELOCITY*timeElasped;
        }
        if (keyboardState[SDL_SCANCODE_UP]){
            // printf("Pressed UP");
            if (p2->y <= 0)
                p2->y = 0;
            else
                p2->y = p2->y - PADDLE_VELOCITY*timeElasped;
        }
        if (keyboardState[SDL_SCANCODE_DOWN]){
            // printf("Pressed DOWN");
            if (p2->y + p2->h >= WINDOW_HEIGHT)
                p2->y = WINDOW_HEIGHT - p2->h;
            else
                p2->y = p2->y + PADDLE_VELOCITY*timeElasped;
        }

        // Clear the events buffer or undefined behaviour
        SDL_PumpEvents();

        printf("p1->y = %d, p2->y = %d \n", p1->y, p2->y);
	}


#endif