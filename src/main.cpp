//spaceraft
#include <viewport.h>

//sdl
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

//std
#include <iostream>
#include <memory>

int main(int argc, char** argv) {
    SDL_Init(0);
    auto v = std::make_unique<Viewport>();
    bool running = true;
    while (running) {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q)
                    running = false;
                break;
            default:
                break;
        }
    }
    SDL_Quit();
}