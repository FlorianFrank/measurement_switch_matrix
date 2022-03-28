#!/usr/bin/bash
echo "PWD ${PWD}"
pushd build
cmake --build . --target upload
#../Toolchain/AVRDude/bin/avrdude -C/home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/Arduino_Firmware/Arduino_SDK/hardware/tools/avr/etc/avrdude.conf  -patmega328p -carduino -b115200 -P/dev/ttyUSB1 -D -v -Uflash:w:"${PWD}/build/Arduino_Firmware.eep":i
popd
