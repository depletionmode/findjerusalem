#ifndef COMPASSTHREAD_H
#define COMPASSTHREAD_H

#include <QCompass>

#include <QThread>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>

QTM_USE_NAMESPACE

class CompassThread : public QThread
{
    Q_OBJECT

public:
    CompassThread();

    void updateAzimuth(int azimuth) { _azimuth = azimuth; }
    void setGv(QGraphicsView *gv) { _gv = gv; }

    void redrawScene(int imgIdx = 1);

protected:
    void run();

    QGraphicsView *_gv;
    QCompass _compass;
    int _currentHeading;
    int _azimuth;
    QCompassReading *_reading;
    QSvgRenderer *_renderer;
    QGraphicsSvgItem *_item;
};


#endif // COMPASSTHREAD_H
