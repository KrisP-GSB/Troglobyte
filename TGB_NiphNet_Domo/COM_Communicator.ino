//  Communicator
//. Detect connections
//..USB 
    boolean comUSBconnected(boolean tgbCon){
      if (!tgbCon) {                //  Not connected
        if(Serial) {                //    Serial, see: https://www.arduino.cc/reference/en/language/functions/communication/serial/ifserial/
          delay(50);                //    For debouncing during connecting
          if(Serial) {
            setBlink++;              //    Increase by one, so setBlink == 1 will pass. Next line is an example.
            if (setBlink>1) {BlinkConnected();}
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
          if (setBlink>1) {BlinkDisconnected();}
          setBlink = setBlink - 1;
          return(false);            //  Connection broken
        }
      }
    }
//..WAN 
    boolean comWANconnected(){
      return false;                 // DUMMY: false
    }

  
