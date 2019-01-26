//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Timer
//. Correct base timer
  void tmrCheckTime(){
    if ((millis() - tmr.timer0_ms) >= tmr.timerBaseMax_ms) {          // If delay in code execution has cause the program to run beyond the sleep time
      while ((millis() - tmr.timer0_ms) >= tmr.timerBaseMax_ms) {     // Loop to check how many times it has run beyond 1s
        cntBase();
        tmr.timer0_ms = tmr.timer0_ms + tmr.timerBaseMax_ms;
      }
    }      
  }
