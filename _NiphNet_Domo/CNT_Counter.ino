//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Counter
//. Increment base counter
  void cntBase(){
    tmrBaseCnt++;
    if (tmr.baseCount[sensBase] >= tmr.baseCountMax[sensBase]) {
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
