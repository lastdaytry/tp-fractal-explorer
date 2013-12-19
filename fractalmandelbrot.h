#ifndef FRACTALMANDELBROT_H
#define FRACTALMANDELBROT_H

#include "fractal.h"

class fractalMandelbrot : public Fractal
{
     Q_OBJECT

public:
    fractalMandelbrot(QObject *parent = 0);
    ~fractalMandelbrot();
    void render(double centerX, double centerY, double scaleFactor,
                              QSize resultSize);
    void run();
};

#endif // FRACTALMANDELBROT_H
