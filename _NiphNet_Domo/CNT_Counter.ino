//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Counter
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
                  tmr.action |= 1<<(s-1);                                       //    .and flag for action (see: https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit)
                }
              }
            }
        }    
  }
