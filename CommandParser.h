#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <QVariant>
#include "AbstractCommand.h"

class CommandParser {
public:
    CommandParser() = default;
    static QVariant parse(AbstractCommand *command, const QString &response);
};

#endif // COMMANDPARSER_H
