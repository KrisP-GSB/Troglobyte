//  Measurer
//. Blink (Measurement indicator)
  void msrBlink() {
    if (setBlink>1) {BlinkShort();}
  }

//. Measure temperature
  void msrT() {
    if (setBlink>1) {BlinkT();}
    // ...
  }

//. Measure relative humidity
  void msrRH() {
    if (setBlink>1) {BlinkRH();}
    // ...
  }

//. Measure pressure
  void msrP() {
    if (setBlink>1) {BlinkP();}
    // ...
  }

//. Measure X (placeholder for additional sensor)
  void msrX() {
    if (setBlink>1) {BlinkX();}
    // ...
  }
