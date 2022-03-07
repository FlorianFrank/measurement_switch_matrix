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

class MultiplexerController;
class SerialInterfaceHandler;

class ArduinoMainController
{
public:
    explicit ArduinoMainController(uint8_t baudrate = 9600);
    ~ArduinoMainController();

    ErrorCode Init();
    ErrorCode DeInit();
    ErrorCode Loop();

private:
    ErrorCode SetRowColumn(Command command, Message message);

    MultiplexerController *m_MuxController;
    SerialInterfaceHandler *m_SerialInterfaceHandler;
    bool m_ConnectionEstablished;
};
#endif //ARDUINO_MAIN_CONTROLLER_H
