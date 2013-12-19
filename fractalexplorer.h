#ifndef FRACTALEXPLORER_H
#define FRACTALEXPLORER_H

 #include <QPushButton>
 #include <QPixmap>
 #include <QWidget>

 #include "fractal.h"
 #include "fractalmandelbrot.h"
 #include "fractaltricorn.h"
 #include "fractalburningship.h"

 class fractalExplorer : public QWidget
 {
     Q_OBJECT

 public:
     fractalExplorer(QWidget *parent = 0);
     Fractal *thread;
     QPixmap pixmap;

 protected:
     void paintEvent(QPaintEvent *event);
     void resizeEvent(QResizeEvent *event);
     void keyPressEvent(QKeyEvent *event);
     void wheelEvent(QWheelEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void mouseDoubleClickEvent(QMouseEvent *event);
 private slots:
     void updatePixmap(const QImage &image, double scaleFactor);
 public slots:
     void updateColor(int fractalColor);
     void changeFractalType(int fractalType);
     void saveImage();

 private:
     void zoom(double zoomFactor);
     void scroll(int deltaX, int deltaY);

     QPoint pixmapOffset;
     QPoint lastDragPos;
     double centerX;
     double centerY;
     double pixmapScale;
     double curScale;
 };

#endif // FRACTALEXPLORER_H
