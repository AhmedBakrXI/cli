#include "Slip.h"


QByteArray Slip::encode(const QByteArray &data) {
    QByteArray encoded;
    encoded.append(SLIP_END); // Start of the packet

    for (char byte : data) {
        if (byte == SLIP_END) {
            encoded.append(SLIP_ESC);
            encoded.append(SLIP_ESC_END);
        } else if (byte == SLIP_ESC) {
            encoded.append(SLIP_ESC);
            encoded.append(SLIP_ESC_ESC);
        } else {
            encoded.append(byte);
        }
    }

    encoded.append(SLIP_END); // End of the packet
    return encoded;
}

QByteArray Slip::decode(const QByteArray &data, bool &isValidPacket) {
    QByteArray decoded;
    isValidPacket = false;
    bool escape = false;

    for (char byte : data) {
        if (byte == SLIP_END) {
            if (!decoded.isEmpty()) {
                isValidPacket = true;
                return decoded;
            }
            continue; // Ignore extra END characters
        }

        if (escape) {
            if (byte == SLIP_ESC_END) {
                decoded.append(SLIP_END);
            } else if (byte == SLIP_ESC_ESC) {
                decoded.append(SLIP_ESC);
            } else {
                // Invalid escape sequence
                isValidPacket = false;
                return QByteArray();
            }
            escape = false;
        } else if (byte == SLIP_ESC) {
            escape = true;
        } else {
            decoded.append(byte);
        }
    }

    return QByteArray();
}
