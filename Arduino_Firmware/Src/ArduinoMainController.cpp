#include "ArduinoMainController.h"
#include "MultiplexerController.h"

#ifdef ETHERNET_SUPPORT

#include "ethernet/EthernetController.h"
#include "ethernet/EthernetDefines.h"

#else // SERIAL_SUPPORT
#include "SerialInterfaceHandler.h"
#endif // ifdef ETHERNET_SUPPORT

#include "Arduino.h"


/**
 * @brief The constructor initializes the controller for ADG726 multiplexer
 * and enables the serial interface handler with an Baudrate.
 */
#ifdef ETHERNET_SUPPORT

ArduinoMainController::ArduinoMainController() : m_ConnectionEstablished(false)
#else
ArduinoMainController::ArduinoMainController(const uint8_t baudrate): m_ConnectionEstablished(false)
#endif
{
    m_MuxController = new MultiplexerController();
#if ETHERNET_SUPPORT
    byte ip[IP_SIZE] = {DEFAULT_IP};
    m_EthernetController = new EthernetController(ip, DEFAULT_PORT);
#else
    m_SerialInterfaceHandler = new SerialInterfaceHandler(baudrate);
#endif
}

/**
 * @brief The destructor deletes the multiplexer controller,
 * as well as the serial interface handler allocated on the heap.
 */
ArduinoMainController::~ArduinoMainController() {
    free(m_MuxController);
#if ETHERNET_SUPPORT
    free(m_EthernetController);
#else
    free(m_SerialInterfaceHandler);
#endif

}

/**
 * @brief This function runs the initialization functions of the multiplexer,
 * as well as the serial interface handler.
 * @return NO_ERROR if no error occurred otherwise an error code is returned.
 */
ErrorCode ArduinoMainController::Init() {
    if (!m_MuxController)
        return NOT_INITIALIZED;

    m_MuxController->InitializeMultiplexer();

#if ETHERNET_SUPPORT
    // Enable serial interface logging
    Serial.begin(9600);
    m_EthernetController->Initialize();
    m_ConnectionEstablished = true;
    return NO_ERROR;
#else
    return m_SerialInterfaceHandler->InitializeSerialInterface();
#endif
}

/**
 * @brief This function runs the de-initialization functions of the multiplexer,
 * as well as the serial interface handler.
 * @return NO_ERROR if no error occurred otherwise an error code is returned.
 */
ErrorCode ArduinoMainController::DeInit() {
    if (!m_MuxController)
        return NOT_INITIALIZED;

    m_MuxController->DeInitializeMultiplexer();
#if ETHERNET_SUPPORT
#else
    return m_SerialInterfaceHandler->DeInitializeSerialInterface();
#endif
}

/**
 * @brief This method contains the main loop of the firmware executed on the Arduino.
 *        Here, data is read from the UART interface, parsed and the commands are forwarded to the
 *        multiplexer to control the darlington arrays.
 * @return NO_ERROR if no error occurred otherwise return an error code.
 */
ErrorCode ArduinoMainController::Loop() {
#if ETHERNET_SUPPORT
    int row, column;
    Command currentCommand = m_EthernetController->ReceiveMessage(&row, &column);

    if (currentCommand == SELECT_ROW) {
        SetRowColumn(Message(static_cast<unsigned long>(row), currentCommand));
    } else if (currentCommand == SELECT_COLUMN) {
        SetRowColumn(Message(static_cast<unsigned long>(column), currentCommand));
    } else if (currentCommand == SELECT_ROW_COLUMN) {
        SetRowColumn(Message(static_cast<unsigned long>(column), SELECT_COLUMN));
        SetRowColumn(Message(static_cast<unsigned long>(row), SELECT_ROW));
    }
    delay(ETHERNET_LOOP_DELAY_MS);
#else // Serial interface
    int len = MAX_COMMAND_LEN;
    Message message = SerialInterfaceHandler::ReadAndParseMessageNonBlocking(&len);
    Command currentCommand = message.GetCurrentCommand();
    if(currentCommand != NOPE)
    {
        char buf[MAX_COMMAND_LEN];
        sprintf(buf, "T: %d\n", currentCommand);
        Serial.write(buf);
        Message acknowledgement(0, ACK);

        if(currentCommand == ERROR_CODE)
            acknowledgement = message;

        if(currentCommand == CONNECT)
            m_ConnectionEstablished = true;

        if(currentCommand == DISCONNECT)
            m_ConnectionEstablished = false;

        if((currentCommand == SELECT_COLUMN || currentCommand == SELECT_ROW))
        {
            ErrorCode rowColumnErrCode = SetRowColumn(message);
            if (rowColumnErrCode != NO_ERROR)
                acknowledgement = Message(rowColumnErrCode);
        }

        ErrorCode serialError = m_SerialInterfaceHandler->WriteMessage(acknowledgement);
        if(serialError != NO_ERROR)
            return serialError;
    }
#endif
    return NO_ERROR;
}

/**
 * @brief This method forwards a Select Row or Select Column command to the ADG726 switch matrix.
 * @param command could be "select row" or "select column".
 * @param message The message contains the row or column to select.
 * @return NO_ERROR if no error occurred otherwise return an error code.
 */
ErrorCode ArduinoMainController::SetRowColumn(Message message) {
    if (!m_ConnectionEstablished)
        return DISCONNECTED;

    ErrorCode errorCode;
    if (message.GetCurrentCommand() == SELECT_COLUMN)
        errorCode = m_MuxController->SelectColumn(message.GetParameter());
    if (message.GetCurrentCommand() == SELECT_ROW)
        errorCode = m_MuxController->SelectRow(message.GetParameter());

    if (errorCode != NO_ERROR)
        return errorCode;

    errorCode = m_MuxController->WriteRowColumn();
    if (errorCode != NO_ERROR)
        return errorCode;
    return NO_ERROR;
}


