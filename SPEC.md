Future Machine Firmware
-----------------------

Firmware on Arduino Mega to monitor inputs and weather station, and control output indicator LED.

Inputs
------

* 1 x 3-position switch (lever)
  - ID = "LEV"
  - "big lever" with clunks. Might have three reed switches, or one potentiometer TBD
* 2 x 4-position rotary dial
  - "Earth dial"
    - ID = "EAR"
  - "Seasons dial"
    - ID = "SEA"
* 2 x 8-position rotary dial
  - "Mood dial"
    - ID = "MOO"
  - "Future myth dial"
    - ID = "FUT"
* 1 x momentary button
  - "Record button"
    - ID = "REC"
* 1 x crank active sensor (shorts two wires with relay when active)
  - ID = "CRA"
* 1 x HC12 wireless serial input for receiving data from Mini Prediction Machine weather station
  - ID = "WEA"
* Read serial data from USB interface for instructions from "Brain" unit to turn on/off LED

Outputs
-------

* 1 x recording indicator LED
* On state change of inputs, information is relayed to the "Brain" over serial
  according to the protocol described below.

Software Elements
-----------------

* Multi-position switch class for lever, all four dials (debounced)
* DebouncedButton class for record button
* Serial reader for weather station
* Serial reader for USB connection
* Serial sender for USB connection

Data Format
-----------

When an input state changes, it shall be relayed to the "Brain" over the USB serial connection.

* Arduino resets "RESET"
* Multi-position switch state changes:
  - LEV0, LEV1, LEV2, LEV3 
  - EAR0, EAR1, EAR2, EAR3, EAR4
  - SEA0, SEA1, SEA2, SEA3, SEA4
  - MOO0, MOO1, MOO2, MOO3, MOO4, MOO5, MOO7, MOO8
  - FUT0, FUT1, FUT2, FUT3, FUT4, FUT5, FUT7, FUT8
  - State will be sent after reset, and when a new position is selected
  - The 0 value is used only when powering on if the position cannot be determined
* DebounedButton state changes
  - REC0 (not pressed), REC1 (pressed)
  - CRA0 (not active),  CRA1 (active)
  - State will be sent after reset, and when position changes
* New weather data (TBC when I've checked what data the weather station is providing):
  - WEA,T=14.6,H=67,W=4.6,P=1004,R=0.1

Expect instructions from Brain about turning on and off LED like this: LED0, LED1

Example Serial Output
---------------------

RESET
LEV1
EAR1
SEA3
MOO7
FUT1
REC0
CRA0
WEA,T=14.6,H=67,W=4.6,P=1004,R=0.1
LEV2






Handle incoming events,and forward to Brain with 

* Serial from HC12
* Serial from USB







