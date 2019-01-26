//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Measurer
//. Blink (Measurement indicator)
  void msrBlink() {
    if (set.blinkLeds>1) {BlinkShort();}
  }

//. Measure temperature
  void msrT() {
    if (set.blinkLeds>1) {BlinkT();}
    // ...
  }

//. Measure relative humidity
  void msrRH() {
    if (set.blinkLeds>1) {BlinkRH();}
    // ...
  }

//. Measure pressure
  void msrP() {
    if (set.blinkLeds>1) {BlinkP();}
    // ...
  }
