//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Commander
//. Commands
//..I'm Here
  void cmdImHere(){
    if (set.debug) {Serial.println ('?');}                                      // Debug and code testing (results in Serial monitor)
    Serial.print("Type.Version.Serial.SensorInternal.SensorsExternal: ");
    Serial.println(inf.tgbWhoAmI);
    Serial.print("Operational since: ");
    Serial.println(inf.tgbStartTGB);
    BlinkImHere();
  }
//..Pauze
  void cmdPauze(){
    if (set.debug) {Serial.println ('P');}                                      // Debug and code testing (results in Serial monitor)
    if (set.blinkLeds>1) {BlinkPauzeStart();}                                   // Lights on
    while (comGet() != 'P') {                                                   // Trap in this loop until P is pressed again
      delay(50);                          
    }
    if (set.debug) {Serial.println ('P');}                                      // Debug and code testing (results in Serial monitor)
    BlinkPauzeEnd();                                                            // Lights off
  }
//..Run (command prompt)
  void cmdRun(){                                                                // Dummy code
    //...                                                                       // Possible starting point: https://www.arduino.cc/en/Tutorial/ShellCommands
  }
  
