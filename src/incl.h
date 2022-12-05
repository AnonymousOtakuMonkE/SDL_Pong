#ifndef incl
#define incl


    // required libraries
    #include <stdio.h>
    #include "include/SDL2/SDL.h"
    #include "include/SDL2/SDL_image.h"
    #include "include/SDL2/SDL_keyboard.h"
    #include "include/SDL2/SDL_keycode.h"
    #include "include/SDL2/SDL_scancode.h"


    // Global constants
    #define WINDOW_WIDTH 1280
    #define WINDOW_HEIGHT 720


    // Entity struct
    typedef struct {
        SDL_Texture* tex;
        unsigned int x, y, w, h;
    } entity, player, ball;


    // Global variables
    SDL_Window* window;
    SDL_Renderer* renderer;
    player* p1;
    player* p2;
    ball* b;
    const Uint8* keyboardState;
    

    // Function declarations
    void Init();
    void Exit();
    void CheckEvents();


    // Function definitions
    void Init(void){
    // Initialize the window, renderer, SDL_IMG and entities

        if (!(SDL_Init(SDL_INIT_EVERYTHING) == 0)){
            printf("ERROR : Couldnt init SDL : %s \n", SDL_GetError());
            return;
        }

        window = SDL_CreateWindow("window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_ALLOW_HIGHDPI);

        if (!window){
            printf("ERROR : Couldnt create window : %s \n", SDL_GetError());
            return;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (!renderer){
            printf("ERROR : Couldnt create renderer : %s \n", SDL_GetError());
            return;
        }

        if (!(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)){
            printf("ERROR : Couldnt init SDL_IMG : %s \n", SDL_GetError());
            return;
        }


        p1 = (player*) malloc(sizeof(player));
        p2 = (player*) malloc(sizeof(player));
        b = (ball*) malloc(sizeof(ball));


        SDL_Surface* batImg = IMG_Load("src/images/bat.png");
        SDL_Surface* ballImg = IMG_Load("src/images/ball.png");
        p1->tex = SDL_CreateTextureFromSurface(renderer, batImg);
        p2->tex = SDL_CreateTextureFromSurface(renderer, batImg);
        b->tex = SDL_CreateTextureFromSurface(renderer, ballImg);


        // If any one of the textures is NULL, then initialization failed
        if (!(p1->tex && p2->tex && b->tex)){
            printf("ERROR : Couldnt make entitites %s \n", SDL_GetError());
            SDL_FreeSurface(batImg);
            SDL_FreeSurface(ballImg);
            SDL_DestroyTexture(p1->tex);
            SDL_DestroyTexture(p2->tex);
            SDL_DestroyTexture(b->tex);
            p1 = NULL;
            p2 = NULL;
            b = NULL;
            return;
        }


        // Assign the width and height to the entities
        p1->w = batImg->w;
        p2->w = batImg->w;
        b->w = ballImg->w;

        p1->h = batImg->h;
        p2->h = batImg->h;
        b->h = ballImg->h;


        // Put the entities in their correct original places
        p1->x = 10;
        p1->y = 10;
        p2->x = WINDOW_WIDTH - 10 - p2->w;
        p2->y = WINDOW_HEIGHT - 10 - p2->h;
        b->x = WINDOW_WIDTH / 2 - b->w;
        b->y = WINDOW_HEIGHT / 2 - b->h;


        // Also get they keyboard state
        keyboardState = SDL_GetKeyboardState(NULL);


        // Free the surfaces since they are not requied anymore
        SDL_FreeSurface(batImg);
        SDL_FreeSurface(ballImg);
    }


    void Exit(){
    // Exit function for both successful and unsuccessful quits
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_DestroyTexture(p1->tex);
        SDL_DestroyTexture(p2->tex);
        SDL_DestroyTexture(b->tex);

        free(p1);
        free(p2);
        free(b);

        IMG_Quit();
        SDL_Quit();

        renderer = NULL;
        window = NULL;
    }


    void CheckEvents(){
        // Runs the event loop
        SDL_Event event;
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
					Exit();
					return;
			}

            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
                Exit();
                return;
            }
		}
    }


#endif
