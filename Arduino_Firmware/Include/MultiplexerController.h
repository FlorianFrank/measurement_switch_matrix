/**
 * @brief This file contains the functionality to set the row and column from the relais by controlling the ADG726 multiplexer.
 * @author Florian Frank
 * @version 1.0
 */

#ifndef MULTIPLEXER_CONTROLLER_H
#define MULTIPLEXER_CONTROLLER_H

#include "ErrorHandler.h"

#include <stdint.h>

/** Allowed range for the Row Index.  **/
#define MAX_ROWS_IDX            13
 /** Allowed range for the Column Index. Index 13 indicates that no column is chosen. */
#define MAX_COLUMNS_IDX         13

/** Index indicate, that no row is chosen.  **/
#define SELECT_NO_ROW           13
/** Index indicate, that no column is chosen.  **/
#define SELECT_NO_COLUMN        13

/**
 * @brief This class is responsible for controlling an ADG726 Multiplexer.
 * The row is set by controlling
 */
class MultiplexerController
{
public:
    MultiplexerController();
    ~MultiplexerController();

    static void InitializeMultiplexer();
    void DeInitializeMultiplexer();

    ErrorCode SelectRow(uint8_t row);
    ErrorCode SelectColumn(uint8_t column);


    ErrorCode WriteRowColumn();

private:
    uint8_t m_CurrentColumn;

    uint8_t m_CurrentRow;
    uint8_t m_LastColumn;

    uint8_t m_LastRow;

    enum RowColumnSelector {
        ROW,
        COLUMN
    };

    enum MUXChannel {
        CH_MUX1,
        CH_MUX2
    };

    static void InitializePinModes();
    static void SetPinDefaultValues();

    static ErrorCode SetAddressLines(RowColumnSelector rowColumnSelector, uint8_t address4Bit);

    static void EnableChannel(MUXChannel muxChannel);

    void WriteRowPhysical() const;
    void WriteColumnPhysical() const;

};


#endif //MULTIPLEXER_CONTROLLER_H
