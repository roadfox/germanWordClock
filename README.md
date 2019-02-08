# ESP8266/32 code for a german word clock
##  Swiss Layout adaption


- Based in mirohero's version https://github.com/mirohero/germanWordClock
- ported to PlatformIO IDE https://platformio.org/

I also changed the case slightly
- My version: https://www.thingiverse.com/thing:3385412
- Original version: https://www.thingiverse.com/thing:2130830

## Setup

1. Change the Env settings in platformio.ini to your board specs
2. Change SSID, WiFi-password and the pin# where the led strip is connected src/WordClock.ino
3. Build and Upload the code in PlatformIO to your board

![alt text](https://github.com/roadfox/germanWordClock/blob/master/img/img.jpg)

# TODO
- extend to 114 pixels with 4 minute led's in the corner
  - minute rounding will change completely
- add a LDR resistor or BH1750 for auto brigthness adjustement

```
  3.3V                A0                 GND
   +                  +                   +
   |                  |                   |
   |     +-------+    |    +--------+     |
   +-----+ LDR   +---------+ 10k    +-----+
         +-------+         +--------+
```


# DONE
- port to CHSV color scheme to get even brightness for all colors
