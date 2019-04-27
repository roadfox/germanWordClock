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
#define BRIGHTNESS  140    // Base Brightness of the LEDs
#define LDR_SHIFT -500     // amount to shift the LDR value
#define LDR_FACTOR 0.1     // amount to multiply the LDR value
  // formula:
  // BRIGHTNESS = BRIGHTNESS + ((LDR value + LDR_SHIFT) * LDR_FACTOR)

// Time parameters
String hours, minutes, seconds;
int currentSecond, currentMinute, currentHour;

// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;

#include "led.h"
#include "clock.h"


void setup() {
  Serial.begin(115200);

  // Init WiFi
  WiFiManager wifiManager;            // init wifi manager
  //wifiManager.resetSettings();            //mit diesem befehl kannst die gespeicherten werte löschen
  wifiManager.autoConnect("Word Clock");
  Serial.println("WiFi connected");

  // Init Time
  configTime(0, 0, "ch.pool.ntp.org", "pool.ntp.org");
  setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);  // from: https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
  get_time();
  Serial.println("Startup Time: " + hours + ":" + minutes + ":" + seconds);

  //FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  runWhiteLed();
  fadeAll();
}

void get_time(){
  time_t now;
  time(&now);
  char hours_output[30], minutes_output[30], seconds_output[30];
  // See http://www.cplusplus.com/reference/ctime/strftime/ for strftime functions
  //strftime(time_output, 30, "%T", localtime(&now)); // Formats time as: 14:05:49
  strftime(hours_output, 30, "%H", localtime(&now));
  strftime(minutes_output, 30, "%M", localtime(&now));
  strftime(seconds_output, 30, "%S", localtime(&now));

  hours = hours_output;
  minutes = minutes_output;
  seconds = seconds_output;
}



// Main loop
void loop() {

  // get current time
  get_time(); // get actual Time

  // if minute changed call word display
  if (minutes.toInt() != currentMinute) {
    // calculate brightness value
    int v = BRIGHTNESS + ((analogRead(LDR_PIN)+LDR_SHIFT)*LDR_FACTOR);
    Serial.print("Calculated Brightness: ");
    Serial.println(v);
    Serial.println("Time: " + hours + ":" + minutes + ":" + seconds);
    fadeAll();
    showWords(v);
    FastLED.show();
  }

  delay(10000);

}
