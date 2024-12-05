#include "CommandParser.h"
#include "CommandResponseError.h"

QVariant CommandParser::parse(AbstractCommand *command, const QString &response) {
    if (response.contains("Error", Qt::CaseInsensitive)) {
        QStringList list = response.split(" ");
        int code = list[1].toInt();
        CommandResponseErrorCode errorCode = static_cast<CommandResponseErrorCode>(code);
        CommandResponseError error(errorCode, "No description available");
        error.printErrorMessage();

        return QVariant::fromValue(error);
    }

    if (command) {
        QVariant responseVariant = command->parseResponse(response);
        if (responseVariant.canConvert<CommandResponseError>()) {
            auto error = responseVariant.value<CommandResponseError>();
            error.printErrorMessage();
        }

        return responseVariant;
    } else {
        CommandResponseError error(CommandResponseErrorCode::NO_COMMAND_SENT, "Error parsing as no command is sent");
        error.printErrorMessage();
        return QVariant::fromValue(error);
    }
}
