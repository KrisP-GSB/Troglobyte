//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Counter
//. Checking for action flag
  bool tmrAction(typSensor s) {
    if ((tmr.action >> s) & 1) {                                                // Return the n-th bit, starting with 0 (unused sensBase) for least significant bit, see: https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
      tmr.action &= ~(0 << s);                                                  // number &= ~(1UL << n);
      return true; 
    }
  }

//. Increment base counter, and check other counters
  void cntBase(){
    //  Increment base counter
        tmrBaseCnt++;
    //  Maximum base counts 
        if (tmr.baseCount[sensBase] >= tmr.baseCountMax[sensBase]) {
        //. Reset base counter
            tmrBaseCnt = 0;                 
        //. Increment other counters
            for (int s = sensBase + 1; s <= sensLed; s++) {                     // Loop sensor list (discussion on: https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum)
              if (tmr.countMax[s] > 0) {                                        // 0 means: sensor disabled, so do not execute
                tmr.count[s]++;                                                 // Increment each counter
                if (tmr.count[s] >= tmr.countMax[s]) {                          // If maximum number of counts reached
                  tmr.count[s] = 0;                                             //    .then reset
                  tmr.action |= 1<<s;                                           //    .and flag for action. Note that this works, because sensBase = 0 (also: least significant bit is not used) (see: https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit)
                }
              }
            }
        }    
  }
