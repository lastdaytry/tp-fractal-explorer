#include <QtGui>
#include <math.h>
#include <QFileDialog>
#include "fractalexplorer.h"

const double DefaultCenterX = -0.637011f;
const double DefaultCenterY = -0.0395159f;
const double DefaultScale = 0.00517897f;

const double ZoomInFactor = 0.8f;
const double ZoomOutFactor = 1 / ZoomInFactor;
const int ScrollStep = 20;

fractalExplorer::fractalExplorer(QWidget *parent)
    : QWidget(parent)
{
    thread = new fractalMandelbrot;
    centerX = DefaultCenterX;
    centerY = DefaultCenterY;
    pixmapScale = DefaultScale;
    curScale = DefaultScale;
    qRegisterMetaType<QImage>("QImage");
    connect(thread, SIGNAL(renderedImage(QImage,double)),
            this, SLOT(updatePixmap(QImage,double)));
    setWindowTitle(tr("Fractal"));
#ifndef QT_NO_CURSOR
    setCursor(Qt::CrossCursor);
#endif
    resize(550, 400);
}

fractalExplorer::~fractalExplorer()
{
    delete(thread);
}

void fractalExplorer::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    if (pixmap.isNull()) {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter,
                         tr("Rendering initial image, please wait..."));
        return;
    }

    if (curScale == pixmapScale) {
        painter.drawPixmap(pixmapOffset, pixmap);
    } else {
        double scaleFactor = pixmapScale / curScale;
        int newWidth = int(pixmap.width() * scaleFactor);
        int newHeight = int(pixmap.height() * scaleFactor);
        int newX = pixmapOffset.x() + (pixmap.width() - newWidth) / 2;
        int newY = pixmapOffset.y() + (pixmap.height() - newHeight) / 2;

        painter.save();
        painter.translate(newX, newY);
        painter.scale(scaleFactor, scaleFactor);
        QRectF exposed = painter.matrix().inverted().mapRect(rect()).adjusted(-1, -1, 1, 1);
        painter.drawPixmap(exposed, pixmap, exposed);
        painter.restore();
    }
}

void fractalExplorer::resizeEvent(QResizeEvent * /* event */)
{
    thread->render(centerX, centerY, curScale, size());
}

void fractalExplorer::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoom(ZoomInFactor);
        break;
    case Qt::Key_Minus:
        zoom(ZoomOutFactor);
        break;
    case Qt::Key_Left:
        scroll(-ScrollStep, 0);
        break;
    case Qt::Key_Right:
        scroll(+ScrollStep, 0);
        break;
    case Qt::Key_Down:
        scroll(0, -ScrollStep);
        break;
    case Qt::Key_Up:
        scroll(0, +ScrollStep);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void fractalExplorer::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    double numSteps = numDegrees / 15.0f;
    zoom(pow(ZoomInFactor, numSteps));
}

void fractalExplorer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        lastDragPos = event->pos();
}

void fractalExplorer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = event->pos();
        update();
    }
}

void fractalExplorer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = QPoint();

        int deltaX = (width() - pixmap.width()) / 2 - pixmapOffset.x();
        int deltaY = (height() - pixmap.height()) / 2 - pixmapOffset.y();
        scroll(deltaX, deltaY);
    }
}

void fractalExplorer::updatePixmap(const QImage &image, double scaleFactor)
{
    if (!lastDragPos.isNull())
        return;

    pixmap = QPixmap::fromImage(image);
    pixmapOffset = QPoint();
    lastDragPos = QPoint();
    pixmapScale = scaleFactor;
    update();
}

void fractalExplorer::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        zoom(0.5);
    }
}

void fractalExplorer::zoom(double zoomFactor)
{
    curScale *= zoomFactor;
    update();
    thread->render(centerX, centerY, curScale, size());
}

void fractalExplorer::scroll(int deltaX, int deltaY)
{
    centerX += deltaX * curScale;
    centerY += deltaY * curScale;
    update();
    thread->render(centerX, centerY, curScale, size());
}

void fractalExplorer::changeFractalType(int fractalType)
{
    if (fractalType == 0) {
        delete(thread);
        thread = 0;
        thread = new fractalMandelbrot;
        centerX = DefaultCenterX;
        centerY = DefaultCenterY;
        pixmapScale = DefaultScale;
        curScale = DefaultScale;
    }

    if (fractalType == 1) {
        delete(thread);
        thread = 0;
        thread = new fractalTricorn;
        centerX = -0.637011f;
        centerY = -0.0395159f;
        pixmapScale = 0.00717897f;
        curScale = 0.00717897f;
    }

    if (fractalType == 2) {
        delete(thread);
        thread = 0;
        thread = new fractalBurningShip;
        centerX = -0.637011f;
        centerY = -0.4795159f;
        pixmapScale = 0.00717897f;
        curScale = 0.00717897f;
    }

    qRegisterMetaType<QImage>("QImage");
    connect(thread, SIGNAL(renderedImage(QImage,double)),
            this, SLOT(updatePixmap(QImage,double)));
    setWindowTitle(tr("Fractal"));
#ifndef QT_NO_CURSOR
    setCursor(Qt::CrossCursor);
#endif
    resize(550, 400);
    thread->render(centerX, centerY, pixmapScale, size());
}

void fractalExplorer::updateColor(int fractalColor)
{
    thread->updateColor(fractalColor);
}

void fractalExplorer::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save Image"), "/home/warprobot", tr("Image Files (*.png)"));

    QFile file( fileName );
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file, "PNG");
}
