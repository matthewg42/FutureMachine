Future Machine Firmware
-----------------------

Firmware on Arduino Mega to monitor inputs and weather station, and control output indicator LED.

Inputs
------

* 1 x 3-position switch (lever)
  - "big lever" with clunks. Might have three reed switches, or one potentiometer TBD
* 2 x 4-position rotary dial
  - "Earth dial"
  - "Seasons dial"
* 2 x 8-position rotary dial
  - "Mood dial"
  - "Future myth dial"
* 1 x momentary button
  - "Record button"
* 1 x crank active sensor (shorts two wires with relay when active)
* 1 x HC12 wireless serial input for receiving data from Mini Prediction Machine weather station
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

On boot, outputs record format comments:

```
#INPUT,Lever,Earth,Season,Mood,Future,Record,Crank
#WEATHER,temperatureC,moisture,windSpeedMs,rainFallMmMinute,rainFallMmHour,rainFallMmDay
```

Periodically prints the state of the system inputs:

```
INPUT,1,2,1,6,4,0,0
```

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







