#include "CommandManager.h"
#include "CommandRegistry.h"

#include "NodeEntryDto.h"
#include "CommandParser.h"
#include "CommandResponseError.h"

CommandManager::CommandManager(DataTransferLayerManager *dtl) {
    this->dtl = dtl;

    dtl->setDataReceivedCallback([this](const QString &response) {
        qDebug() << "Response: " << response;
        processResponse(response);
    });
}

void CommandManager::sendCommand(AbstractCommand *command) {
    dtl->sendString(command->toStringCommand());
    timer.start();
}

void CommandManager::sendCommand(const QString &command) {
    if (currentCommand) {
        qDebug() << "Busy executing another command";
        return;
    }

    CommandRegistry &registry = CommandRegistry::instance();
    currentCommand = registry.getCommand(command);
    if (currentCommand) {
        sendCommand(currentCommand);
    } else {
        qDebug() << "Command Not Found";
    }
}

void CommandManager::processResponse(const QString &response) {
    QVariant variantDto;
    if (!currentCommand) {
        CommandResponseError error(CommandResponseErrorCode::NO_COMMAND_SENT, "There is a response with no command sent");
        variantDto = QVariant::fromValue(error);
    } else if (timer.elapsed() > currentCommand->getTimeout()) {
        qDebug() << "CMD: Timeout for response";
        CommandResponseError error(CommandResponseErrorCode::TIMEOUT, "There is a response but it has reached after timeout");
        variantDto = QVariant::fromValue(error);
        return;
    }

    // Marked for removal
    QVariant parsedDto = CommandParser::parse(currentCommand, response);
    if (parsedDto.canConvert<NodeEntryDto>()) {

        NodeEntryDto nodeEntryDto = parsedDto.value<NodeEntryDto>();
        qDebug().noquote() << nodeEntryDto.toString();
    }

    if (callback) {
        // pass the parsed response as parameter to callback
        callback(variantDto);
        qDebug() << "CMD: Called callback";
    } else {
        qDebug() << "CMD: callback is null";
        if (variantDto.canConvert<CommandResponseError>()) {
            auto error = variantDto.value<CommandResponseError>();
            error.printErrorMessage();
        }
    }

    currentCommand = nullptr; // free for other commands
}

void CommandManager::setOnResponseCallback(CommandReceivedCallback callback) {
    this->callback = callback;
}

bool CommandManager::isAvailable() {
    if (!currentCommand) {
        return true;
    } else {
        return false;
    }
}
