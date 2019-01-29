//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Commander
//. Commands
//..I'm Here
  void cmdImHere(){
    if (set.debug) {dbgSerialPrintLn("?");}                                      // Debug and code testing (results in Serial monitor)
    Serial.print("Type.Version.Serial.SensorInternal.SensorsExternal: ");
    Serial.println(inf.tgbWhoAmI);
    Serial.print("Operational since: ");
    Serial.println(inf.tgbStartTGB);
    ledImHere();
  }
//..Pauze
  void cmdPauze(){
    if (set.debug) {dbgSerialPrintLn("P");}                                      // Debug and code testing (results in Serial monitor)
    if (set.blinkLeds>1) {ledPauzeStart();}                                     // Lights on
    while (comGet() != 'P') {                                                   // Trap in this loop until P is pressed again
      delay(50);                          
    }
    if (set.debug) {dbgSerialPrintLn("P");}                                      // Debug and code testing (results in Serial monitor)
    ledPauzeEnd();                                                              // Lights off
  }
//..Run (command prompt)
  void cmdRun(){                                                                // Dummy code
    //...                                                                       // Possible starting point: https://www.arduino.cc/en/Tutorial/ShellCommands
  }
  
