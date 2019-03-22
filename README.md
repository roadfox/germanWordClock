# ESP8266/32 code for a german word clock
##  Swiss Layout adaption


- Based in mirohero's version https://github.com/mirohero/germanWordClock
- ported to PlatformIO IDE https://platformio.org/

I also changed the case slightly
- My version: https://www.thingiverse.com/thing:3385412
- Original version: https://www.thingiverse.com/thing:2130830

## Hardware Setup

### LDR Resistor for auto brighntness
```
  3.3V                A0                 GND
   +                  +                   +
   |                  |                   |
   |     +-------+    |    +--------+     |
   +-----+ LDR   +---------+ 10k    +-----+
         +-------+         +--------+
```
If you don't have an LDR you can also connect a potentiometer instead

## Software Setup

1. Change the Env settings in platformio.ini to your board specs
2. Build and Upload the code in PlatformIO to your board
3. User your mobile phone to scan for an AP called "Word Clock"
4. Connect to this AP and configure your WiFi settings


![alt text](https://github.com/roadfox/germanWordClock/blob/master/img/img.jpg)

# TODO
- extend to 114 pixels with 4 minute led's in the corner
  - minute rounding will change completely



# DONE
- port to CHSV color scheme to get even brightness for all colors
- add a LDR resistor or BH1750 for auto brigthness adjustement
