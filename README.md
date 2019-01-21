# Arduino code for a german word clock
#  Swiss Layout adaption



- Based in mirohero's version https://github.com/mirohero/germanWordClock
- ported to PlatformIO IDE https://platformio.org/

I've printed the 96-LED word clock https://www.thingiverse.com/thing:2130830 and I didn't find flashable code for the arduino or clones like NodeMCU. So I wrote this simple, wifi-synchronized code to flash with the Arduino IDE.


1. Enter the Env settings in platformio.ini to your board specs
2. Change SSID, WiFi-password, the number of leds and the pin# in the code
3. Build and Upload the code in PlatformIO

![alt text](https://github.com/roadfox/germanWordClock/blob/master/img/img.jpg)

# TODO

- extend to 114 pixels with 4 minute led's in the corner
  - minute rounding will change completely
- port to CHSV color scheme to keep brightness over all colors the same
