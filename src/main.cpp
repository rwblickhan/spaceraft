//spaceraft
#include <viewport.h>

//std
#include <iostream>
#include <memory>

//qt
#include <QApplication>
#include <QMainWindow>

int main(int argc, char** argv) {
    std::unique_ptr<QApplication> app(new QApplication(argc, argv));
    std::unique_ptr<QMainWindow> mw(new QMainWindow());
    mw->show();
    std::unique_ptr<Viewport> v(new Viewport(mw.get()));
    v->show();
    return app->exec();
}