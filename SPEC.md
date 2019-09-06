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

Serial Output
-------------

The device outputs over USB serial at baud 115200.  On boot, prints values for persistent 
settings, and the record of the main two output records:

```
# Settings loaded from EEPROM
# Settings:
# - InputDisplayPeriodMs = 250 [default]
# INPUT,Lever,Earth,Season,Mood,Future,Record,Crank
# WEATHER,temperatureC,moisture,windSpeedMs,rainFallMmMinute,rainFallMmHour,rainFallMmDay
```

Periodically prints the state of the system inputs:

```
INPUT,1,2,1,6,4,0,1
```

Which would be interpretted as:

* Lever in position 1
* Earth dial in position 2
* Season dial in position 1
* Mood dial in position 6
* Future Myth dial in position 4
* Record button not pressed
* Crank is active

When weather data is received from the remote weather station, the weather record is output:

```
WEATHER,20.37,0,0.00,0.00,0.00,0.00
```

Which would be interpretted as:

* Temperature is 20.37 degrees C
* Moisture sensor does not detect moisture
* Wind speed is 0 m/s
* There has been no rainfall in the last minute
* There has been no rainfall in the last hour
* There has been no rainfall in the last day

Serial Input
------------

Textual commands may be sent to the device over USB serial at 115200. Valid commands:

* `help` - print a help message to the serial device
* `settings` - display the currrent persistent settings (those which are saved to EEPROM)
* `reset` - reset factory detail settings and save to EEPROM
* `input [ms]` - change the period the INPUT record is displayed (parameter in milliseconds)

