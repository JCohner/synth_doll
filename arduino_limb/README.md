# Arduino Limb Development Interface
#### Compile and Deploy
Run `make compile` to invoke compilation 
Run `make deploy` to send compiled binaries to your board. 

## Setup
To free us from the shackles of the arduino ide but not mire us in the trenches of full force embedded development (its fun but time consuming) I elected to use `arduino-cli` and Makefile as the development interface to the project. [Install insctructions for arduino-cli](https://arduino.github.io/arduino-cli/0.35/installation/#use-the-install-script)

Output of `arduino-cli lib list` for this project

<pre>
Name              Installed Available   Location              Description
Arduino_LSM6DS3   1.0.3     -           LIBRARY_LOCATION_USER -
ArduinoMqttClient 0.1.7     -           LIBRARY_LOCATION_USER -
fast_samd21_tc    0.3.0     -           LIBRARY_LOCATION_USER -
MFRC522           1.4.11    -           LIBRARY_LOCATION_USER -
WiFiNINA          1.8.14    -           LIBRARY_LOCATION_USER -
</pre>

Run `arduino-cli core install arduino:samd` to get our board. 
Output of `arduino-cli core list`
ID                  Installed Latest Name
arduino:samd        1.8.13    1.8.13 Arduino SAMD Boards (32-bits ARM Cortex-M0+)

Also make directories `build` and `bin` in your dev environment to cache build artifacts. 

MQTT wise I am currently using [Shiftr IO Desktop](https://www.shiftr.io/desktop) as the MQTT broker; in the more finished application the broker will likely by the "body"

