/**
 * @brief This file is responsible for the error handling within the firmware.
 * It contains a function to convert error codes into string error messages.
 * @author Florian Frank
 * @version 1.0
 */

#ifndef ARDUINO_BOARD_CONTROLLER_ERRORHANDLER_H
#define ARDUINO_BOARD_CONTROLLER_ERRORHANDLER_H

#include "ErrorCodes.h"

/** Maximum size of the buffer containing the error message */
#define ERR_CODE_BUFFER_SIZE 128

class ErrorHandler
{
public:
    static const char* ErrorCodeToString(ErrorCode errCode);

private:
    static char errorCodeBuffer[ERR_CODE_BUFFER_SIZE];
};



#endif //ARDUINO_BOARD_CONTROLLER_ERRORHANDLER_H
