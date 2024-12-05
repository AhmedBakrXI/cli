#ifndef NODEENTRYDTO_H
#define NODEENTRYDTO_H

#include <qobject.h>
#include <qtypes.h>
#include <QString>
#include <QVariant>

class NodeEntryDto {
public:
    NodeEntryDto() = default;
    qint16 getNetworkAddress() const;
    void setNetworkAddress(qint16 newNetworkAddress);
    QString getMacAddress() const;
    void setMacAddress(const QString &newMacAddress);
    qint8 getLogicalType() const;
    void setLogicalType(qint8 newLogicalType);
    qint16 getParentNetworkAddress() const;
    void setParentNetworkAddress(qint16 newParentNetworkAddress);

    QString toString();

private:
    quint16 networkAddress;
    QString macAddress;
    quint8 logicalType;
    quint16 parentNetworkAddress;
};

Q_DECLARE_METATYPE(NodeEntryDto)

#endif // NODEENTRYDTO_H
