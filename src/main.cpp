#include <QtGui/QApplication>
#include "AdaptiveControl.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    AdaptiveControl foo;
    foo.show();
    return app.exec();
}
