#include "UserInput.h"
#include "SDL_keycode.h"
#include "stdio.h"
#include "SDL.h"

struct GameStatus gameStatus;
void UpdateUserInput()
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) ){

        /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
        
        switch( event.type ){
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        gameStatus.run = 0;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                break;
            case SDL_QUIT:
                gameStatus.run = 0;
                printf("Quiting\n");
                break;
            default:
                break;
        }
    }

}
