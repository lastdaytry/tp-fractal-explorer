#include <QApplication>

#include "mandelbrotwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FractalWidget widget;
    widget.show();
    return app.exec();
}
