#include "NodeEntryDto.h"

qint16 NodeEntryDto::getNetworkAddress() const
{
    return networkAddress;
}

void NodeEntryDto::setNetworkAddress(qint16 newNetworkAddress)
{
    networkAddress = newNetworkAddress;
}

QString NodeEntryDto::getMacAddress() const
{
    return macAddress;
}

void NodeEntryDto::setMacAddress(const QString &newMacAddress)
{
    macAddress = newMacAddress;
}

qint8 NodeEntryDto::getLogicalType() const
{
    return logicalType;
}

void NodeEntryDto::setLogicalType(qint8 newLogicalType)
{
    logicalType = newLogicalType;
}

qint16 NodeEntryDto::getParentNetworkAddress() const
{
    return parentNetworkAddress;
}

void NodeEntryDto::setParentNetworkAddress(qint16 newParentNetworkAddress)
{
    parentNetworkAddress = newParentNetworkAddress;
}

QString NodeEntryDto::toString() {
    QString str;
    str += "{\n";
    str += "\tNWK ADDR: " + QString::number(networkAddress) + ", \n";
    str += "\tMAC ADDR: " + macAddress + ",\n";
    // convert logical type to string
    QString type = (logicalType == 0) ? "Coordinator" : (logicalType == 1 ? "Router" : "Device");
    str += "\tLOGICAL TYPE: " + type + ",\n";
    str += "\tPARENT NWK ADDR: " + QString::number(parentNetworkAddress) + "\n";
    str += "}";
    return str;
}
