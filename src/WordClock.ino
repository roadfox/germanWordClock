#include <FastLED.h>
#include "ESP8266WiFi.h"
#include "NTPClient.h"
#include <WiFiUdp.h>

#define FASTLED_ESP8266_D1_PIN_ORDER
#define LED_PIN    D2 //The data pin of the arduino
#define NUM_LEDS    110 //Numbers of LED
#define BRIGHTNESS  140 //Brightness of the LEDs
#define NIGHT_REDUCE 40 //Amount to reduce the brightness during night hours
#define LED_TYPE    WS2812 //The type of the LED stripe
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 120

// WiFi parameters
const char* ssid = "uhu-privat";
const char* password = "privat-uhu";

String hours, minutes, seconds;
int currentSecond, currentMinute, currentHour;

WiFiUDP ntpUDP;
const float UTC_OFFSET = 3600;
NTPClient timeClient(ntpUDP, "ch.pool.ntp.org", UTC_OFFSET);

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
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
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;

  }
  FastLED.show();
}

void showLed(int i, int h, int s) {
  int v = BRIGHTNESS;
  if ( timeClient.getHours() > 20 || timeClient.getHours() < 6 ) {
    v = v - NIGHT_REDUCE;
  }
  leds[i] = CHSV( h, s, v );
}

void wordES( int h, int s) {
  showLed(108, h, s);
  showLed(109, h, s);
}

void wordIST(int h, int s) {
  showLed(103, h, s);
  showLed(104, h, s);
  showLed(105, h, s);
  showLed(106, h, s);
}
void wordFUENF(int h, int s) {
  showLed(99, h, s);
  showLed(100, h, s);
  showLed(101, h, s);
}

void wordZEHN(int h, int s) {
  showLed(96, h, s);
  showLed(97, h, s);
  showLed(98, h, s);
}

void wordZWANZIG(int h, int s) {
  showLed(82, h, s);
  showLed(83, h, s);
  showLed(84, h, s);
  showLed(85, h, s);
  showLed(86, h, s);
  showLed(87, h, s);
}

void wordVIERTEL(int h, int s) {
  showLed(88, h, s);
  showLed(89, h, s);
  showLed(90, h, s);
  showLed(91, h, s);
  showLed(92, h, s);
  showLed(93, h, s);
}

void wordNACH(int h, int s) {
  showLed(66, h, s);
  showLed(67, h, s);
}

void wordVOR(int h, int s) {
  showLed(77, h, s);
  showLed(78, h, s);
  showLed(79, h, s);
}

void wordZWOELF(int h, int s) {
  showLed(0, h, s);
  showLed(1, h, s);
  showLed(2, h, s);
  showLed(3, h, s);
  showLed(4, h, s);
  showLed(5, h, s);
}

void wordHALB(int h, int s) {
  showLed(69, h, s);
  showLed(70, h, s);
  showLed(71, h, s);
  showLed(72, h, s);
  showLed(73, h, s);
}

void wordEINS(int h, int s) {
  showLed(63, h, s);
  showLed(64, h, s);
  showLed(65, h, s);
}

void wordZWEI(int h, int s) {
  showLed(59, h, s);
  showLed(60, h, s);
  showLed(61, h, s);
  showLed(62, h, s);
}

void wordDREI(int h, int s) {
  showLed(55, h, s);
  showLed(56, h, s);
  showLed(57, h, s);
}

void wordSIEBEN(int h, int s) {
  showLed(33, h, s);
  showLed(34, h, s);
  showLed(35, h, s);
  showLed(36, h, s);
  showLed(37, h, s);
}

void wordSTUNDEDREI(int h, int s) {
  showLed(55, h, s);
  showLed(56, h, s);
  showLed(57, h, s);
}

void wordSTUNDEFUENF(int h, int s) {
  showLed(49, h, s);
  showLed(50, h, s);
  showLed(51, h, s);
  showLed(52, h, s);
}

void wordVIER(int h, int s) {
  showLed(44, h, s);
  showLed(45, h, s);
  showLed(46, h, s);
  showLed(47, h, s);
  showLed(48, h, s);
}

void wordNEUN(int h, int s) {
  showLed(27, h, s);
  showLed(28, h, s);
  showLed(29, h, s);
  showLed(30, h, s);
}
void wordELF(int h, int s) {
  showLed(11, h, s);
  showLed(12, h, s);
  showLed(13, h, s);
  showLed(14, h, s);
}
void wordACHT(int h, int s) {
  showLed(22, h, s);
  showLed(23, h, s);
  showLed(24, h, s);
  showLed(25, h, s);
  showLed(26, h, s);
}
void wordSTUNDEZEHN(int h, int s) {
  showLed(18, h, s);
  showLed(19, h, s);
  showLed(20, h, s);
  showLed(21, h, s);
}

void wordSECHS(int h, int s) {
  showLed(38, h, s);
  showLed(39, h, s);
  showLed(40, h, s);
  showLed(41, h, s);
  showLed(42, h, s);
  showLed(43, h, s);
}

void wordUHR(int h, int s) {
  showLed(10, h, s);
  showLed(9, h, s);
  showLed(8, h, s);
}

int color() {
  return random(0, 255);
}


// Main loop
void loop() {

  hours = timeClient.getHours();
  minutes = timeClient.getMinutes();
  seconds = timeClient.getSeconds();

  currentHour = hours.toInt();
  if (currentHour > 12) currentHour = currentHour - 12;
  currentMinute = minutes.toInt();
  currentSecond = seconds.toInt();
  wordES(color(), color());
  wordIST(color(), color());

  if (currentMinute >= 2 && currentMinute < 7) {
    wordFUENF(color(), color());
    wordNACH(color(), color());
  }
  if (currentMinute >= 7 && currentMinute < 12) {
    wordZEHN(color(), color());
    wordNACH(color(), color());
  }
  if (currentMinute >= 12 && currentMinute < 17) {
    wordVIERTEL(color(), color());
    wordNACH(color(), color());
  }
  if (currentMinute >= 17 && currentMinute < 22) {
    wordZWANZIG(color(), color());
    wordNACH(color(), color());
  }
  if (currentMinute >= 22 && currentMinute < 27) {
    wordFUENF(color(), color());
    wordVOR(color(), color());
    wordHALB(color(), color());
    currentHour += 1;
  }
  if (currentMinute >= 27 && currentMinute < 32) {
    wordHALB(color(), color());
    currentHour += 1;
  }
  if (currentMinute >= 32 && currentMinute < 37) {
    wordFUENF(color(), color());
    wordNACH(color(), color());
    wordHALB(color(), color());
    currentHour += 1;
  }
  if (currentMinute >= 37 && currentMinute < 42) {
    wordZWANZIG(color(), color());
    wordVOR(color(), color());
    currentHour += 1;
  }
  if (currentMinute >= 42 && currentMinute < 47) {
    wordVIERTEL(color(), color());
    wordVOR(color(), color());
    currentHour += 1;
  }
  if (currentMinute >= 47 && currentMinute < 52) {
    wordZEHN(color(), color());
    wordVOR(color(), color());
    currentHour += 1;
  }
  if (currentMinute >= 52 && currentMinute < 57) {
    wordZEHN(color(), color());
    wordVOR(color(), color());
    currentHour += 1;
  }
  if (currentMinute >= 57 && currentMinute <= 59 ) {
    currentHour += 1;
  }
  if (currentHour > 12) currentHour = currentHour - 12;

  switch (currentHour) {
    case 1:
      wordEINS(color(), color());
      break;
    case 2:
      wordZWEI(color(), color());
      break;
    case 3:
      wordSTUNDEDREI(color(), color());
      break;
    case 4:
      wordVIER(color(), color());
      break;
    case 5:
      wordSTUNDEFUENF(color(), color());
      break;
    case 6:
      wordSECHS(color(), color());
      break;
    case 7:
      wordSIEBEN(color(), color());
      break;
    case 8:
      wordACHT(color(), color());
      break;
    case 9:
      wordNEUN(color(), color());
      break;
    case 10:
      wordSTUNDEZEHN(color(), color());
      break;
    case 11:
      wordELF(color(), color());
      break;
    case 12:
      wordZWOELF(color(), color());
      break;
    case 0:
      wordZWOELF(color(), color());
      break;
  }

  FastLED.show();

  delay(60000);
  fadeAll();
}
