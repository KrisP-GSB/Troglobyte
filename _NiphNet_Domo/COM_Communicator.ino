//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Communicator
//. Get command
    int comGet(){
      if (Serial.available() > 0) {       // Crucial command: Serial may indicate True, when still receiving a byte. 
        return Serial.read();             // Code from https://www.instructables.com/id/HOW-TO-use-the-ARDUINO-SERIAL-MONITOR/ 
      }                                   // and file:///C:/Program%20Files%20(x86)/Arduino/reference/www.arduino.cc/en/Serial/Available.html
      else {                              // and example switchCase2
        return 0;                       //  0 is the NULL in ASCII (0 is 48)
      }
    }

//. Detect connections
//..USB 
    boolean comUSBconnected(boolean tgbCon){
      if (!tgbCon) {                //  Not connected
        if(Serial) {                //    Serial, see: https://www.arduino.cc/reference/en/language/functions/communication/serial/ifserial/
          delay(50);                //    For debouncing during connecting
          if(Serial) {
            set.blinkLeds++;              //    Increase by one, so set.blinkLeds == 1 will pass. Next line is an example.
            if (set.blinkLeds>1) {BlinkConnected();}
            return(true);           //    If still connected, will return true
          } else {
            return(false);
          }
        } else {
          return(false);
        }
      } else {                      // Connected
        if (Serial) { 
          return(true);             //  Confirm connection (no debouncing needed)
        } else {
          if (set.blinkLeds>1) {BlinkDisconnected();}
          set.blinkLeds--;
          return(false);            //  Connection broken
        }
      }
    }
//..WAN 
    boolean comWANconnected(){
      return false;                 // DUMMY: false
    }

  
