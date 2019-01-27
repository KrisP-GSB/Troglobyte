//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
#include "HDR_Header.h"
//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void setup() {
  //  Initialise
  //. Hardware
      pinMode(pin.led00, OUTPUT);                                               // Pins are input by default
      Serial.begin(9600);                                                       // 9600 is default communication speed for most Arduinos
  //. User input
      inpRead();                                                                // DUMMY: these variables will be provided externally, or have been stored in case of reboot
  //. Action flags
      for (int s = sensLed; s > sensBase;  s--) {                               // Flagging all sensors for action before entering loop
        tmr.action |= (tmr.countMax[s] > 0) << s;                               // Explanation, see: https://github.com/KrisP-GSB/Troglobyte/wiki/Initiate-sensor-actions
      }
  //  Last things to do
      ledInitialised();                                                         // Three distincitve blinks to mark start (other native, always shorter blinks will have occured before)
      tmr.timer0_ms = millis();                                                 // Reset the timer
}
//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void loop() { 
  //  User commands  
  com.USB = comUSBconnected(com.USB);                                           // Works as far as tested (i.e. it always detects the USB serial connection)
  com.WAN = comWANconnected();                                                  // DUMMY (always false)
  if (com.USB || com.WAN) {
    switch(comGet()) {                                                          // Reacting to commands. Note that even cmdGet is an int, and so is a character between single quotes ('')! (Only double quotes indicate a char/string.)
      tgb.go = true;                                                            // Did the command result in a delay? True for most commands
      case 0: tgb.go = false; break;                                            // Most common 'action': Nohting received, no delay 
      case '?': cmdImHere(); break;                                                              
      case 'R': cmdRun(); break;                                                // Open command prompt to receive commands (pauzes all activities)
      case 'P': cmdPauze(); break;                                              // Suspend all actions untill P is pressed again
      case 'S': // cmdStopMeasuring(); break;                                   // Be careful with this, needs certainty to be turned on again
      case 'T': // LiveMeasureT(); break; 
      case 'M': // LiveMeasureAll(); break; 
      case '>': // cmdPlay(); break;                                            // Dump all data to serial
      default: Serial.println("Unknown command"); break;                        // No command or command not recognised 
    }
    if (tgb.go) {tmrCheckTime(); tgb.go = false;}                               // Correct timer (only necessary when there were delays, command actions). Also reset the generic variable to default.
  }

  //  Automatic measurements
  if (tmrAction(sens01_T )) {msrT();      tmrCheckTime();}                      // Record sensor 01: T
  if (tmrAction(sens02_RH)) {msrRH();     tmrCheckTime();}                      // Record sensor 02: RH
  if (tmrAction(sens03_P )) {msrP();      tmrCheckTime();}                      // Record sensor 03: P
  //...                                                                         // Placeholder for other sensors (up to sensor 14)
  if (tmrAction(sensLed  )) {msrBlink();  tmrCheckTime();}                      // Place last: a blink not followed by a pauze

  //  Sleep or delay                                                            // Depending on whether connected
  if (com.USB || com.WAN) {
    delay(100);                                                                 // Stay responsive. Delay of 100 ms is acceptable for most input.
    tmrCheckTime();
  } else {
    tmpSleep();                                                                 // Sleep until next second has passed, and increase counters.
  }
}
//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
