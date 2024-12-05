#ifndef SLIP_H
#define SLIP_H

#include <QByteArray>

constexpr char SLIP_END = 0xC0;
constexpr char SLIP_ESC = 0xDB;
constexpr char SLIP_ESC_END = 0xDC;
constexpr char SLIP_ESC_ESC = 0xDD;

class Slip {
public:
    static QByteArray encode(const QByteArray &data);
    static QByteArray decode(const QByteArray &data, bool &isValidPacket);
};

#endif // SLIP_H
