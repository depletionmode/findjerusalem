#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QCompass>

#include <QGraphicsScene>

#include "compassthread.h"

QTM_USE_NAMESPACE

namespace Ui {
    class FindJerusalem;
}

class FindJerusalem : public QMainWindow
{
    Q_OBJECT

public:
    explicit FindJerusalem(QWidget *parent = 0);
    ~FindJerusalem();

private:
    Ui::FindJerusalem *ui;

    QGraphicsScene _s;
    QGeoPositionInfoSource *_source;

    CompassThread _compassThread;

private slots:
    void positionUpdated(const QGeoPositionInfo &info);
    void updateTimeout();
};

#endif // MAINWINDOW_H
