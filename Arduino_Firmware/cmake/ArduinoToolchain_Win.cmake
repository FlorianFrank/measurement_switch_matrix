#=============================================================================#
# Author: Tomasz Bogdal (QueezyTheGreat)
# Home:   https://github.com/queezythegreat/arduino-cmake
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at http://mozilla.org/MPL/2.0/.
#=============================================================================#
set(CMAKE_SYSTEM_NAME Arduino)
set(ARDUINO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Arduino_SDK")

set(CMAKE_C_COMPILER   "${CMAKE_CURRENT_SOURCE_DIR}/Toolchain/SysGCC/bin/avr-gcc.exe")
set(CMAKE_CXX_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/Toolchain/SysGCC/bin/avr-g++.exe")

if (CMAKE_GENERATOR MATCHES "Ninja")
        # Force update the program to allow updating the ninja version
        # Don't worry about bad builds
        # Ninja handles this update by starting over. Here is the error message ninja gave from
        # upgrading from version 1.7 -> 1.10
        # "ninja: warning: bad deps log signature or version; starting over"
        # This is why ninja is fantastic
        message("CMAKE_MAKE_PROGRAM: ${CMAKE_CURRENT_SOURCE_DIR}")
        set(CMAKE_MAKE_PROGRAM "D:/foobar/ninja/1.10.0/ninja.exe" CACHE FILEPATH "" FORCE)
endif()


# Add current directory to CMake Module path automatically
if(EXISTS  ${CMAKE_CURRENT_LIST_DIR}/Platform/Arduino.cmake)
    set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})
endif()

#=============================================================================#
#                         System Paths                                        #
#=============================================================================#
if(UNIX)
    include(Platform/UnixPaths)
    if(APPLE)
        list(APPEND CMAKE_SYSTEM_PREFIX_PATH ~/Applications
                                             /Applications
                                             /Developer/Applications
                                             /sw        # Fink
                                             /opt/local) # MacPorts
    endif()
elseif(WIN32)
    include(Platform/WindowsPaths)
endif()


#=============================================================================#
#                         Detect Arduino SDK                                  #
#=============================================================================#
if(NOT ARDUINO_SDK_PATH)
    set(ARDUINO_PATHS)

    foreach(DETECT_VERSION_MAJOR 1)
        foreach(DETECT_VERSION_MINOR RANGE 5 0)
            list(APPEND ARDUINO_PATHS arduino-${DETECT_VERSION_MAJOR}.${DETECT_VERSION_MINOR})
            foreach(DETECT_VERSION_PATCH  RANGE 3 0)
                list(APPEND ARDUINO_PATHS arduino-${DETECT_VERSION_MAJOR}.${DETECT_VERSION_MINOR}.${DETECT_VERSION_PATCH})
            endforeach()
        endforeach()
    endforeach()

    foreach(VERSION RANGE 23 19)
        list(APPEND ARDUINO_PATHS arduino-00${VERSION})
    endforeach()

    if(UNIX)
        file(GLOB SDK_PATH_HINTS /usr/share/arduino*
            /opt/local/arduino*
            /opt/arduino*
            /usr/local/share/arduino*)
    elseif(WIN32)
        set(SDK_PATH_HINTS "C:\\Program Files\\Arduino"
            "C:\\Program Files (x86)\\Arduino"
            )
    endif()
    list(SORT SDK_PATH_HINTS)
    list(REVERSE SDK_PATH_HINTS)
endif()

find_path(ARDUINO_SDK_PATH
          NAMES lib/version.txt
          PATH_SUFFIXES share/arduino
                        Arduino.app/Contents/Resources/Java/
                        Arduino.app/Contents/Java/
                        ${ARDUINO_PATHS}
          HINTS ${SDK_PATH_HINTS}
          DOC "Arduino SDK path.")

if(ARDUINO_SDK_PATH)
    list(APPEND CMAKE_SYSTEM_PREFIX_PATH ${ARDUINO_SDK_PATH}/hardware/tools/avr)
    list(APPEND CMAKE_SYSTEM_PREFIX_PATH ${ARDUINO_SDK_PATH}/hardware/tools/avr/utils)
else()
    message(FATAL_ERROR "Could not find Arduino SDK (set ARDUINO_SDK_PATH)!")
endif()

set(ARDUINO_CPUMENU)
if(ARDUINO_CPU)
    set(ARDUINO_CPUMENU ".menu.cpu.${ARDUINO_CPU}")
endif(ARDUINO_CPU)

