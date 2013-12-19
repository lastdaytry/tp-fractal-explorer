#ifndef FRACTALTRICORN_H
#define FRACTALTRICORN_H

#include "fractal.h"

class fractalTricorn : public Fractal
{
     Q_OBJECT

public:
    fractalTricorn(QObject *parent = 0);
    ~fractalTricorn();
    void render(double centerX, double centerY, double scaleFactor,
                              QSize resultSize);
    void run();
};

#endif // FRACTALTRICORN_H
