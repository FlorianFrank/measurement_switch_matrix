#include "MultiplexerController.h"
#include "ADG726Pins.h"
#include "Arduino.h"

/**
 * @brief Constructor sets the maximum number of rows and columns.
 */
MultiplexerController::MultiplexerController() : m_CurrentColumn(SELECT_NO_COLUMN), m_CurrentRow(SELECT_NO_ROW),
                                                 m_LastColumn(256), m_LastRow(256)
{
}

/**
 * @brief Destructor de-initializes the multiplexer.
 */
MultiplexerController::~MultiplexerController()
{
    DeInitializeMultiplexer();
}

/**
 * @brief Initialization function enables the pin modes and initializes all lines to its default values.
 */
/*static*/ void MultiplexerController::InitializeMultiplexer()
{
    InitializePinModes();
    SetPinDefaultValues();
}

/**
 * @brief Currently not used
 */
void MultiplexerController::DeInitializeMultiplexer()
{
}

/**
 * @brief Deselect all rows and columns, set CS, EN and WE of both multiplexers to low.
 * @return
 */
/*static*/ void MultiplexerController::SetPinDefaultValues()
{
    // Deselect all rows and columns
    digitalWrite(MUX1_A0, LOW);
    digitalWrite(MUX1_A1, LOW);
    digitalWrite(MUX1_A2, LOW);
    digitalWrite(MUX1_A3, LOW);

    digitalWrite(MUX1_CS, LOW);
    digitalWrite(MUX1_EN, LOW);
    digitalWrite(MUX1_WE, LOW);

    // Deselect all rows and columns
    digitalWrite(MUX2_A0, LOW);
    digitalWrite(MUX2_A1, LOW);
    digitalWrite(MUX2_A2, LOW);
    digitalWrite(MUX2_A3, LOW);

    digitalWrite(MUX2_CS, LOW);
    digitalWrite(MUX2_EN, LOW);
    digitalWrite(MUX2_WE, LOW);
}

/*static*/ void MultiplexerController::InitializePinModes()
{

    // Initialize multiplexer 1 (U4)
    pinMode(MUX1_EN, OUTPUT);
    pinMode(MUX1_CS, OUTPUT);
    pinMode(MUX1_WE, OUTPUT);

    pinMode(MUX1_A0, OUTPUT);
    pinMode(MUX1_A1, OUTPUT);
    pinMode(MUX1_A2, OUTPUT);
    pinMode(MUX1_A3, OUTPUT);

    // Initialize multiplexer 2 (U11)
    pinMode(MUX2_EN, OUTPUT);
    pinMode(MUX2_CS, OUTPUT);
    pinMode(MUX2_WE, OUTPUT);

    pinMode(MUX2_A0, OUTPUT);
    pinMode(MUX2_A1, OUTPUT);
    pinMode(MUX2_A2, OUTPUT);
    pinMode(MUX2_A3, OUTPUT);
}

/**
 * @brief Sets the physical pins to set a row via the multiplexer 1 (U4)
 */
void MultiplexerController::WriteRowPhysical() const
{
    digitalWrite(MUX1_A0, m_CurrentRow & 1);
    digitalWrite(MUX1_A1, ((m_CurrentRow & 2) > 0) ? 1 : 0);
    digitalWrite(MUX1_A2, ((m_CurrentRow & 4) > 0) ? 1 : 0);
    digitalWrite(MUX1_A3, ((m_CurrentRow & 8) > 0) ? 1 : 0);
}

/**
 * @brief Sets the physical pins to set a row via the multiplexer 2 (U11)
 */
void MultiplexerController::WriteColumnPhysical() const
{
    digitalWrite(MUX2_A0, m_CurrentColumn & 1);
    digitalWrite(MUX2_A1, ((m_CurrentColumn & 2) > 0) ? 1 : 0);
    digitalWrite(MUX2_A2, ((m_CurrentColumn & 4) > 0) ? 1 : 0);
    digitalWrite(MUX2_A3, ((m_CurrentColumn & 8) > 0) ? 1 : 0);
}


/**
 * @brief Selects a column without physically switching the multiplexer.
 * @param column column to select.
 * @return NO_ERROR if index is valid otherwise INVALID_INDEX is returned.
 */
ErrorCode MultiplexerController::SelectColumn(uint8_t column)
{
    if (column < MAX_COLUMNS_IDX)
    {
        m_CurrentColumn = column;
    }
    else
        return INVALID_INDEX;
    return NO_ERROR;
}

/**
 * @brief Selects a row without physically switching the multiplexer.
 * @param column column to select.
 * @return NO_ERROR if index is valid otherwise INVALID_INDEX is returned.
 */
ErrorCode MultiplexerController::SelectRow(uint8_t row)
{
    if (row < MAX_ROWS_IDX)
    {
        m_CurrentRow = row;
    }
    else
        return INVALID_INDEX;
    return NO_ERROR;
}

/**
 * @brief This method writes the row and column by forwarding the commands to the two multiplexers.
 *        A switch operation is only executed when the previous index changes.
 * @return NO_ERROR if no error occurred otherwise return error code.
 */
ErrorCode MultiplexerController::WriteRowColumn()
{
    if (m_LastRow != m_CurrentRow)
    {
        EnableChannel(CH_MUX1);
        WriteRowPhysical();
        m_LastRow = m_CurrentRow;
    }

    if (m_LastColumn != m_CurrentColumn)
    {
        EnableChannel(CH_MUX2);
        WriteColumnPhysical();
        m_LastColumn = m_CurrentColumn;
    }
    return NO_ERROR;
}

/**
 * @brief Sets the Chip enable signal
 * @param muxChannel select either multiplexer 1 or multiplexer 2.
 */
/*static*/ void MultiplexerController::EnableChannel(MultiplexerController::MUXChannel muxChannel)
{
    digitalWrite(MUX1_WE, LOW);
    digitalWrite(MUX1_EN, LOW);
    digitalWrite(MUX2_WE, LOW);
    digitalWrite(MUX2_EN, LOW);

    if (muxChannel == CH_MUX1)
    {
        digitalWrite(MUX1_CS, LOW);
    } else
    {
        digitalWrite(MUX2_CS, LOW);
    }
}

