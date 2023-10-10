cmake_minimum_required(VERSION 3.10)

include(${CMAKE_CURRENT_SOURCE_DIR}/settings.cmake)
set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME nanosec_crossbar_controller)
set(${PROJECT_NAME}_BOARD nano)

# Set Arduino settings
set(${PROJECT_NAME}_PROGRAMMER ${ARDUINO_PROGRAMMER})
set(${PROJECT_NAME}_PORT ${USB_PORT})
set(${PROJECT_NAME}_AFLAGS -v)

if(ARDUINO_NANO_OLD)
    set(ARDUINO_CPU atmega328old)
else()
    set(ARDUINO_CPU atmega328)
endif()

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain_Win.cmake)
else()
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
endif() # if WIN32

project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

include_directories("./Include")
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/build_documentation.cmake)

# Define additional source and header files or default arduino sketch files


set(src_files
        Src/FirmwareEntry.cpp
        Src/MultiplexerController.cpp
        Src/SerialInterfaceHandler.cpp
        Src/ErrorHandler.cpp
        Src/Message.cpp
        Src/ArduinoMainController.cpp
        Src/ethernet/EthernetCommandParser.cpp
        Src/ethernet/EthernetController.cpp)

set(headers_files
        Include/MultiplexerController.h
        Include/SerialInterfaceHandler.h
        Include/ErrorHandler.h
        Include/ADG726Pins.h
        Include/Message.h
        Include/ArduinoMainController.h
        Include/Commands.h
        Include/ErrorCodes.h
        Include/ethernet/EthernetDefines.h
        Include/ethernet/EthernetCommandParser.h
        Include/ethernet/EthernetController.h)

if(DEFINED ETHERNET_SUPPORT)
    add_definitions(-DETHERNET_SUPPORT)
    message("Build UIPEthernet library")
    file(GLOB eth_src_files ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/*.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/utility/*.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/utility/*.c
                            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/*.c
                            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/*.h
                            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/utility/*.h
                            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/tiny-json/tiny-json.c
                            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/tiny-json/tiny-json.h)

    file(GLOB eth_header_files ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/*.h
                               ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/utility/*.h)

    set(${PROJECT_NAME}_SRCS ${src_files} ${eth_src_files})
    set(${PROJECT_NAME}_HDRS ${header_files} ${eth_header_files})

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/
                        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/UIPEthernet/src/utility/
                        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/tiny-json/)
endif()


generate_arduino_firmware(${PROJECT_NAME})



if (BUILD_DOCUMENTATION)
    build_documentation()
endif () # BUILD_DOCUMENTATION
