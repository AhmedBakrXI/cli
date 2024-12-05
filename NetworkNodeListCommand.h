#ifndef NETWORKNODELISTCOMMAND_H
#define NETWORKNODELISTCOMMAND_H

#include "AbstractCommand.h"

class NetworkNodeListCommand : public AbstractCommand {
public:
    NetworkNodeListCommand();


    // AbstractCommand interface
public:
    QVariant parseResponse(const QString &response) override;
};



#endif // NETWORKNODELISTCOMMAND_H
