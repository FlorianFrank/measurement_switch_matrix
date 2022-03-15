/**
 * @brief Header file containing the physical Pins used to control the ADG726 Multiplexer.
 * @author Florian Frank
 * @version 1.0
 */

#ifndef ARDUINO_BOARD_CONTROLLER_ADG726PINS_H
#define ARDUINO_BOARD_CONTROLLER_ADG726PINS_H

/**
 * ******************** Multiplexer 2 U4 *********************
 */

/** Pin of the Chip Select Signal for channel A (Row Selector). **/
#define MUX1_CS PIN_A4 // D2

/** Pin for the Enable Signal of the multiplexer. **/
#define MUX1_EN PIN_A4
/** Pin for the Write Enable Signal of the multiplexer. **/
#define MUX1_WE 9

/** Multiplexer 1 address line 0. **/
#define MUX1_A0 PIN_A0 // Arduino Pin A0
/** Multiplexer 1 address line 1. **/
#define MUX1_A1 PIN_A1 // Arduino Pin A1
/** Multiplexer 1 address line 2. **/
#define MUX1_A2 PIN_A2 // Arduino Pin A2
/** Multiplexer 1 address line 3. **/
#define MUX1_A3 PIN_A3 // Arduino Pin A3

/**
 * ******************** Multiplexer 2 U11 *********************
 */

/** Multiplexer 2 EN Pin **/
#define MUX2_EN PIN_A5 // Arduino Pin A5
/** Multiplexer 2 CSA & CSB. **/
#define MUX2_CS 3 // Arduino Pin D3
/** Multiplexer 2 WE. **/
#define MUX2_WE 10 // Arduino Pin D10

/** Multiplexer 2 address line 0. **/
#define MUX2_A0 5 // Arduino Pin D5
/** Multiplexer 2 address line 1. **/
#define MUX2_A1 6 // Arduino Pin D6
/** Multiplexer 2 address line 2. **/
#define MUX2_A2 7 // Arduino Pin D7
/** Multiplexer 2 address line 3. **/
#define MUX2_A3 8 // Arduino Pin D8

#endif //ARDUINO_BOARD_CONTROLLER_ADG726PINS_H
