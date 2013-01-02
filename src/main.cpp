#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow foo;
    foo.show();
    return app.exec();
}
