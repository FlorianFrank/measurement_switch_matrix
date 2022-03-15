//
// Created by florianfrank on 15.03.22.
//

#ifndef NANOSEC_CROSSBAR_CONTROLLER_MULTIPLEXERDEFINES_H
#define NANOSEC_CROSSBAR_CONTROLLER_MULTIPLEXERDEFINES_H

enum MUXChannel {
    CH_MUX1,
    CH_MUX2
};


/** Allowed range for the Row Index.  **/
#define MAX_ROWS_IDX            13
/** Allowed range for the Column Index. Index 13 indicates that no column is chosen. */
#define MAX_COLUMNS_IDX         13

/** Index indicate, that no row is chosen.  **/
#define SELECT_NO_ROW           13
/** Index indicate, that no column is chosen.  **/
#define SELECT_NO_COLUMN        13

#endif //NANOSEC_CROSSBAR_CONTROLLER_MULTIPLEXERDEFINES_H
