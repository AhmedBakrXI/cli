#ifndef PHYSICALLAYERMANAGER_H
#define PHYSICALLAYERMANAGER_H


#include <QObject>
#include <QSerialPort>

class PhysicalLayerManager : public QObject {
    Q_OBJECT
public:
    using PhyDataReceivedCallback = std::function<void(const QByteArray&)>;

    explicit PhysicalLayerManager(QSerialPort *port);
    void sendData(QByteArray &dataBytes);
    void setOnDataReceivedCallback(PhyDataReceivedCallback callback);

public slots:
    void handleReadyRead();

private:
    QSerialPort *port;
    PhyDataReceivedCallback dataReceivedCallback;
};

#endif // PHYSICALLAYERMANAGER_H
