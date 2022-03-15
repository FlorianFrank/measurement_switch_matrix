#include <string.h>
#include "ErrorHandler.h"

/*static*/ char ErrorHandler::m_ErrorCodeBuffer[ERR_CODE_BUFFER_SIZE];


/**
 * @brief This function transforms an error code to a error message as string.
 * @param errCode error code to convert
 * @return error message as string.
 */
const char *ErrorHandler::ErrorCodeToString(ErrorCode errCode)
{
    switch (errCode)
    {
            /** No error occurred. */
        case NO_ERROR:
            strcpy(m_ErrorCodeBuffer, "NO ERROR");
            break;
            /** Invalid row or column index chosen. */
        case INVALID_INDEX:
            strcpy(m_ErrorCodeBuffer, "Invalid Index");
            break;
            /** Format of received message is invalid. */
        case INVALID_MESSAGE:
            strcpy(m_ErrorCodeBuffer, "Invalid Message");
            break;
            /** UART interface is already closed. */
        case INTERFACE_CLOSED:
            strcpy(m_ErrorCodeBuffer, "Interface Closed");
            break;
            /** TODO invalid length? */
        case INVALID_LENGTH:
            strcpy(m_ErrorCodeBuffer, "Invalid Length");
            break;
            /** The length of the buffer is invalid. */
        case INVALID_BUFFER_LEN:
            strcpy(m_ErrorCodeBuffer, "Invalid Buffer Len");
            break;
            /** Argument is invalid for current command. */
        case INVALID_ARGUMENT:
            strcpy(m_ErrorCodeBuffer, "Invalid Argument");
            break;
            /** Command is invalid. */
        case INVALID_COMMAND:
            strcpy(m_ErrorCodeBuffer, "Invalid Command");
            break;
            /** UART connection is already closed. */
        case DISCONNECTED:
            strcpy(m_ErrorCodeBuffer, "Disconnected");
            break;
            /** Trying to apply a function on an uninitialized object. */
        case NOT_INITIALIZED:
            strcpy(m_ErrorCodeBuffer, "Variable not initialized");
            break;
    }
    return m_ErrorCodeBuffer;
}
