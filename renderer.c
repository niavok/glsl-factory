#include <SDL/SDL.h>

#include "renderer.h"


RendererDescriptor* renderer_init() {
    RendererDescriptor* renderer;
    SDL_Surface* screen;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

    SDL_Flip(screen);
    renderer = malloc(sizeof(RendererDescriptor));
    
    return renderer;
}

void renderer_run(RendererDescriptor* gui) {
    char running = 1;
    SDL_Event event;

    while (running)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                running = 0;
        }
    }

}

void renderer_destroy(RendererDescriptor* gui) {
    SDL_Quit();
}
