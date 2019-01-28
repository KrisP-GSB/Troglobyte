//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Timer
//. Correct base timer
  void tmrCheckTime(){
    if ((millis() - tmr.timer0_ms) >= tmr.sleep_ms) {                           // If delay in code execution has cause the program to run beyond the sleep time
      while ((millis() - tmr.timer0_ms) >= tmr.sleep_ms) {                      // Loop to check how many times it has run beyond 1s
        cntBase();
        tmr.timer0_ms = tmr.timer0_ms + tmr.sleep_ms;
      }
    }      
  }

//. Checking for action flag
  bool tmrAction(typSensor s) {
    if ((tmr.action >> s) & 1) {                                                // Return the n-th bit, starting with 0 (unused sensBase) for least significant bit, see: https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
      tmr.action &= ~(1 << s);                                                  // number &= ~(1UL << n);
      return true; 
    }
    return false;                                                               // Required line, will otherwise exit with 'true' (for success)
  }

//. Delay code execution                                                        // Do this to save power
  void tmrDelay(byte t) {                                                       // Delay e.g. 100 ms, or less if close to timer limit
    if ((millis() + t - tmr.timer0_ms) >= tmr.sleep_ms) {
      t = tmr.sleep_ms - (millis() - tmr.timer0_ms);                            // I am not 100% certain whether this always works correctly (because of unsigned character, running over of variables...)
      t += 10;                                                                  // Make sure it runs accross the timer limit (+10, because timer resolution/accuracy is not 1 ms, which could result in tmrCheckTime not reacting). 
      tgb.go = true;
    }
    delay(t);
    if (tgb.go) {
      tmrCheckTime();                                                           // Time limit must have been crossed passed, tmrCheckTime will take care of counters.
      tgb.go = false;                                                           // Reset generic parameter.
    }
  }
