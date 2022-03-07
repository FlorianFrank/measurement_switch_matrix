#include <string.h>
#include "ErrorHandler.h"

/*static*/ char ErrorHandler::errorCodeBuffer[ERR_CODE_BUFFER_SIZE];


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
            strcpy(errorCodeBuffer, "NO ERROR");
            break;
            /** Invalid row or column index chosen. */
        case INVALID_INDEX:
            strcpy(errorCodeBuffer, "Invalid Index");
            break;
            /** Format of received message is invalid. */
        case INVALID_MESSAGE:
            strcpy(errorCodeBuffer, "Invalid Message");
            break;
            /** UART interface is already closed. */
        case INTERFACE_CLOSED:
            strcpy(errorCodeBuffer, "Interface Closed");
            break;
            /** TODO invalid length? */
        case INVALID_LENGTH:
            strcpy(errorCodeBuffer, "Invalid Length");
            break;
            /** The length of the buffer is invalid. */
        case INVALID_BUFFER_LEN:
            strcpy(errorCodeBuffer, "Invalid Buffer Len");
            break;
            /** Argument is invalid for current command. */
        case INVALID_ARGUMENT:
            strcpy(errorCodeBuffer, "Invalid Argument");
            break;
            /** Command is invalid. */
        case INVALID_COMMAND:
            strcpy(errorCodeBuffer, "Invalid Command");
            break;
            /** UART connection is already closed. */
        case DISCONNECTED:
            strcpy(errorCodeBuffer, "Disconnected");
            break;
            /** Trying to apply a function on an uninitialized object. */
        case NOT_INITIALIZED:
            strcpy(errorCodeBuffer, "Variable not initialized");
            break;
    }
    return errorCodeBuffer;
}
