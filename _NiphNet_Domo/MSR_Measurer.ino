//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Measurer
//. Blink (Measurement indicator)
  void msrBlink() {
    if (set.debug) {Serial.println ("B_");}                                      // Debug and code testing (results in Serial monitor)
    if (set.blinkLeds>1) {BlinkShort();}
  }

//. Measure temperature
  void msrT() {
    if (set.debug) {Serial.print ("T_");}                                       // Debug and code testing (results in Serial monitor)
    // ...
  }

//. Measure relative humidity
  void msrRH() {
    if (set.debug) {Serial.print ("RH_");}                                      // Debug and code testing (results in Serial monitor)
    // ...
  }

//. Measure pressure
  void msrP() {
    if (set.debug) {Serial.print ("P_");}                                       // Debug and code testing (results in Serial monitor)
    // ...
  }
