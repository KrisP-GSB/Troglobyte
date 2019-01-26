//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
  void inpRead(){
    //. Timers and related counters    
      tmr.countMax[sensBase]  = 5;                                              // Take action every y counts
      tmr.countMax[sensLed]   = 1;                                              // Take action every z base counts (i.e. multiples of base counts), 
      tmr.countMax[sens01_T]  = 1;                                              // use 0 to disable (all are disabled by default).
      tmr.countMax[sens02_RH] = 12;    
      tmr.countMax[sens03_P]  = 12*60;  
    //. Other settings
      set.blinkLeds           = 1;                                              // 0: never blink, 1: blink only when connected, 2: always blink
      set.debug               = true;
  }
