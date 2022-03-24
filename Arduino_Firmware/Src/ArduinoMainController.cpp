#include "ArduinoMainController.h"
#include "MultiplexerController.h"
#include "SerialInterfaceHandler.h"

#include "Arduino.h"

/**
 * @brief The constructor initializes the controller for ADG726 multiplexer
 * and enables the serial interface handler with an Baudrate.
 */
ArduinoMainController::ArduinoMainController(const uint8_t baudrate): m_ConnectionEstablished(false)
{
    m_MuxController = new MultiplexerController();
    m_SerialInterfaceHandler = new SerialInterfaceHandler(baudrate);
}

/**
 * @brief The destructor deletes the multiplexer controller,
 * as well as the serial interface handler allocated on the heap.
 */
ArduinoMainController::~ArduinoMainController()
{
    free(m_MuxController);
    free(m_SerialInterfaceHandler);
}

/**
 * @brief This function runs the initialization functions of the multiplexer,
 * as well as the serial interface handler.
 * @return NO_ERROR if no error occurred otherwise an error code is returned.
 */
ErrorCode ArduinoMainController::Init()
{
    if(!m_MuxController || !m_SerialInterfaceHandler)
        return NOT_INITIALIZED;

    m_MuxController->InitializeMultiplexer();

    return m_SerialInterfaceHandler->InitializeSerialInterface();
}

/**
 * @brief This function runs the de-initialization functions of the multiplexer,
 * as well as the serial interface handler.
 * @return NO_ERROR if no error occurred otherwise an error code is returned.
 */
ErrorCode ArduinoMainController::DeInit()
{
    if(!m_MuxController || !m_SerialInterfaceHandler)
        return NOT_INITIALIZED;

    m_MuxController->DeInitializeMultiplexer();

    return m_SerialInterfaceHandler->DeInitializeSerialInterface();
}

/**
 * @brief This method contains the main loop of the firmware executed on the Arduino.
 *        Here, data is read from the UART interface, parsed and the commands are forwarded to the
 *        multiplexer to control the darlington arrays.
 * @return NO_ERROR if no error occurred otherwise return an error code.
 */
ErrorCode ArduinoMainController::Loop()
{
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
            ErrorCode rowColumnErrCode = SetRowColumn(currentCommand, message);
            if (rowColumnErrCode != NO_ERROR)
                acknowledgement = Message(rowColumnErrCode);
        }

        ErrorCode serialError = m_SerialInterfaceHandler->WriteMessage(acknowledgement);
        if(serialError != NO_ERROR)
            return serialError;
    }
    return NO_ERROR;
}

/**
 * @brief This method forwards a Select Row or Select Column command to the ADG726 switch matrix.
 * @param command could be "select row" or "select column".
 * @param message The message contains the row or column to select.
 * @return NO_ERROR if no error occurred otherwise return an error code.
 */
ErrorCode ArduinoMainController::SetRowColumn(Command command, Message message)
{
    if(!m_ConnectionEstablished)
        return DISCONNECTED;

    ErrorCode errorCode;
    if(command == SELECT_COLUMN)
        errorCode = m_MuxController->SelectColumn(message.GetParameter());
    if(command == SELECT_ROW)
        errorCode = m_MuxController->SelectRow(message.GetParameter());

    if(errorCode != NO_ERROR)
        return errorCode;

    errorCode = m_MuxController->WriteRowColumn();
    if(errorCode != NO_ERROR)
        return errorCode;
    return NO_ERROR;
}


