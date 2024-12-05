#include "DataTransferLayerManager.h"
#include <QDebug>

#include "Slip.h"

DataTransferLayerManager::DataTransferLayerManager(PhysicalLayerManager *phy) {
    this->phy = phy;
    phy->setOnDataReceivedCallback([this](const QByteArray &data) {
        bytesRead.append(data);
        if (bytesRead.endsWith(SLIP_END)) {
            processReceivedData(data);
        }
    });
}

void DataTransferLayerManager::sendString(const QString &str) {
    if (phy) {
        QByteArray encoded = Slip::encode(str.toUtf8());
        phy->sendData(encoded);
    } else {
        qDebug() << "Phy is null";
    }
}

void DataTransferLayerManager::processReceivedData(const QByteArray &data) {
    bool isValid = false;
    QByteArray decoded = Slip::decode(data, isValid);
    if (isValid) {
        qDebug() << "Decoded data successfully";
        if (callback) {
            callback(QString::fromUtf8(decoded));
        } else {
            qDebug() << "No call back for DTL";
        }
    } else {
        qDebug() << "Can't decode data";
    }

    bytesRead.clear();
}


void DataTransferLayerManager::setDataReceivedCallback(DtlDataReceivedCallback callback) {
    this->callback = callback;
}
