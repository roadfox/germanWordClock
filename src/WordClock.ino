#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "ESP8266WiFi.h"          // or #include <WiFi.h> for ESP32
#include <WiFiManager.h>          // https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <time.h>

// LED Params
#define FASTLED_ESP8266_D1_PIN_ORDER
#define LED_PIN    D2      // The data pin of the arduino
#define NUM_LEDS    110    // Numbers of LED
#define LED_TYPE    WS2812 // The type of the LED stripe
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
#define UPDATES_PER_SECOND 120

// LDR Params

#define LDR_PIN A0         // what pin is the LDR output connected to
#define LDR_SHIFT -500     // amount to shift the LDR value
#define LDR_FACTOR 0.1     // amount to multiply the LDR value

int brightness = 181; // Base Brightness of the LEDs
// formula:
// brightness = brightness + ((LDR value + LDR_SHIFT) * LDR_FACTOR)

// Time parameters
String hours, minutes, seconds;
int currentSecond, currentMinute, currentHour;
bool refresh = false;

// Set web server port number to 80
ESP8266WebServer server(80); //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer

#include "led.h"
#include "clock.h"
#include "web.h"

void setup() {
  Serial.begin(115200);

  // Init WiFi
  WiFiManager wifiManager;            // init wifi manager
  //wifiManager.resetSettings();            //mit diesem befehl kannst die gespeicherten werte löschen
  WiFi.hostname("wordclock");
  wifiManager.autoConnect("Word Clock");
  Serial.println("WiFi connected");

  // Init Time
  configTime(0, 0, "ch.pool.ntp.org", "pool.ntp.org");
  setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);  // from: https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
  get_time();
  Serial.println("Startup Time: " + hours + ":" + minutes + ":" + seconds);

  //FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( brightness );
  runWhiteLed();
  fadeAll();

  // Init Webserver
  server.on("/", handle_index); //Handle Index page
  server.on("/all", HTTP_GET, get_all);
  server.on("/brightness/", HTTP_POST, post_brightness);
  server.begin();
}



// Main loop
void loop() {

  // get current time
  get_time(); // get actual Time

  // if minute changed call word display
  if (minutes.toInt() != currentMinute or refresh) {
    refresh = false; // reset refresh
    // calculate brightness value
    int v = brightness + ((analogRead(LDR_PIN)+LDR_SHIFT)*LDR_FACTOR);
    Serial.print("Calculated Brightness: ");
    Serial.println(v);
    Serial.println("Time: " + hours + ":" + minutes + ":" + seconds);
    // update the clock
    fadeAll();
    showWords(v);
    FastLED.show();
  }

  server.handleClient(); //Handling of incoming client requests

}
