#ifndef FRACTAL_H
#define FRACTAL_H

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>

class QImage;

class Fractal : public QThread
{
    Q_OBJECT

public:
    Fractal(QObject *parent = 0);
    virtual ~Fractal();

    virtual void render(double centerX, double centerY, double scaleFactor,
                QSize resultSize) = 0;
    virtual void run() = 0;

    void updateColor(int fractalColor);

signals:
    void renderedImage(const QImage &image, double scaleFactor);

protected:

    uint rgbFromWaveLength(double wave, int colorIndex);

    QMutex mutex;
    QWaitCondition condition;
    double centerX;
    double centerY;
    double scaleFactor;
    QSize resultSize;
    bool restart;
    bool abort;

    enum { ColormapSize = 512 };
    uint colormap[ColormapSize];
};

#endif // FRACTAL_H
