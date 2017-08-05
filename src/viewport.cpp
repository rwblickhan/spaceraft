//
// Created by Russell Blickhan on 7/28/17.
//

//spaceraft
#include <viewport.h>

//bgfx
#include <bgfx/platform.h>

//sdl
#include <SDL2/SDL_syswm.h>

Viewport::Viewport()
    : m_window(SDL_CreateWindow("Main Window", 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL),
               [](SDL_Window* w){SDL_DestroyWindow(w);})
{
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    SDL_GetWindowWMInfo(m_window.get(), &wmi);
    bgfx::PlatformData pd;
#if BX_PLATFORM_LINUX
    pd.ndt = wmi.info.x11.display;
    pd.nwh = (void*)(uintptr_t)wmi.info.x11.window;
#elif BX_PLATFORM_OSX
    pd.nwh = wmi.info.cocoa.window;
#elif BX_PLATFORM_WINDOWS
    pd.nwh = wmi.info.win.window;
#endif
    bgfx::setPlatformData(pd);
    bgfx::init(bgfx::RendererType::OpenGL);
    bgfx::reset(640, 480);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x00000000);
    bgfx::setViewRect(0, 0, 0, 640, 480);
    bgfx::touch(0);
}