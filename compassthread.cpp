#include "compassthread.h"

#include <unistd.h>

#include <QDebug>

CompassThread::CompassThread() :
        QThread(), _currentHeading(0), _azimuth(0), _reading(NULL), _renderer(NULL), _item(NULL)
{
    _compass.start();
}

void CompassThread::run()
{
    int heading;
    while (1) {
        ::usleep(100000);

        _reading = _compass.reading();
        qreal calibrationLevel = _reading->calibrationLevel();

        heading = _azimuth - (int)_reading->azimuth();
        heading %= 360;

        qDebug() << "compass azimuth:" << (int)_reading->azimuth();
        qDebug() << "azimuth:" << _azimuth;
        qDebug() << "heading:" << _currentHeading;

        _gv->rotate(360 - _currentHeading);
        _currentHeading = heading;
        _gv->rotate(_currentHeading);

        if (_currentHeading < 0) _currentHeading += 360;

        if (_currentHeading >= 355 || _currentHeading <= 5) {
            redrawScene(2);
        }
        else {
            redrawScene(1);
        }
    }
}

#define deletex(x)              \
        if (x) {                \
            delete x;           \
            x = NULL;           \
        }

void CompassThread::redrawScene(int imgIdx)
{
    static int idx(0);

    if (imgIdx != idx) {
        idx = imgIdx;

        if (_gv) {
            if (_item) _gv->scene()->removeItem(_item);
            deletex(_renderer);
            deletex(_item);

            char resource[30];
            ::snprintf(resource, sizeof(resource), ":/arrow%d.svg", idx);
            _renderer = new QSvgRenderer(QLatin1String(resource));
            _item = new QGraphicsSvgItem();

            _item->setSharedRenderer(_renderer);
            _item->setScale(2.5);
            _gv->scene()->addItem(_item);

            qDebug() << "Scene redraw, idx = " << idx;
        }
    }
}
