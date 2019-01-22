//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Commander
//. Get command
    char cmdGet(){
      if (Serial.available() > 0) {       // Crucial command: Serial may indicate True, when still receiving a byte. 
        return char(Serial.read());       // Code from https://www.instructables.com/id/HOW-TO-use-the-ARDUINO-SERIAL-MONITOR/ 
      }                                   // and file:///C:/Program%20Files%20(x86)/Arduino/reference/www.arduino.cc/en/Serial/Available.html
      else {
        return ' ';                       //  ' ' to be documented as: no command
      }
    }

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
    while (cmdGet() != 'P') {             // Trap in this loop until P is pressed
      delay(50);                          
    }
    BlinkPauzeEnd();                      // Lights off
  }
//..Run (command prompt)
  void cmdRun(){                    // Dummy code
    //...     // Possible starting point: https://www.arduino.cc/en/Tutorial/ShellCommands
  }
  
