#include "AbstractCommand.h"

QString AbstractCommand::getName() const
{
    return name;
}

void AbstractCommand::setName(const QString &newName)
{
    name = newName;
}

QString AbstractCommand::getDescription() const
{
    return description;
}

void AbstractCommand::setDescription(const QString &newDescription)
{
    description = newDescription;
}

int AbstractCommand::getTimeout() const
{
    return timeout;
}

void AbstractCommand::setTimeout(int newTimeout)
{
    timeout = newTimeout;
}

QString AbstractCommand::toStringCommand() {
    QString str;
    str.append(this->name);
    for (QString &param : params) {
        str.append(" ");
        str.append(param);
    }
    return str;
}

QStringList AbstractCommand::getParams() const
{
    return params;
}

void AbstractCommand::setParams(const QStringList &newParams)
{
    params = newParams;
}

void AbstractCommand::addParam(const QString &param)
{
    this->params.append(param);
}
