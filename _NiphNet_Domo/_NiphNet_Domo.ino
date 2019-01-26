//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
#include "HDR_Header.h"
//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void setup() {
  //  Initialise
  //. Hardware
      pinMode(pin.led00, OUTPUT);                                               // Pins are input by default
  //. Communication
      Serial.begin(9600);                                                       // 9600 is default communication speed for most Arduinos
  //  Input
  //. Reading variables
      inpRead();                                                                // DUMMY: these variables will be provided externally, or have been stored in case of reboot
  //. Set Action to true
      for (int s = sensLed; s > sensBase;  s--) {                               // Flagging all sensors for action before entering loop
        tmr.action |= (tmr.countMax[s] > 0) << s;                               // Explanation, see: https://github.com/KrisP-GSB/Troglobyte/wiki/Initiate-sensor-actions
      }
  //  Last things to do
  //. Confirm proper initialisation      
      BlinkInitiateSuccess();                                                   // Three distincitve blinks to mark start (other native, always shorter blinks will have occured before)
      tmr.timer0_ms = millis();                                                 // Reset the timer
}
//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void loop() { 
  //  Receiving commands  
      com.USB = comUSBconnected(com.USB);                                       // Works as far as tested (i.e. it always detects the USB serial connection)
      com.WAN = comWANconnected();                                              // DUMMY (always false)
      if (com.USB || com.WAN) {
        switch(comGet()) {                                                      // Reacting to commands. Note that even cmdGet is an int, and so is a character between single quotes ('')! (Only double quotes indicate a char/string.)
          tgb.go = true;                                                        // Did the command result in a delay? True for most commands
          case 0: tgb.go = false; break;                                        // Most common 'action': Nohting received, no delay 
          case '?': cmdImHere(); break;                                                              
          case 'R': cmdRun(); break;                                            // Open command prompt to receive commands (pauzes all activities)
          case 'P': cmdPauze(); break;                                          // Suspend all actions untill P is pressed again
          case 'S': // cmdStopMeasuring(); break;                               // Be careful with this, needs certainty to be turned on again
          case 'T': // LiveMeasureT(); break; 
          case 'M': // LiveMeasureAll(); break; 
          case '>': // cmdPlay(); break;                                        // Dump all data to serial
          default: Serial.println("Unknown command"); break;                    // No command or command not recognised 
        }
        if (tgb.go) {tmrCheckTime(); tgb.go = false;}                           // Correct timer (only necessary when there were delays, command actions). Also reset the generic variable to default.
      }

  //  Executing measurements
      if (tmrAction(sens01_T )) {msrT();}
      if (tmrAction(sens02_RH)) {msrRH();}
      if (tmrAction(sens03_P )) {msrP();}
      //...                                                                     // Room for other sensors (up to sens14_X)
      if (tmrAction(sensLed  )) {msrBlink();}                                   // Place last: a blink not followed by a pauze

  //  Sleep or delay                                                            // Depending on whether connected
  if  (com.USB || com.WAN) {
    delay(100);                                                                 // Stay responsive. Delay of 100 ms is acceptable for most input.
    tmrCheckTime();
  } else {
    tmpSleep();                                                                 // Sleep until next second has passed, and increase counters.
  }
}
//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
