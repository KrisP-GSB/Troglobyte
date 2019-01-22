//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Commander
//. Commands
//..I'm Here
  void cmdImHere(){
    Serial.print("Type.Version.Serial.SensorInternal.SensorsExternal: ");
    Serial.print(tgbWhoAmI);
    Serial.print("Operational since: ");
    Serial.println(tgbStartTGB);
    BlinkImHere();
  }
//..Pauze
  void cmdPauze(){
    if (setBlink>1) {BlinkPauzeStart();}  // Lights on
    while (comGet() != 'P') {             // Trap in this loop until P is pressed again
      delay(50);                          
    }
    BlinkPauzeEnd();                      // Lights off
  }
//..Run (command prompt)
  void cmdRun(){                    // Dummy code
    //...     // Possible starting point: https://www.arduino.cc/en/Tutorial/ShellCommands
  }
  
