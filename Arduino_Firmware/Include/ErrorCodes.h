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
    /** Message received from the UART interface is invalid. */
    INVALID_MESSAGE     = 2,
    /** Interface is closed no actions can be executed. */
    INTERFACE_CLOSED    = 3,
    /** TODO. */
    INVALID_LENGTH      = 4,
    /** Length of input buffer is invalid. */
    INVALID_BUFFER_LEN  = 5,
    /** Invalid argument passed to a function. */
    INVALID_ARGUMENT    = 6,
    /** Command is invalid and will not be executed. */
    INVALID_COMMAND     = 7,
    /** Device is disconnected. */
    DISCONNECTED        = 8,
    /** Trying to execute a function on a not initialized structure. */
    NOT_INITIALIZED     = 9
};

#endif //NANOSEC_CROSSBAR_CONTROLLER_ERRORCODES_H
