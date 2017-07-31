//spaceraft
#include <viewport.h>

//std
#include <iostream>
#include <memory>

//qt
#include <QApplication>
#include <QMainWindow>

int main(int argc, char** argv) {
    std::unique_ptr<QApplication> app(std::make_unique<QApplication>(argc, argv));
    std::unique_ptr<QMainWindow> mw(std::make_unique<QMainWindow>());
    mw->show();
    std::unique_ptr<Viewport> v(std::make_unique<Viewport>(mw.get()));
    v->show();
    return app->exec();
}