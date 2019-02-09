#include <FastLED.h>
#include "ESP8266WiFi.h"
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include "NTPClient.h"
#include <WiFiUdp.h>

#define FASTLED_ESP8266_D1_PIN_ORDER
#define LED_PIN    D2 //The data pin of the arduino
#define NUM_LEDS    110 //Numbers of LED
#define LED_TYPE    WS2812 //The type of the LED stripe
#define COLOR_ORDER GRB

#define LDR_PIN A0 // what pin is the LDR output connected to
#define BRIGHTNESS  100 //Base Brightness of the LEDs
#define LDR_SHIFT -500 //amount to shift the LDR value
#define LDR_FACTOR 0.1 //amount to multiply the LDR value
// formula:
// BRIGHTNESS = BRIGHTNESS + ((LDR value + LDR_SHIFT) * LDR_FACTOR)

CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 120

// WiFi parameters
//const char* ssid = "uhu-privat";
//const char* password = "privat-uhu";

// Time parameters
String hours, minutes, seconds;
int currentSecond, currentMinute, currentHour;

WiFiUDP ntpUDP;
const float UTC_OFFSET = 3600;
NTPClient timeClient(ntpUDP, "ch.pool.ntp.org", UTC_OFFSET);

void setup() {
  Serial.begin(115200);

  // Init WiFi
  WiFiManager wifiManager;            // init wifi manager
  wifiManager.resetSettings();            //mit diesem befehl kannst die gespeicherten werte löschen
  wifiManager.autoConnect("Word Clock");
  Serial.println("WiFi connected");

  //FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  timeClient.update();
  Serial.println("Current Time from NTP Server:");
  Serial.println(timeClient.getFormattedTime());
  runWhiteLed();
  fadeAll();
}

// led test, moves a white led trough the whole strip
void runWhiteLed() {
   // Move a single white led
   for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed] = CRGB::White;
      // Show the leds (only one of which is set to white, from above)
      FastLED.show();
      // Wait a little bit
      delay(10);
      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;
   }
}

void fadeAll() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void showLed(int i, int h, int s, int v) {
  leds[i] = CHSV( h, s, v );
}

void wordES( int h, int s, int v) {
  showLed(108, h, s, v);
  showLed(109, h, s, v);
}

void wordIST(int h, int s, int v) {
  showLed(103, h, s, v);
  showLed(104, h, s, v);
  showLed(105, h, s, v);
  showLed(106, h, s, v);
}

void wordFUENF(int h, int s, int v) {
  showLed(99, h, s, v);
  showLed(100, h, s, v);
  showLed(101, h, s, v);
}

void wordZEHN(int h, int s, int v) {
  showLed(96, h, s, v);
  showLed(97, h, s, v);
  showLed(98, h, s, v);
}

void wordZWANZIG(int h, int s, int v) {
  showLed(82, h, s, v);
  showLed(83, h, s, v);
  showLed(84, h, s, v);
  showLed(85, h, s, v);
  showLed(86, h, s, v);
  showLed(87, h, s, v);
}

void wordVIERTEL(int h, int s, int v) {
  showLed(88, h, s, v);
  showLed(89, h, s, v);
  showLed(90, h, s, v);
  showLed(91, h, s, v);
  showLed(92, h, s, v);
  showLed(93, h, s, v);
}

void wordNACH(int h, int s, int v) {
  showLed(66, h, s, v);
  showLed(67, h, s, v);
}

void wordVOR(int h, int s, int v) {
  showLed(77, h, s, v);
  showLed(78, h, s, v);
  showLed(79, h, s, v);
}

void wordZWOELF(int h, int s, int v) {
  showLed(0, h, s, v);
  showLed(1, h, s, v);
  showLed(2, h, s, v);
  showLed(3, h, s, v);
  showLed(4, h, s, v);
  showLed(5, h, s, v);
}

void wordHALB(int h, int s, int v) {
  showLed(69, h, s, v);
  showLed(70, h, s, v);
  showLed(71, h, s, v);
  showLed(72, h, s, v);
  showLed(73, h, s, v);
}

void wordEINS(int h, int s, int v) {
  showLed(63, h, s, v);
  showLed(64, h, s, v);
  showLed(65, h, s, v);
}

void wordZWEI(int h, int s, int v) {
  showLed(59, h, s, v);
  showLed(60, h, s, v);
  showLed(61, h, s, v);
  showLed(62, h, s, v);
}

void wordDREI(int h, int s, int v) {
  showLed(55, h, s, v);
  showLed(56, h, s, v);
  showLed(57, h, s, v);
}

void wordSIEBEN(int h, int s, int v) {
  showLed(33, h, s, v);
  showLed(34, h, s, v);
  showLed(35, h, s, v);
  showLed(36, h, s, v);
  showLed(37, h, s, v);
}

void wordSTUNDEDREI(int h, int s, int v) {
  showLed(55, h, s, v);
  showLed(56, h, s, v);
  showLed(57, h, s, v);
}

void wordSTUNDEFUENF(int h, int s, int v) {
  showLed(49, h, s, v);
  showLed(50, h, s, v);
  showLed(51, h, s, v);
  showLed(52, h, s, v);
}

void wordVIER(int h, int s, int v) {
  showLed(44, h, s, v);
  showLed(45, h, s, v);
  showLed(46, h, s, v);
  showLed(47, h, s, v);
  showLed(48, h, s, v);
}

void wordNEUN(int h, int s, int v) {
  showLed(27, h, s, v);
  showLed(28, h, s, v);
  showLed(29, h, s, v);
  showLed(30, h, s, v);
}
void wordELF(int h, int s, int v) {
  showLed(11, h, s, v);
  showLed(12, h, s, v);
  showLed(13, h, s, v);
  showLed(14, h, s, v);
}
void wordACHT(int h, int s, int v) {
  showLed(22, h, s, v);
  showLed(23, h, s, v);
  showLed(24, h, s, v);
  showLed(25, h, s, v);
  showLed(26, h, s, v);
}
void wordSTUNDEZEHN(int h, int s, int v) {
  showLed(18, h, s, v);
  showLed(19, h, s, v);
  showLed(20, h, s, v);
  showLed(21, h, s, v);
}

void wordSECHS(int h, int s, int v) {
  showLed(38, h, s, v);
  showLed(39, h, s, v);
  showLed(40, h, s, v);
  showLed(41, h, s, v);
  showLed(42, h, s, v);
  showLed(43, h, s, v);
}

void wordUHR(int h, int s, int v) {
  showLed(10, h, s, v);
  showLed(9, h, s, v);
  showLed(8, h, s, v);
}

int color() {
  return random(0, 255);
}


// Main loop
void loop() {

  // calculate brightness value
  int v = BRIGHTNESS + ((analogRead(LDR_PIN)+LDR_SHIFT)*LDR_FACTOR);
  Serial.println("Calculated Brightness...");
  Serial.println(v);

  hours = timeClient.getHours();
  minutes = timeClient.getMinutes();
  seconds = timeClient.getSeconds();

  currentHour = hours.toInt();
  if (currentHour > 12) currentHour = currentHour - 12;
  currentMinute = minutes.toInt();
  currentSecond = seconds.toInt();
  wordES(color(), color(), v);
  wordIST(color(), color(), v);

  if (currentMinute >= 2 && currentMinute < 7) {
    wordFUENF(color(), color(), v);
    wordNACH(color(), color(), v);
  }
  if (currentMinute >= 7 && currentMinute < 12) {
    wordZEHN(color(), color(), v);
    wordNACH(color(), color(), v);
  }
  if (currentMinute >= 12 && currentMinute < 17) {
    wordVIERTEL(color(), color(), v);
    wordNACH(color(), color(), v);
  }
  if (currentMinute >= 17 && currentMinute < 22) {
    wordZWANZIG(color(), color(), v);
    wordNACH(color(), color(), v);
  }
  if (currentMinute >= 22 && currentMinute < 27) {
    wordFUENF(color(), color(), v);
    wordVOR(color(), color(), v);
    wordHALB(color(), color(), v);
    currentHour += 1;
  }
  if (currentMinute >= 27 && currentMinute < 32) {
    wordHALB(color(), color(), v);
    currentHour += 1;
  }
  if (currentMinute >= 32 && currentMinute < 37) {
    wordFUENF(color(), color(), v);
    wordNACH(color(), color(), v);
    wordHALB(color(), color(), v);
    currentHour += 1;
  }
  if (currentMinute >= 37 && currentMinute < 42) {
    wordZWANZIG(color(), color(), v);
    wordVOR(color(), color(), v);
    currentHour += 1;
  }
  if (currentMinute >= 42 && currentMinute < 47) {
    wordVIERTEL(color(), color(), v);
    wordVOR(color(), color(), v);
    currentHour += 1;
  }
  if (currentMinute >= 47 && currentMinute < 52) {
    wordZEHN(color(), color(), v);
    wordVOR(color(), color(), v);
    currentHour += 1;
  }
  if (currentMinute >= 52 && currentMinute < 57) {
    wordZEHN(color(), color(), v);
    wordVOR(color(), color(), v);
    currentHour += 1;
  }
  if (currentMinute >= 57 && currentMinute <= 59 ) {
    currentHour += 1;
  }
  if (currentHour > 12) currentHour = currentHour - 12;

  switch (currentHour) {
    case 1:
      wordEINS(color(), color(), v);
      break;
    case 2:
      wordZWEI(color(), color(), v);
      break;
    case 3:
      wordSTUNDEDREI(color(), color(), v);
      break;
    case 4:
      wordVIER(color(), color(), v);
      break;
    case 5:
      wordSTUNDEFUENF(color(), color(), v);
      break;
    case 6:
      wordSECHS(color(), color(), v);
      break;
    case 7:
      wordSIEBEN(color(), color(), v);
      break;
    case 8:
      wordACHT(color(), color(), v);
      break;
    case 9:
      wordNEUN(color(), color(), v);
      break;
    case 10:
      wordSTUNDEZEHN(color(), color(), v);
      break;
    case 11:
      wordELF(color(), color(), v);
      break;
    case 12:
      wordZWOELF(color(), color(), v);
      break;
    case 0:
      wordZWOELF(color(), color(), v);
      break;
  }

  FastLED.show();

  delay(60000);
  fadeAll();
}
