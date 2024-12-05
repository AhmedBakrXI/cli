#include <QCoreApplication>
#include <QObject>

#include <QSerialPort>

#include "CommandRegistry.h"
#include "PhysicalLayerManager.h"
#include "DataTransferLayerManager.h"
#include "CommandManager.h"
#include "NetworkNodeListCommand.h"

void onDataReceived(const QString& str) {
    qDebug() << "Received: " << str;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    QSerialPort *port = new QSerialPort;
    port->setPortName("tnt1");
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data7);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    if (port->open(QIODevice::ReadWrite)) {
        qDebug() << "Port is Open";
    } else {
        qDebug()<<"Failed: " << port->errorString();
    }

    PhysicalLayerManager *phy = new PhysicalLayerManager(port);
    DataTransferLayerManager *dtl = new DataTransferLayerManager(phy);
    CommandRegistry &registry = CommandRegistry::instance();
    NetworkNodeListCommand nwkListCmd;
    registry.registerCommand(nwkListCmd);
    CommandManager *cmdMngr = new CommandManager(dtl);
    cmdMngr->sendCommand("nwk nd disc");

    // while (true) {
    //     if (cmdMngr->isAvailable()) {
    //         cmdMngr->sendCommand("nwk nd disc");
    //         break;
    //     }
    // }

    // port->close();

    return a.exec();
}
