#include "PhysicalLayerManager.h"

#include <QDebug>

PhysicalLayerManager::PhysicalLayerManager(QSerialPort *port) {
    this->port = port;
    QObject::connect(port, &QSerialPort::readyRead, this, &PhysicalLayerManager::handleReadyRead);
}

void PhysicalLayerManager::sendData(QByteArray &dataBytes) {
    if (port->isOpen()) {
        port->write(dataBytes);
    } else {
        qDebug() << port->errorString();
    }
}

void PhysicalLayerManager::setOnDataReceivedCallback(PhyDataReceivedCallback callback) {
    this->dataReceivedCallback = callback;
}

void PhysicalLayerManager::handleReadyRead() {
    QByteArray data = port->readAll();  // Read all available data
    if (dataReceivedCallback) {
        dataReceivedCallback(data);  // Invoke the callback with the received data
    } else {
        qDebug() << "PHY: No call back is set";
    }
}
