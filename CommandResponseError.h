#ifndef COMMANDRESPONSEERROR_H
#define COMMANDRESPONSEERROR_H

#include <QString>
#include <QDebug>

enum class CommandResponseErrorCode {
    NO_NETWORK = 0,
    INVALID_COMMAND,
    INVALID_PARAMETERS,
    OPERATION_FAILED,
    NODE_NOT_FOUND,
    TIMEOUT,
    NO_COMMAND_SENT,
    PARSING_ERROR,
    UNKNOWN_ERROR
};

class CommandResponseError {
public:
    CommandResponseError()
        : code(CommandResponseErrorCode::UNKNOWN_ERROR),
        message(mapErrorMessage(code)),
        description("No description available") {}

    CommandResponseError(CommandResponseErrorCode errCode, const QString &description)
        : code(errCode), message(mapErrorMessage(code)), description(description) {}

    CommandResponseErrorCode getCode() const { return code; }
    QString getMessage() const { return message; }
    QString getDescription() const { return description; }
    void printErrorMessage() {
        qCritical().noquote() << toString();
    }
    QString toString() {
        QString str;
        str += "Error: " + mapErrorMessage(code) + ", description: " + description;
        return str;
    }

    static QString mapErrorMessage(CommandResponseErrorCode code) {
        switch (code) {
        case CommandResponseErrorCode::NO_NETWORK: return "No network connection.";
        case CommandResponseErrorCode::INVALID_COMMAND: return "The command is invalid.";
        case CommandResponseErrorCode::INVALID_PARAMETERS: return "Invalid parameters provided.";
        case CommandResponseErrorCode::OPERATION_FAILED: return "The operation failed.";
        case CommandResponseErrorCode::NODE_NOT_FOUND: return "Node not found.";
        case CommandResponseErrorCode::TIMEOUT: return "The operation timed out.";
        case CommandResponseErrorCode::NO_COMMAND_SENT: return "User didn't send a command";
        case CommandResponseErrorCode::PARSING_ERROR: return "Error while parsing response";
        case CommandResponseErrorCode::UNKNOWN_ERROR: return "Unknown error";
        default: return "Unknown error.";
        }
    }

private:
    CommandResponseErrorCode code;
    QString message;
    QString description;
};

Q_DECLARE_METATYPE(CommandResponseError)

#endif // COMMANDRESPONSEERROR_H
