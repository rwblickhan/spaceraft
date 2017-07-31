//
// Created by Russell Blickhan on 7/28/17.
//

#pragma once

#include <QWidget>

#include <bgfx/bgfx.h>

class Viewport : public QWidget {
public:
    Viewport(QWidget* parent)
            : QWidget(parent)
    {
        initBGFX();
    }

    ~Viewport() {
        bgfx::shutdown();
    }

private:
    void initBGFX();

};