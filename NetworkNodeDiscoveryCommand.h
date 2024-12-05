#ifndef NETWORKNODEDISCOVERYCOMMAND_H
#define NETWORKNODEDISCOVERYCOMMAND_H

#include "AbstractCommand.h"

class NetworkNodeDiscoveryCommand : public AbstractCommand {
public:
    NetworkNodeDiscoveryCommand();



    // AbstractCommand interface
public:
    QVariant parseResponse(const QString &response) override;
};

#endif // NETWORKNODEDISCOVERYCOMMAND_H
