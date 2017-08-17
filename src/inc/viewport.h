//
// Created by Russell Blickhan on 7/28/17.
//

#pragma once

//bgfx
#include <bgfx/bgfx.h>

//sdl
#include <SDL2/SDL.h>

//std
#include <memory>
#include <array>

class Viewport {
public:
    Viewport();

    ~Viewport() { bgfx::shutdown(); }

    void render() {bgfx::touch(0);}

private:
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> m_window;
};