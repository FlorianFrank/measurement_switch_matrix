/**
 * @brief This file contains the functionality to set the row and column from the relais by controlling the ADG726 multiplexer.
 * @author Florian Frank
 * @version 1.0
 */

#ifndef MULTIPLEXER_CONTROLLER_H
#define MULTIPLEXER_CONTROLLER_H

#include "MultiplexerDefines.h"
#include "ErrorHandler.h"

#include <stdint.h> // uint8_t

/**
 * @brief This class is responsible for controlling an ADG726 Multiplexer.
 * The row is set by controlling
 */
class MultiplexerController
{
public:
    MultiplexerController();
    ~MultiplexerController();

    void InitializeMultiplexer();
    void DeInitializeMultiplexer();

    ErrorCode SelectRow(uint8_t row);
    ErrorCode SelectColumn(uint8_t column);


    ErrorCode WriteRowColumn();

private:
    uint8_t m_CurrentColumn;

    uint8_t m_CurrentRow;
    uint8_t m_LastColumn;

    uint8_t m_LastRow;

    static void InitializePinModes();
    void SetPinDefaultValues();

    static void EnableChannel(MUXChannel muxChannel);
    static void DisableChannel(MUXChannel muxChannel);

    void WriteRowPhysical() const;
    void WriteColumnPhysical() const;

};


#endif //MULTIPLEXER_CONTROLLER_H
