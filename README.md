# Measurement Switch Matrix

This repository contains a description of the NanoSEC switch matrix, as well as all the relevant source code, 
to controll the board. 

![Switch Matrix](documentation/figures/Motherboard.jpg)

### 1. Circuit description 

The circuit is subdivided into two parts, a **control part** and a measurement part. 
The measurement part consists of a 12 V power supply forwarded to four darlington arrays (ULN2003APW), which are responsible
for switching the Finder 40.41 relays. Single lines on the darlington arrays are controlled by two 2/16 ADG726 multiplexers. 
The multiplexer transform a four bit input address signal to a parallel output signal which selects a specific row and column relay
over the Darlington arrays. The multiplexers are controlled by a Arduino Nano.

The measurement part consists of four BNC connectors $V_{ID}$, $V_{DS}$, $V_{GS}$, $V$ and GND. 

![PCB_Layout](documentation/figures/PCB_Layout.png)

#### 1.1 Overview Components

| Symbol | Component         | Description                                            |
|:------:|:-----------------:|:------------------------------------------------------:|
| U1     | MDT350M01001VT-2  | PCI-E M.2 Key M connector to mount the daugher boards  |
| U2     | ULN2003PWN        | Darlington arrays consists of two transistors to forward 12V to the relays controlled by a 3V control signal (Responsible for relay 19 - 23 column). |
| U3     | ULN2003PWN        | Darlington arrays consists of two transistors to forward 12V to the relays controlled by a 3V control signal (Responsible for relay 7 - 12 column). |
| U4     | ADG726BSUZ        | 2x16 Multiplexer to forward parallel lines to the Darlington Arrays controlled by a 4-bit column address. |
| U5     | ULN2003PWN        | Darlington arrays consists of two transistors to forward 12V to the relays controlled by a 3V control signal (Responsible for relay 1 - 6 row). |
| U6     | ULN2003PWN        | Darlington arrays consists of two transistors to forward 12V to the relays controlled by a 3V control signal (Responsible for relay 13 - 18 row). |
| U7     | 5-1634556-0-1     | Angled BNC connector to connect the V_GS signal. |
| U8     | 5-1634556-0-1     | Angled BNC connector to connect the V_DS signal. |
| U9     | 5-1634556-0-1     | Angled BNC connector to connect the I_D signal. |
| U10    | 5-1634556-0-1     | Angled BNC connector to connect the GND signal. |
| U11    | ADG726BSUZ        | 2x16 Multiplexer to forward parallel lines to the Darlington Arrays controlled by a 4-bit row address. |
| K1-K12 | Finder 0.51.9.012.0000  | Single Pole Double Throw Relay to select a column on the daugherboard and forward GND to the CNT FET if not switched V_DS is forwarded | 
| K13-K24 | Finder 0.51.9.012.0000  | Single Pole Double Throw Relay to select a row on the daugherboard and forward I_D to the CNT FET if not switched V_DS is forwarded |
| R1 | Diode xx  |  |
| C1 | Capacitor xx  | Stabilizes possible variations caused by the DC power supply |
| A1 | Adruino Nano Connector  | Pin Socket connector Pitch 2.54 to connect an Arduino Nano to the board |
| J1 | DA selector | Debugging Pin to connect the Data output (here data output serves as input and is forwarded to the parallel lines) connectors of U4 (Lower Row) and CS signal of U11 (Upper Row) with the 3.3V pin of the Arduino. The rows must be connected horizontally by a 2.54mm Jumper |
| J2 | CS selector | Debugging Pin to connect the CS signal of U4 (Lower Row) and CS signal of U11 (Upper Row) with D3 and D2 pin of the Arduino. The rows must be connected horizontally by a 2.54mm Jumper |
| J3 | WE selector | Debugging Pin to connect the WE signal of U4 (Lower Row) and CS signal of U11 (Upper Row) with D9 and D10 pin of the Arduino. The rows must be connected horizontally by a 2.54mm Jumper |
| J4 | EN selector | Debugging Pin to connect the EN signal of U4 (Lower Row) and EN signal of U11 (Upper Row) with A4 and A5 pin of the Arduino. The rows must be connected horizontally by a 2.54mm Jumper |
| J5 | Arduino additional pin header  | Additional pin header to access UART TX and RX pins as well as GND and the SPI interface of the Arduino Nano |
| J6 | BarrelJack Wuerth 6941xx301002  | Wuerth electronics barrel jack connector (5.5mm outher diameter, inner diameter 2.55mm) used to connect a 12V power supply used to switch the relays |
| J7 | Shielding connector  | Pin header to connect the GND BNC connector U10 with the shielding of all other BNC connectors by using a 2.54mm Jumper. |
| J9 | Ground Pad connector  | Pin header to connect the daughter board ground connector with the GND BNC connector U10. |
| J10 | V_DS connector  | Connector to forward V_DS to the row and column relays. Must be connected by a 2.54mm jumper. |
| MP* | Mounting holes  | To mount the board using M2 or M3 screws to a holder or case. The four mounting holes in the vicinity of the M.2 interface are used to mount holders for the daugherboard. The hole are placed according to the PC/104 EBX standard. | 

[See documentation of ADG726 Multiplexer](https://www.mouser.de/datasheet/2/609/ADG726_732-1503078.pdf).
[See documentation of Arduino Nano](https://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf).
[See documentation of ALN2003APW](https://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fuln2003a).
[See documentation of MDT350M01001VT-2](https://www.amphenol-icc.com/pcie-m-2-mdt350m01001vt.html).
[See documentation of 5-1634556-0-1 ](https://www.mouser.de/datasheet/2/418/7/ENG_CD_1634556_G2-2014703.pdf).
[See documentation of Finder 0.51.9.012.0000 ](https://asset.re-in.de/add/160267/c1/-/en/001419701DS02/DA_Finder-40.51.9.012.0000-Printrelais-12-V-DC-10A-1-Wechsler-1St..pdf).
[See documentation of BarrelJack Wuerth 6941xx301002 ](http://katalog.we-online.de/em/datasheet/6941xx301002.pdf).

#### 1.1 Connections Arduino - ADG726 Multiplexer (M1)


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

##### 1.1.2 Connections Darlington Array (U3) - ADG726 (U4)

| Darlington U3  | Description | Pin ADG726 (U4) | Description  |
|:--------------:|:-----------:|:---------------:|:------------:|
| Pin  1         |     I1      | Pin 1           | S12A         |       
| Pin  2         |     I2      | Pin 2           | S11A         |      
| Pin  3         |     I3      | Pin 3           | S10A         |     
| Pin  4         |     I4      | Pin 4           |  S9A         |
| Pin  5         |     I5      | Pin 5           |  S8A         |     
| Pin  6         |     I6      | Pin 6           |  S7A         |     
 
<BR>

##### 1.1.3 Connections Darlington Array (U3) - ADG726 (U4)

| Darlington U2  | Description | Pin ADG726 (U4) | Description  |
|:--------------:|:-----------:|:---------------:|:------------:|
| Pin  1         |     I1      | Pin 7           |  S8A        |       
| Pin  2         |     I2      | Pin 8           |  S7A         |      
| Pin  3         |     I3      | Pin 9           |  S6A         |     
| Pin  4         |     I4      | Pin 10          |  S5A         |
| Pin  5         |     I5      | Pin 11          |  S4A         |     
| Pin  6         |     I6      | Pin 12          |  S3A         |     


#### 1.2 Connections Arduino - ADG726 Multiplexer (M2)


[See documentation of ADG726 Multiplexer](https://www.mouser.de/datasheet/2/609/ADG726_732-1503078.pdf).
[See documentation of Arduino Nano](https://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf).

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

##### 1.1.2 Connections Darlington Array (U3) - ADG726 (U4)

|     Pin U3     | Description | Pin ADG726 (U6) | Description  |
|:--------------:|:-----------:|:---------------:|:------------:|
| Pin  1         |     I1      | Pin 6           | S7A         |       
| Pin  2         |     I2      | Pin 5           | S8A         |      
| Pin  3         |     I3      | Pin 4           | S9A         |     
| Pin  4         |     I4      | Pin 3           |  S10A         |
| Pin  5         |     I5      | Pin 2           |  S11A         |     
| Pin  6         |     I6      | Pin 1           |  S12A         |     
 
<BR>

##### 1.1.3 Connections Darlington Array (U3) - ADG726 (U4)

|     Pin U3     | Description | Pin ADG726 (U5) | Description  |
|:--------------:|:-----------:|:---------------:|:------------:|
| Pin  1         |     I1      | Pin 12           |  S3A        |       
| Pin  2         |     I2      | Pin 11           |  S4A         |      
| Pin  3         |     I3      | Pin 10           |  S5A         |     
| Pin  4         |     I4      | Pin 9            |  S6A         |
| Pin  5         |     I5      | Pin 8            |  S7A         |     
| Pin  6         |     I6      | Pin 7            |  S8A         |     