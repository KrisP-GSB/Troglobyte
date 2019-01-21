//  Commander
//. Get command
    char cmdGet(){
      char charIn = ' ';                    
      if (Serial.available() > 0) {
        charIn = Serial.read();       // Examples work with bytes (int), so not sure if this is going to work. 
      }                               // See: file:///C:/Program%20Files%20(x86)/Arduino/reference/www.arduino.cc/en/Serial/Available.html
      return charIn;                
    }

//. Commands
//..I'm Here
  void cmdImHere(){
    Serial.print("Type.Version.Serial.SensorInternal.SensorsExternal: ");
    Serial.print(tgbWhoAmI);
    Serial.print("Operational since: ");
    Serial.print(tgbStartTGB);
    BlinkImHere();
  }
//..Pauze
  void cmdPauze(){
    if (setBlink>1) {BlinkPauzeStart();}  // Lights on
    while (cmdGet() != 'P') {             // Trap in this loop until P is pressed
      delay(50);                          
    }
    BlinkPauzeEnd();                      // Lights off
  }
//..Run (command prompt)
  void cmdRun(){                    // Dummy code
    //...     // Possible starting point: https://www.arduino.cc/en/Tutorial/ShellCommands
  }
  
