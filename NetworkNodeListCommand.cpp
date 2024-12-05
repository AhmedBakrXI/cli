#include "CommandResponseError.h"
#include "NetworkNodeListCommand.h"
#include "NodeEntryDto.h"

NetworkNodeListCommand::NetworkNodeListCommand() {
    this->setName("nwk nd list");
    this->setParams({"4", "2"});
    this->setTimeout(100000);
}

QVariant NetworkNodeListCommand::parseResponse(const QString &response) {
    NodeEntryDto nodeEntryDto;
    QStringList responseAsList = response.split(" ");

    if (responseAsList.size() != 4) {
        CommandResponseError error(CommandResponseErrorCode::PARSING_ERROR, "Response is too short");
        return QVariant::fromValue(error);
    }

    bool canConvert = false;
    quint16 networkAddress = responseAsList[0].toInt(&canConvert, 16);
    if (canConvert) {
        nodeEntryDto.setNetworkAddress(networkAddress);
    } else {
        CommandResponseError error(CommandResponseErrorCode::PARSING_ERROR, "Failed to convert network address to hex");
        return QVariant::fromValue(error);
    }

    QString macAddress = responseAsList[1];
    nodeEntryDto.setMacAddress(macAddress);

    canConvert = false;
    quint8 logicalType = responseAsList[2].toInt(&canConvert);
    if (canConvert) {
        nodeEntryDto.setLogicalType(logicalType);
    } else {
        CommandResponseError error(CommandResponseErrorCode::PARSING_ERROR, "Failed converting string to int");
        return QVariant::fromValue(error);
    }

    canConvert = false;
    qint16 parentNetworkAddress = responseAsList[0].toInt(&canConvert, 16);
    if (canConvert) {
        nodeEntryDto.setParentNetworkAddress(parentNetworkAddress);
    } else {
        CommandResponseError error(CommandResponseErrorCode::PARSING_ERROR, "Failed to convert network address to hex");
        return QVariant::fromValue(error);
    }

    QVariant respDto = QVariant::fromValue(nodeEntryDto);

    return respDto;
}
