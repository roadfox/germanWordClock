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



int color() {
  return random(0, 255);
}
