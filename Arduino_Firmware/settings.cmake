option(BUILD_DOCUMENTATION "BUILD_DOCUMENTATION" OFF)
option(ARDUINO_NANO_OLD "BUILD for old Arduino Nano Board (blue)" OFF)

set(ARDUINO_BOARD_TYPE "nano") # Type like micro or nano
set(USB_PORT  "/dev/ttyUSB0") # "Set the USB port on Linux /dev/ttyUSB0 on windows COM<comID>"
set(ARDUINO_PROGRAMMER  "avrispmkii") # "Set the programmer to be used to flash the Arduino Nano"
set(CMAKE_VERBOSE_MAKEFILE on)
