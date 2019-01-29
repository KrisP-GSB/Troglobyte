//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Measurer
//. Blink (Measurement indicator)
  void msrBlink() {
    if (set.debug) {dbgSerialPrintLn("B_");}                                     // Debug and code testing (results in Serial monitor)
    if (set.blinkLeds>1) {ledShort();}
  }

//. Measure temperature
  void msrT() {
    if (set.debug) {dbgSerialPrint("T_");}                                       // Debug and code testing (results in Serial monitor)
    // ...
  }

//. Measure relative humidity
  void msrRH() {
    if (set.debug) {dbgSerialPrint("RH_");}                                      // Debug and code testing (results in Serial monitor)
    // ...
  }

//. Measure pressure
  void msrP() {
    if (set.debug) {dbgSerialPrint("P_");}                                       // Debug and code testing (results in Serial monitor)
    // ...
  }
