//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Timer
//. Correct base timer
  void tmrCheckTime(){
    if ((millis() - tmr.timer0_ms) >= tmr.timerBaseMax_ms) {                    // If delay in code execution has cause the program to run beyond the sleep time
      while ((millis() - tmr.timer0_ms) >= tmr.timerBaseMax_ms) {               // Loop to check how many times it has run beyond 1s
        cntBase();
        tmr.timer0_ms = tmr.timer0_ms + tmr.timerBaseMax_ms;
      }
    }      
  }

//. Checking for action flag
  bool tmrAction(typSensor s) {
    if ((tmr.action >> s) & 1) {                                                // Return the n-th bit, starting with 0 (unused sensBase) for least significant bit, see: https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
      tmr.action &= ~(0 << s);                                                  // number &= ~(1UL << n);
      return true; 
    }
  }
