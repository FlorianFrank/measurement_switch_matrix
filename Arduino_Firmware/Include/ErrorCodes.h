/**
 * @brief This file contains the list of all possible error codes, which are used in this Arduino firmware.
 * @author Florian Frank
 * @version 1.0
 */

#ifndef NANOSEC_CROSSBAR_CONTROLLER_ERRORCODES_H
#define NANOSEC_CROSSBAR_CONTROLLER_ERRORCODES_H

enum ErrorCode {
    NO_ERROR            = 0,
    /** Invalid index, e.g. invalid row or column is chosen. */
    INVALID_INDEX       = 1,
    INVALID_MESSAGE     = 2,
    INTERFACE_CLOSED    = 3,
    INVALID_LENGTH      = 4,
    INVALID_BUFFER_LEN  = 5,
    INVALID_ARGUMENT    = 6,
    INVALID_COMMAND     = 7,
    DISCONNECTED        = 8,
    NOT_INITIALIZED     = 9
};

#endif //NANOSEC_CROSSBAR_CONTROLLER_ERRORCODES_H
