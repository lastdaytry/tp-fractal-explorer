#ifndef FRACTALBURNINGSHIP_H
#define FRACTALBURNINGSHIP_H

#include "fractal.h"

class fractalBurningShip : public Fractal
{
     Q_OBJECT

public:
    fractalBurningShip(QObject *parent = 0);
    ~fractalBurningShip();
    void render(double centerX, double centerY, double scaleFactor,
                              QSize resultSize);
    void run();
};
#endif // FRACTALBURNINGSHIP_H
