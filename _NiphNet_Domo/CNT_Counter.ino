//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Counter
//. Base counter
  void tmrCheckTime(){
    if ((millis() - tmrMillis0) >= tmrBaseIntMS) {          // If delay in code execution has cause the program to run beyond the sleep time
      while ((millis() - tmrMillis0) >= tmrBaseIntMS) {     // Loop to check how many times it has run beyond 1s
        cntBase();
        tmrMillis0 = tmrMillis0 + tmrBaseIntMS;
      }
    }      
  }

//. Increment base counter
  void cntBase(){
    tmrBaseCnt++;
    if (tmrBaseCnt >= tmrBaseInt) {
      tmrBaseCnt = 0;                 // Reset counter
      cntBlink();                     // Increment all other counters
      cntT();
      cntRH();
      cntP();
    }    
  }

//. Increment blink counter                               // Serves as template for all other counters
  void cntBlink(){
    if (tmrBlinkInt > 0) {                               // 0 means: no such event, so do not execute
      tmrBlinkCnt++;
      if (tmrBlinkCnt >= tmrBlinkInt) {
        tmrBlinkCnt = 0;
        tmrBlinkAction = 1;
      }
    }
  }

//. Increment temperature counter                               
  void cntT(){
    if (tmrTInt > 0) {                               // 0 means: no such event, so do not execute
      tmrTCnt++;
      if (tmrTCnt >= tmrTInt) {
        tmrTCnt = 0;
        tmrTAction = 1;
      }
    }
  }

//. Increment relative humidity counter
  void cntRH(){
    if (tmrRHInt > 0) {                               // 0 means: no such event, so do not execute
      tmrRHCnt++;
      if (tmrRHCnt >= tmrRHInt) {
        tmrRHCnt = 0;
        tmrRHAction = 1;
      }
    }
  }

//. Increment pressure counter
  void cntP(){
    if (tmrPInt > 0) {                               // 0 means: no such event, so do not execute
      tmrPCnt++;
      if (tmrPCnt >= tmrPInt) {
        tmrPCnt = 0;
        tmrPAction = 1;
      }
    }
  }
