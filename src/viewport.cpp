//
// Created by Russell Blickhan on 7/28/17.
//

#include <viewport.h>
#include <bgfx/platform.h>

void Viewport::initBGFX() {
    bgfx::PlatformData pd;
    pd.nwh = (void*)winId();
    bgfx::setPlatformData(pd);
    bgfx::init(bgfx::RendererType::OpenGL);
}