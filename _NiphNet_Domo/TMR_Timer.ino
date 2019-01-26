//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Timer
//. Correct base timer
  void tmrCheckTime(){
    if ((millis() - tmrMillis0) >= tmr.timerBaseMax_ms) {          // If delay in code execution has cause the program to run beyond the sleep time
      while ((millis() - tmrMillis0) >= tmr.timerBaseMax_ms) {     // Loop to check how many times it has run beyond 1s
        cntBase();
        tmrMillis0 = tmrMillis0 + tmr.timerBaseMax_ms;
      }
    }      
  }
