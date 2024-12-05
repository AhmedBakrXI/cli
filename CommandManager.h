#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "DataTransferLayerManager.h"
#include "AbstractCommand.h"

#include <QElapsedTimer>

class CommandManager {
public:
    using CommandReceivedCallback = std::function<void(const QVariant&)>;

    CommandManager(DataTransferLayerManager *dtl);
    void sendCommand(AbstractCommand *command);
    void sendCommand(const QString &command);
    void processResponse(const QString &response);
    void setOnResponseCallback(CommandReceivedCallback callback);
    bool isAvailable();
private:
    DataTransferLayerManager *dtl;
    CommandReceivedCallback callback;
    QElapsedTimer timer;

    AbstractCommand *currentCommand;
};

#endif // COMMANDMANAGER_H
