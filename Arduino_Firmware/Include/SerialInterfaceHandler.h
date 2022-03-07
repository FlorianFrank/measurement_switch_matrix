/**
 * @brief This file contains the functionality to control the serial connection to the control computer.
 *        It contains functionality to send and receive messages.
 * @author Florian Frank
 * @version 1.0
 */

#ifndef SERIAL_INTERFACE_HANDLER_H
#define SERIAL_INTERFACE_HANDLER_H


#include <stdint.h>
#include "Message.h"
#include "ErrorHandler.h"

#define MAX_LEN_SEND_BUFFER 512

class SerialInterfaceHandler
{
public:
    explicit SerialInterfaceHandler(uint16_t baudRate = 9600);
    ~SerialInterfaceHandler();

    ErrorCode InitializeSerialInterface();
    ErrorCode DeInitializeSerialInterface();

    ErrorCode WriteMessage(Message &message) const;
    static Message ReadAndParseMessageBlocking(int *len);
    static Message ReadAndParseMessageNonBlocking(int *len);
    static int DataAvail();

private:
    uint16_t m_Baudrate;
    bool m_IsSerialInterfaceOpen;

};


#endif //SERIAL_INTERFACE_HANDLER_H
