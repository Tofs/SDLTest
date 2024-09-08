#include "stdio.h"
#include "SDL.h"

SDL_Window* window;
SDL_Renderer* renderer;

int init()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }
  else {
    printf("SDL started\n");
  }

  window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  if (window == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    return 1;
  }
  else {
    printf("SDL Window created\n");
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    return 1;
  }
  else {
    printf("SDL Renderer created\n");
  }

  return 0;
}

struct Possition {
  int x;
  int y;
};

struct RenderObject {
  int sizeX;
  int sizeY;
};

struct Object {
  struct Possition pos;
  struct Possition target;
  struct RenderObject render;
};

struct Object objects[100];

void Render()
{
  struct Object renderObject = objects[0];
 
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_Rect rect;
  rect.x = renderObject.pos.x-renderObject.render.sizeX/2;
  rect.y = renderObject.pos.y-renderObject.render.sizeY/2;
  rect.w = renderObject.render.sizeX;
  rect.h = renderObject.render.sizeY;
  SDL_RenderDrawRect(renderer, &rect);


  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderDrawLine(renderer,
                     renderObject.pos.x,
                     renderObject.pos.y,
                     renderObject.target.x,
                     renderObject.target.y);


  SDL_RenderPresent(renderer);
}

void Update()
{
  struct Object* renderObject = &objects[0];
  renderObject->pos.x++;
}

void mainLoop()
{
  objects[0].pos.x = 0;
  objects[0].pos.y = 0;
  objects[0].target.x = 100;
  objects[0].target.y = 200;
  objects[0].render.sizeX = 10;
  objects[0].render.sizeY = 10;
  int run = 1;
  while (run)
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);


    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          printf("Quiting\n");
          run = 0;
          break;

        default:
          break;
      }
    }

    // Render
    Render();

    // Update possition
    Update();
    

    SDL_Delay(1000/60);
  }
}

void shutdown()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char* argv[])
{
  init();
  mainLoop();
  shutdown();

  
  return 0;
}

int WinMain(int argc, char* argv[]) 
{
  return main(argc, argv);
}
