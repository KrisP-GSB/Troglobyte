//  Sleep functionality
//. Sleep lookalike
  void tmpSleep() {
    cntBase();            // Increase base and other counters
    delay(1000);          // Dummy code: replace by 'sleep until second has passed'
    tmrMillis0 = millis(); // Reset the milli second counter
  }
