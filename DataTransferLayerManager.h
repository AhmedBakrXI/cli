#ifndef DATATRANSFERLAYERMANAGER_H
#define DATATRANSFERLAYERMANAGER_H

#include "PhysicalLayerManager.h"

class DataTransferLayerManager
{
public:
    using DtlDataReceivedCallback = std::function<void(const QString&)>;

    explicit DataTransferLayerManager(PhysicalLayerManager *phy);
    void sendString(const QString &str);
    void processReceivedData(const QByteArray& data);

    void setDataReceivedCallback(DtlDataReceivedCallback callback);

private:
    PhysicalLayerManager *phy;
    DtlDataReceivedCallback callback;

    QByteArray bytesRead;
};

#endif // DATATRANSFERLAYERMANAGER_H
