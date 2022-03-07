# Measurement Switch Matrix

This repository contains a description of the NanoSEC switch matrix, as well as all the relevant source code, 
to control the board. 

![Switch Matrix](documentation/figures/Motherboard.jpg)

### 1. Circuit description 

The circuit is subdivided into two parts, a **control part** and a measurement part. 
The measurement part consists of a 12 V power supply forwarded to four darlington arrays (ULN2003APW), which are responsible
for switching the Finder 40.41 relays. Single lines on the darlington arrays are controlled by two 2/16 ADG726 multiplexers. 
The multiplexer transform a four bit input address signal to a parallel output signal which selects a specific row and column relay
over the Darlington arrays. The multiplexers are controlled by a Arduino Nano.

The measurement part consists of four BNC connectors I_D, V_DS, V_GS and GND.
V_DS connects is forwarded to each CNT_FETs on the matrix not switched. 
I_D is forwarded to the selected row.
GND is forwarded to the selected column.
V_GS is connected to the global gate.

![PCB_Layout](documentation/figures/PCB_Layout.png)

#### 1.1 Overview Components

This table contains an overview of the components on the Motherboard. 
Each component is identified by a Symbol ID.

| Symbol | Component         | Description                                            |
|:------:|:-----------------:|:------------------------------------------------------:|
| U1     | [5-1634556-0-1 ](https://www.mouser.de/datasheet/2/418/7/ENG_CD_1634556_G2-2014703.pdf). | PCI-E M.2 Key M connector to mount the daugher boards  |
| U2     | [ALN2003APW](https://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fuln2003a). | Darlington arrays consists of two transistors to forward 12V to the relays controlled by a 3V control signal (Responsible for relay 19 - 23 column). |
| U3     | [ALN2003APW](https://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fuln2003a). | Darlington arrays consists of two transistors to forward 12V to the relays controlled by a 3V control signal (Responsible for relay 7 - 12 column). |
| U4     | [ADG726 Multiplexer](https://www.mouser.de/datasheet/2/609/ADG726_732-1503078.pdf). | 2x16 Multiplexer to forward parallel lines to the Darlington Arrays controlled by a 4-bit column address. |
| U5     | [ALN2003APW](https://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fuln2003a). | Darlington arrays consists of two transistors to forward 12V to the relays controlled by a 3V control signal (Responsible for relay 1 - 6 row). |
| U6     | [ALN2003APW](https://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fuln2003a). | Darlington arrays consists of two transistors to forward 12V to the relays controlled by a 3V control signal (Responsible for relay 13 - 18 row). |
| U7     | [5-1634556-0-1 ](https://www.mouser.de/datasheet/2/418/7/ENG_CD_1634556_G2-2014703.pdf). | Angled BNC connector to connect the V_GS signal. |
| U8     | [5-1634556-0-1 ](https://www.mouser.de/datasheet/2/418/7/ENG_CD_1634556_G2-2014703.pdf).     | Angled BNC connector to connect the V_DS signal. |
| U9     | [5-1634556-0-1 ](https://www.mouser.de/datasheet/2/418/7/ENG_CD_1634556_G2-2014703.pdf).     | Angled BNC connector to connect the I_D signal. |
| U10    | [5-1634556-0-1 ](https://www.mouser.de/datasheet/2/418/7/ENG_CD_1634556_G2-2014703.pdf).     | Angled BNC connector to connect the GND signal. |
| U11    | [ADG726 Multiplexer](https://www.mouser.de/datasheet/2/609/ADG726_732-1503078.pdf).        | 2x16 Multiplexer to forward parallel lines to the Darlington Arrays controlled by a 4-bit row address. |
| K1-K12 | [Finder 0.51.9.012.0000 ](https://asset.re-in.de/add/160267/c1/-/en/001419701DS02/DA_Finder-40.51.9.012.0000-Printrelais-12-V-DC-10A-1-Wechsler-1St..pdf)  | Single Pole Double Throw Relay to select a column on the daugherboard and forward GND to the CNT FET if not switched V_DS is forwarded | 
| K13-K24 | [Finder 0.51.9.012.0000 ](https://asset.re-in.de/add/160267/c1/-/en/001419701DS02/DA_Finder-40.51.9.012.0000-Printrelais-12-V-DC-10A-1-Wechsler-1St..pdf). | Single Pole Double Throw Relay to select a row on the daugherboard and forward I_D to the CNT FET if not switched V_DS is forwarded |
| R1 | Diode xx  |  |
| C1 | Capacitor xx  | Stabilizes possible variations caused by the DC power supply |
| A1 | [Arduino Nano Connector](https://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf). | Pin Socket connector Pitch 2.54 to connect an Arduino Nano to the board |
| J1 | DA selector | Debugging Pin to connect the Data output (here data output serves as input and is forwarded to the parallel lines) connectors of U4 (Lower Row) and CS signal of U11 (Upper Row) with the 3.3V pin of the Arduino. The rows must be connected horizontally by a 2.54mm Jumper |
| J2 | CS selector | Debugging Pin to connect the CS signal of U4 (Lower Row) and CS signal of U11 (Upper Row) with D3 and D2 pin of the Arduino. The rows must be connected horizontally by a 2.54mm Jumper |
| J3 | WE selector | Debugging Pin to connect the WE signal of U4 (Lower Row) and CS signal of U11 (Upper Row) with D9 and D10 pin of the Arduino. The rows must be connected horizontally by a 2.54mm Jumper |
| J4 | EN selector | Debugging Pin to connect the EN signal of U4 (Lower Row) and EN signal of U11 (Upper Row) with A4 and A5 pin of the Arduino. The rows must be connected horizontally by a 2.54mm Jumper |
| J5 | Arduino additional pin header  | Additional pin header to access UART TX and RX pins as well as GND and the SPI interface of the Arduino Nano |
| J6 | [BarrelJack Wuerth 6941xx301002 ](http://katalog.we-online.de/em/datasheet/6941xx301002.pdf).  | Wuerth electronics barrel jack connector (5.5mm outher diameter, inner diameter 2.55mm) used to connect a 12V power supply used to switch the relays |
| J7 | Shielding connector  | Pin header to connect the GND BNC connector U10 with the shielding of all other BNC connectors by using a 2.54mm Jumper. |
| J9 | Ground Pad connector  | Pin header to connect the daughter board ground connector with the GND BNC connector U10. |
| J10 | V_DS connector  | Connector to forward V_DS to the row and column relays. Must be connected by a 2.54mm jumper. |
| MP* | Mounting holes  | To mount the board using M2 or M3 screws to a holder or case. The four mounting holes in the vicinity of the M.2 interface are used to mount holders for the daugherboard. The hole are placed according to the PC/104 EBX standard. | 

#### 1.2 Connections 

The following tables contain the connections between the components described in 1.1.

#### 1.2.1 Connections Arduino - ADG726 Multiplexer (M1)


| Pin Arduino | Description | ADG726 (U4) | Description   |
|:-----------:|:-----------:|:-----------:|:-------------:|
| Pin 16      |     3.3V    |  Pin 13     | VDD           |
| Pin 16      |     3.3V    |  Pin 14     | VDD           |
| Pin 4/29    |     GND     |  Pin 23     | GND           |
| Pin 4/29    |     GND     |  Pin 24     | VSS           |  
| Pin 5       |     A2      |  Pin 19     | CSA           |
| Pin 5       |     A2      |  Pin 20     | CSB           |
| Pin 12      |     D9      |  Pin 21     | WR            |
| Pin 23      |     A4      |  Pin 22     | EN            |
| Pin 16      |     3.3V    | Pin 43      | DA            |   
| Pin 19      |     A0      | Pin 15      | A0            |
| Pin 20      |     A1      | Pin 16      | A1            |
| Pin 21      |     A2      | Pin 17      | A2            |
| Pin 22      |     A3      | Pin 18      | A3            |

<BR>

##### 1.2.2 Connections Darlington Array (U3) - ADG726 (U4)

| Darlington U3  | Description | Pin ADG726 (U4) | Description  |
|:--------------:|:-----------:|:---------------:|:------------:|
| Pin  1         |     I1      | Pin 1           | S12A         |       
| Pin  2         |     I2      | Pin 2           | S11A         |      
| Pin  3         |     I3      | Pin 3           | S10A         |     
| Pin  4         |     I4      | Pin 4           |  S9A         |
| Pin  5         |     I5      | Pin 5           |  S8A         |     
| Pin  6         |     I6      | Pin 6           |  S7A         |     
| Pin  8         |     GND      | Pin 4/29       |  GND         |    

<BR>

##### 1.2.3 Connections Darlington Array (U3) - ADG726 (U4)

| Darlington U2  | Description | Pin ADG726 (U4) | Description  |
|:--------------:|:-----------:|:---------------:|:------------:|
| Pin  1         |     I1      | Pin 7           |  S8A        |       
| Pin  2         |     I2      | Pin 8           |  S7A         |      
| Pin  3         |     I3      | Pin 9           |  S6A         |     
| Pin  4         |     I4      | Pin 10          |  S5A         |
| Pin  5         |     I5      | Pin 11          |  S4A         |     
| Pin  6         |     I6      | Pin 12          |  S3A         |     
| Pin  8         |     GND      | Pin 4/29       |  GND         |    

<BR>


#### 1.2.4 Connections Arduino - ADG726 Multiplexer (M2)


| Pin Arduino | Description | ADG726 (U11) | Description   |
|:-----------:|:-----------:|:-----------:|:-------------:|
| Pin 16      |     3.3V    |  Pin 13     | VDD           |
| Pin 16      |     3.3V    |  Pin 14     | VDD           |
| Pin 4/29    |     GND     |  Pin 23     | GND           |
| Pin 4/29    |     GND     |  Pin 24     | VSS           |  
| Pin 6       |     D3      |  Pin 19     | CSA           |
| Pin 6       |     D3      |  Pin 20     | CSB           |
| Pin 13      |    D10      |  Pin 21     | WR            |
| Pin 24      |     A5      |  Pin 22     | EN            |
| Pin 16      |     3.3V    | Pin 43      | DA            |   
| Pin 8       |     D5      | Pin 15      | A0            |
| Pin 9       |     D6      | Pin 16      | A1            |
| Pin 10      |     D7      | Pin 17      | A2            |
| Pin 11      |     D8      | Pin 18      | A3            |


<BR>

##### 1.2.5 Connections Darlington Array (U3) - ADG726 (U4)

|     Pin U6     | Description | Pin ADG726 (U11) | Description  |
|:--------------:|:-----------:|:---------------:|:------------:|
| Pin  1         |     I1      | Pin 6           | S7A         |       
| Pin  2         |     I2      | Pin 5           | S8A         |      
| Pin  3         |     I3      | Pin 4           | S9A         |     
| Pin  4         |     I4      | Pin 3           |  S10A         |
| Pin  5         |     I5      | Pin 2           |  S11A         |     
| Pin  6         |     I6      | Pin 1           |  S12A         |     
| Pin  8         |     GND      | Pin 4/29       |  GND         |    
<BR>

##### 1.2.6 Connections Darlington Array (U3) - ADG726 (U4)

|     Pin U5     | Description | Pin ADG726 (U11) | Description  |
|:--------------:|:-----------:|:---------------:|:------------:|
| Pin  1         |     I1      | Pin 12           |  S3A        |       
| Pin  2         |     I2      | Pin 11           |  S4A         |      
| Pin  3         |     I3      | Pin 10           |  S5A         |     
| Pin  4         |     I4      | Pin 9            |  S6A         |
| Pin  5         |     I5      | Pin 8            |  S7A         |     
| Pin  6         |     I6      | Pin 7            |  S8A         |

<BR>

##### 1.2.7 Connections Darlington Array COM -GND (U2, U3, U5, U6)

|     Pin U2, U3, U5, U6     | Description | Component (Pin) | Description  |
|:--------------:|:-----------:|:---------------:|:------------:|
| Pin  8         |     GND      | Arduino Pin (Pin 4/29), J6 (GND)    |  GND         |    
| Pin  9         |     COM      | J6 (VDD)       |  12 V Power Supply         |    


<BR>

##### 1.2.8 Connections M.2 interface (J1)


|     Pin J1     | Description | Component            | Description  |
|:--------------:|:-----------:|:--------------------:|:------------:|
| Pin  1         |  GND Pad    | J9 |  Connected with ground pad connector forwarded to BNC GND (U10)        |       
| Pin  3         |     Row 1      | K13 | Connected to Relay output (Pin 11). Line length: 318 mm|     
| Pin  5         |     Row 2      | K14 | Connected to Relay output (Pin 11). Line length: 318 mm |    
| Pin  7         |     Row 3      | K15 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  9         |     Row 4      | K16 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  11         |     Row 5     | K17 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  13         |     Row 6     | K18 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  15         |     Column 1  | K1 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  17         |     Column 2  | K3 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  19         |     Column 3  | K5 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  21         |     Column 4  | K7 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  23         |     Column 5  | K9 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  25         |     Column 6  | K11 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  27         |     Row 7      | K19 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  29         |     Row 8      | K20 | Connected to Relay output (Pin 11). Line length: 318 mm |     
| Pin  31         |     Row 9      | K21 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  33         |     Row 10      | K22 | Connected to Relay output (Pin 11). Line length: 318 mm |     
| Pin  35         |     Row 11     | K23 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  37         |     Row 12     | K24 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  39         |     Column 7      | K2 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  41         |     Column 8      | K4 | Connected to Relay output (Pin 11). Line length: 318 mm |      
| Pin  43         |     Column 9      | K6 | Connected to Relay output (Pin 11). Line length: 318 mm |     
| Pin  45         |     Column 10     | K8 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  47         |     Column 11      | K10 | Connected to Relay output (Pin 11). Line length: 318 mm |     
| Pin  49         |     Column 12  | K12 | Connected to Relay output (Pin 11). Line length: 318 mm |
| Pin  53         |     V_GS  | U7 | Connected to the V_GS BNC connector. Line length: 180 mm |

<BR>

##### 1.2.9 Connections V_DS (U8)

|     Pin U7     | Description | Component            | Description  |
|:--------------:|:-----------:|:--------------------:|:------------:|
| V_GS           | Gate Source connector | J1 (Pin 53) | Connects to the common ground via the M.2 connector Pin 53 |

<BR>

##### 1.2.10 Connections V_DS (U8)

|     Pin U8     | Description | Component            | Description  |
|:--------------:|:-----------:|:--------------------:|:------------:|
| V_DS           | Drain Source connector | K 1 - K24 | Connected to the permanently connected input Pin 12 |

<BR>


##### 1.2.11 Connections I_D (U9)

Routed on the Backside. Common length of 316 mm.

|     Pin U9     | Description | Component            | Description  |
|:--------------:|:-----------:|:--------------------:|:------------:|
| I_D           | - | K 13 - K24 | Forwarded to a specific row when a row relay is switched.  |

<BR>


##### 1.2.12 Connections GND (U9)

Routed on the Backside. Common length of 140 mm.

|     Pin U9     | Description | Component            | Description  |
|:--------------:|:-----------:|:--------------------:|:------------:|
| GND           | - | K 1 - K12 | Forwarded to a specific column when a column relay is switched.  |

##### 1.2.13 Connections Arduino Breakout Pin Headers (J5)

|     Pin A1     | Description | Pin J5            | Description  |
|:--------------:|:-----------:|:--------------------:|:------------:|
| Pin 1           | Tx0 | Pin 1 | UART TX (Transmission) Pin.  |
| Pin 2           | Rx0 | Pin 2 | UART Rx (Receive) Pin.  |
| Pin 14           | SPI MOSI | Pin 3 | SPI Master out Slave in signal.  |
| Pin 15           | SPI MISO | Pin 4 | SPI Slave in Master out signal.  |
| Pin 16           | SPI SCK | Pin 5 | SPI clock signal.  |
| Pin 7           | SPI CS | Pin 6 | SPI chip select signal.  |
| Pin 4/29           | GND | Pin 7 | Ground connection.  |

<BR>


### 2. Code description 

The code is basically subdivided into two different components. 
- The **Arduino Firmware** which is the code executed on the Arduino Nano. 
It accepts commands via an UART interface and forwards the commands to the multiplexers, which switch the corresponding rows and columns.
  <br><br>
- The **Client Side API** is executed on the computer responsible for the test execution and communicates the 
commands to the Arduino Nano via an UART interface.
  
#### 2.1 Preconditions

##### 2.1.1 Installing the compilers

To compile the firmware the avr-gcc or avr-g++ compilers must be installed.
These can be installed manually or are part of the [Arduino IDE](https://www.arduino.cc/en/software).

##### 2.1.1 Installing CMAKE

Additionally, the cmake build system must be installed to build the Firmware as well as the Client Side API.

Linux: 
```
sudo apt-get install cmake
```

Windows: 

Follow this link [Cmake install](https://cmake.org/download/) and download the latest version. 


##### 2.2 Compiling the firmware

On Linux run: 

```
cd ./Arduino_Firmware
./compile.sh
```

On Windows run:

```
cd ./Arduino_Firmware
./compile.bat
```

##### 2.2 Flashing the Firmware onto the Arduino Nano

On Linux run after compiling:

```
cd ./Arduino_Firmware
./flash.sh
```

On Windows after compiling:

```
cd ./Arduino_Firmware
./flash.bat
```

##### 2.3 Communication protocol

A lightweight communication protocol is implemented on the Arduino Nano tunneled over the USB UART interface.
A UART connection is established by simply plugin in the Mini USB cable. On linux for example, the device is 
typically available under "/dev/ttyUSB0" on Windows the device can be seen in the device manager under "COMxx".

#### 2.3.1 UART properties 

|     Properties     | Values |
|:--------------:|:-----------:|
| Baudrate            | 115200  |
| Data bits           | 8  |
| Stop Bits           | 8  |
| Parity              | None  |
| Flow control        | None  |

##### 2.3.2 Commands

|     Command     | Description | Allowed values |
|:--------------:|:-----------:|:-----------:|
| connect            | Connect to the Arduino controller  | - |
| disconnect            | Disconnect the connection  | - |
| r:           | Select a row | 1- 12  |
| c:           | Select a column | 1- 12  |
| ack           | Command was acknowledged by the Arduino controller | -  |
| error:           | Error code returned by the Arduino controller |  Any error message |

Sample accessing the protocol on linux: 
```shell
$ serial /dev/ttyUSB0
$ connect
-> ack
$ row: 1
 ack
$ column: 1
 ack

$ column: 15
 error: Invalid index

$ disconnect
 ack
```
