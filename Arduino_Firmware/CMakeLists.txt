cmake_minimum_required(VERSION 2.8.4)
if(WIN32)
	set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain_Win.cmake)
else()
	set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
endif() # if WIN32

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME nanosec_crossbar_controller)

set(${PROJECT_NAME}_BOARD nano)
#set(ARDUINO_CPU atmega328old)
set(ARDUINO_CPU atmega328old)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

option(BUILD_DOCUMENTATION "BUILD_DOCUMENTATION" ON)


include_directories("./Include")
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/build_documentation.cmake)

# Define additional source and header files or default arduino sketch files
set(${PROJECT_NAME}_SRCS
        Src/FirmwareEntry.cpp
        Src/MultiplexerController.cpp
        Src/SerialInterfaceHandler.cpp
        Src/ErrorHandler.cpp
        Src/Message.cpp
        Src/ArduinoMainController.cpp)

set(${PROJECT_NAME}_HDRS
        Include/MultiplexerController.h
        Include/SerialInterfaceHandler.h
        Include/ErrorHandler.h
        Include/ADG726Pins.h
        Include/Message.h
        Include/ArduinoMainController.h
        Include/Commands.h
        Include/ErrorCodes.h)

# Set Arduino settings
set(${PROJECT_NAME}_PROGRAMMER avrispmkii)
set(${PROJECT_NAME}_PORT /dev/ttyUSB0)
set(${PROJECT_NAME}_AFLAGS -v)

generate_arduino_firmware(${PROJECT_NAME})

if (BUILD_DOCUMENTATION)
    build_documentation()
endif () # BUILD_DOCUMENTATION
