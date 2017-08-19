//
// Created by Russell Blickhan on 7/28/17.
//

//spaceraft
#include <viewport.h>

//bgfx
#include <bgfx/platform.h>

//sdl
#include <SDL2/SDL_syswm.h>

//glm
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

//std
#include <fstream>

namespace {
    static std::array<float, 24> g_icon = {
            -0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -0.1f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.1f, 0.0f, 0.0f, 0.0f
    };

    bgfx::ShaderHandle loadShader(const std::string& path) {
        std::fstream fin(path, std::ios::in | std::ios::binary);
        fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        fin.seekg(0, fin.end);
        const bgfx::Memory* buf = bgfx::alloc(fin.tellg());
        fin.seekg(fin.beg);

        fin.read(reinterpret_cast<char*>(buf->data), buf->size);
        return bgfx::createShader(buf);
    }
}

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
    //bgfx::FrameBufferHandle fb = bgfx::createFrameBuffer(pd.nwh, 640, 480);
    //bgfx::setViewFrameBuffer(1, fb);
    bgfx::setViewFrameBuffer(1, BGFX_INVALID_HANDLE);
    glm::mat4x4 modelMtx;
    bgfx::setTransform(&modelMtx);
    glm::mat4x4 viewMtx = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
    glm::mat4x4 projMtx = glm::perspective<float>(glm::half_pi<float>(), 640/480, 0.01, 1000);
    bgfx::setViewTransform(1, &viewMtx, &projMtx);
    bgfx::VertexDecl vertexDecl;
    vertexDecl.begin();
    vertexDecl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
    vertexDecl.add(bgfx::Attrib::Color0, 3, bgfx::AttribType::Float);
    vertexDecl.end();
    bgfx::VertexBufferHandle vBuf = bgfx::createVertexBuffer(bgfx::makeRef(g_icon.data(), g_icon.size()), vertexDecl);

#if BX_PLATFORM_OSX
    // create vertex shader
    bgfx::ShaderHandle vsShader = loadShader("/Users/rwblickhan/Developer/spaceraft/shadergen/shaders/metal/vs_basic.bin");
    //create fragment shader
    bgfx::ShaderHandle fsShader = loadShader("/Users/rwblickhan/Developer/spaceraft/shadergen/shaders/metal/vs_basic.bin");
#else
    bgfx::ShaderHandle vsShader = BGFX_INVALID_HANDLE;
    bgfx::ShaderHandle fsShader = BGFX_INVALID_HANDLE;
#endif
    bgfx::ProgramHandle basicProgram = bgfx::createProgram(vsShader, fsShader, true);
    bgfx::submit(1, basicProgram);
    bgfx::destroyVertexBuffer(vBuf);
    bgfx::destroyProgram(basicProgram);
}