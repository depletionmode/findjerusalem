#include "findjerusalem.h"
#include "ui_findjerusalem.h"

#include <QDebug>
#include <QMessageBox>
#include <QGeoCoordinate>
#include <QGeoSatelliteInfoSource>
#include <QDesktopWidget>

#include <QGraphicsSvgItem>
#include <QSvgRenderer>

FindJerusalem::FindJerusalem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindJerusalem)
{
    ui->setupUi(this);

    _source = QGeoPositionInfoSource::createDefaultSource(this);
    connect(_source, SIGNAL(positionUpdated(QGeoPositionInfo)),
            this, SLOT(positionUpdated(QGeoPositionInfo)));
    connect(_source, SIGNAL(updateTimeout()),
            this, SLOT(updateTimeout()));
    _source->setUpdateInterval(3000);
    _source->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
    _source->startUpdates();

    QRect clientRect = QApplication::desktop()->availableGeometry();
    ui->gv->resize(clientRect.right(), clientRect.bottom());

    ui->gv->setScene(&_s);

    _compassThread.setGv(ui->gv);
    _compassThread.start();
}

FindJerusalem::~FindJerusalem()
{
    _compassThread.exit();
    delete ui;
}

void FindJerusalem::updateTimeout()
{
    ui->lblTest->setText("Unable to find your location!");

    QMessageBox msgBox;
    msgBox.setText("Unable to find your location!");
    msgBox.exec();
}

void FindJerusalem::positionUpdated(const QGeoPositionInfo &info)
{
    qDebug() << "Current position:" << info;
    qDebug() << info.coordinate().toString(QGeoCoordinate::DegreesMinutesSeconds);

    if (info.coordinate().isValid()) {
        ui->lblTest->setText(info.coordinate().toString(QGeoCoordinate::DegreesMinutesSeconds));
    }

    QGeoCoordinate coordJlem(31.776783, 35.234469); //Kotel 31 46' 36.42", 35 14' 4.09"

    qreal azimuth = info.coordinate().azimuthTo(coordJlem);

    qDebug() << QString::number(double(azimuth)) + QString("° to the Kotel");

    _compassThread.updateAzimuth((int)azimuth);

    _compassThread.redrawScene();
    _source->stopUpdates();
}
