/**
 * @brief This class contains the main controller of the firmware. It is used to receive and send commands over the
 * serial interface forwards the commands to the multiplexers, which are responsible to switch the relays
 * @author Florian Frank
 * @version 1.0
 */

#ifndef ARDUINO_MAIN_CONTROLLER_H
#define ARDUINO_MAIN_CONTROLLER_H

#include <stdint.h>
#include "ErrorHandler.h"
#include "Message.h"

#ifdef ETHERNET_SUPPORT
class EthernetController;
#else // SERIAL_SUPPORT
class SerialInterfaceHandler;
#endif // ETHERNET_SUPPORT
class MultiplexerController;


class ArduinoMainController
{
public:
#ifdef ETHERNET_SUPPORT
    explicit ArduinoMainController();
#else
    explicit ArduinoMainController(uint8_t baudrate = 9600);
#endif
    ~ArduinoMainController();

    ErrorCode Init();
    ErrorCode DeInit();
    ErrorCode Loop();

private:
    ErrorCode SetRowColumn(Message message);
#ifdef ETHERNET_SUPPORT
    EthernetController *m_EthernetController;
#else
    SerialInterfaceHandler *m_SerialInterfaceHandler;
#endif
    MultiplexerController *m_MuxController;
    bool m_ConnectionEstablished;
};
#endif //ARDUINO_MAIN_CONTROLLER_H
