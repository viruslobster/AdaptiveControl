#include <QtGui/QApplication>
#include "mainwindow.h"
#include <ctime> 
#include <cstdlib>


int main(int argc, char** argv) {
    srand((unsigned)time(0));
    QApplication app(argc, argv);
    MainWindow foo;
    foo.show();
    return app.exec();
}
