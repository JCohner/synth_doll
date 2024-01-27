# Synth Doll
Was inspired to make this by a friend.

Synth Doll may be a misnomer, who knows what this will be. 

Idea is to lay the mechatronic ground work for making making music more physical. 

## Components of Repo
### Arduino Limb
An edge peripheral using a SAMD21 with integrated NINA-W102 Wifi Module[^1]. 

The idea is this limb will receive its identity via rfid tag interaction and publish its sensors on the relevant MQTT topic such that a host (body) can consome those messages and modulate a sound accordingly. 

I should and will attach a fritzing diagram.

### RFID Writer / Reader
Very simple application to read and write UIDs of nRFID tags. 
I'm getting lazy so if the above is setup for you you're in business. Makefile interfce is the same. 



[^1]: (Yes this is just a [Arduino Nano 33 IoT](https://docs.arduino.cc/hardware/nano-33-iot/) for now). 