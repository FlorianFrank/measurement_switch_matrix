/**
 * @brief This file is the starting point of the Arduino firmware, similar to a main file.
 *        It consists of a setup phase where the Switch Matrix and Arduino is initialized and a
 *        continuous loop where commands are parsed and forwarded to the switch matrix.
 * @author Florian Frank
 * @version 1.0
 */
#include "ArduinoMainController.h"

#include "Arduino.h"

ArduinoMainController mainController;

/**
 * @brief Initialization of the Arduino Nano as well as the Switch Matrix.
 */
void setup() {
    mainController.Init();
}

/**
 * @brief Loop in which the commands are parsed and forwarded to the Switch Matrix.
 */
void loop() {
    mainController.Loop();
}