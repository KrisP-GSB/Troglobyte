//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
  void inpRead(){
    tmrBaseInt  = 5;    // Take action every y counts
    tmrBlinkInt = 0;    // Take action every z base counts (i.e. multiples of base counts), 
    tmrTInt     = 1;    // use 0 to disable
    tmrRHInt    = 12;    
    tmrPInt     = 12*60;  
    tmrXInt     = 1;  

    setBlink    = 1;    // 0: never blink, 1: blink only when connected, 2: always blink
  }
