#include "NetworkNodeDiscoveryCommand.h"

NetworkNodeDiscoveryCommand::NetworkNodeDiscoveryCommand() {
    this->setName("nwk nd disc");
    this->setTimeout(100000);
}

QVariant NetworkNodeDiscoveryCommand::parseResponse(const QString &response) {
    return "OK";
}
