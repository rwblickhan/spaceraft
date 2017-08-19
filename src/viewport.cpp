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
#include <glm/gtc/matrix_transform.hpp>

//std
#include <fstream>

namespace {
    std::array<float, 24> g_icon = {
            -0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //left
            0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //right
            0.0f, 0.0f, -0.1f, 0.0f, 0.0f, 0.0f, //down
            0.0f, 0.0f, 0.1f, 0.0f, 0.0f, 0.0f   //up
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
    : m_window(SDL_CreateWindow("spaceraft", 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL),
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
    bgfx::setDebug(BGFX_DEBUG_TEXT);
    bgfx::reset(640, 480);
    bgfx::setViewClear(1, BGFX_CLEAR_COLOR, 0x000000ff);
    bgfx::setViewRect(1, 0, 0, 640, 480);
    bgfx::dbgTextPrintf(0, 1, 0x0f, "Hello world!");
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
    bgfx::setVertexBuffer(1, vBuf);
    bgfx::setState(BGFX_STATE_DEFAULT);
    // create vertex shader
    bgfx::ShaderHandle vsShader = loadShader("/Users/rwblickhan/Developer/spaceraft/shadergen/shaders/glsl/vs_basic.bin");
    //create fragment shader
    bgfx::ShaderHandle fsShader = loadShader("/Users/rwblickhan/Developer/spaceraft/shadergen/shaders/glsl/fs_basic.bin");
    bgfx::ProgramHandle basicProgram = bgfx::createProgram(vsShader, fsShader, true);
    bgfx::submit(1, basicProgram);
    bgfx::frame();
    bgfx::destroy(vBuf);
    bgfx::destroy(basicProgram);
}