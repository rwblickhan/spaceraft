#!/bin/sh
mkdir deps && cd deps
git clone https://github.com/JoshuaBrookover/bgfx.cmake.git && cd bgfx.cmake && git submodule init && git submodule update
cd .. && git clone https://github.com/g-truc/glm.git
cd .. && mkdir build && cd build && cmake .. && make
