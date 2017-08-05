#!/bin/sh
git clone https://github.com/JoshuaBrookover/bgfx.cmake.git && cd bgfx.cmake && git submodule init && git submodule update
cd .. && mkdir build && cd build && cmake .. && make
