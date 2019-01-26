//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Initialise
  //  Pin assignments
      struct {
        const int led00 = LED_BUILTIN;                                          // pin.led00 - LED_BUILTIN points to the internal led, D13 on the Nano (see https://www.arduino.cc/en/Tutorial/Blink)
        const int led01 = 0;                                                    //    .led01 - Open slots for three external leds (not compiled if not used)
        const int led02 = 0;                                                    //    .led02
        const int led03 = 0;                                                    //    .led03
      } pin;
      
  //  Naming
      enum typSensor {                                                          // Explicitly naming the sensors
        sensBase, sens01_T, sens02_RH,                                          // sensBase and sensLed mark start and beginning of enum list
        sens03_P,                                                               // Insert up to 'sens14_X' depending on how many sensors are active
        sensLed                                                                 // Only other updates needed: input parameters need to be set, and the 'executing measurements'
      };                                                          

  //  Communication
      struct {
        boolean USB = false;                                                    // com.USB - USB serial connection detected
        boolean WAN = false;                                                    //    .WAN - LoRa connection active
      } com; 

  //  Timers and related counters
      struct {
        int           action = 0;                                               // tmr.action - 0b0000000000000000 (so 16 flags). Base (position 0) is not used. Good tutorial on using bits: https://playground.arduino.cc/Code/BitMath#bit_pack
        int           countMax[sensLed + 1];                                    //  ` .countMax[] - User defined: 0: sensor not used, value: number of counts to take action.
        int           counts[sensLed + 1] = {};                                 //    .count[] - count[0] -> base counter, others multiples of base counter. Range base counter: 1 s to ~18 days. {} initiates all values to 0, see: https://stackoverflow.com/questions/201101/how-to-initialize-all-members-of-an-array-to-the-same-value.
        const int     sleep_ms = 1000;                                          //    .sleep_ms - Equal to the sleep duration (1 s or 1000 ms for most clocks)
        unsigned long timer0_ms;                                                //    .timer0_ms - timer starting point (in ms)
//        long          timerBaseMax_ms;                                          //    .timerBaseMax_ms - timer limit (in ms) for base counters (only base needs a timer, others can use counters)
      } tmr;

  //  Identification and information
      struct {
        const String  tgbWhoAmI = "NiphDomo.000.000.T_RH_P._.";                 // Type.Version.Serial.SensorInternal.SensorsExternal    // Consider using PROGMEM: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
        String        tgbStartTGB = "dd-mmm-yyyy hh:mm UCT";                    // Dummy: ask the clock
        String        tgbLocation = "";                                         // Where is the Niph located (needs to be command controlled, e.g. when replacing one Niph with another)
      } inf;

  //  Operational settings
      struct {
        byte blinkLeds;                                                         // Turn leds on or off
        bool debug = false;
      } set; 
  
  //  Generic variables                                                         // TGB-wide reusable parameters
      struct {
        boolean go = false;                                                     // Do or Don't parameter (see e.g. command switch)
      } tgb;

//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void setup() {
  //  Initialise
  //. Hardware
      pinMode(pin.led00, OUTPUT);                                               // Pins are input by default
  //. Communication
      Serial.begin(9600);                                                       // 9600 is default communication speed for most Arduinos
  //  Input
  //. Reading variables
      inpRead();                                                                // DUMMY: these variables will be provided externally, or have been stored in case of reboot
  //. Input dependent parameters
//      tmr.timerBaseMax_ms = tmr.countMax[sensBase] * tmr.sleep_ms;              // Take action every x milliseconds (base counter time step)
  //. Set Action to true
      for (int s = sensLed; s > sensBase;  s--) {                               // Flagging all sensors for action before entering loop
        tmr.action |= (tmr.countMax[s] > 0) << s;                               // Explanation, see: https://github.com/KrisP-GSB/Troglobyte/wiki/Initiate-sensor-actions
      }
  //  Last things to do
  //. Confirm proper initialisation      
      BlinkInitiateSuccess();                                                   // Three distincitve blinks to mark start (other native, always shorter blinks will have occured before)
      tmr.timer0_ms = millis();                                                 // Reset the timer
}

//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void loop() { 
  //  Receiving commands  
//if (set.debug) {Serial.println (tmr.action, BIN);}                          // Debug and code testing (results in Serial monitor)
      com.USB = comUSBconnected(com.USB);                                       // Works as far as tested (i.e. it always detects the USB serial connection)
      com.WAN = comWANconnected();                                              // DUMMY (always false)
      if (com.USB || com.WAN) {
        switch(comGet()) {                                                      // Reacting to commands. Note that even cmdGet is an int, and so is a character between single quotes ('')! (Only double quotes indicate a char/string.)
          tgb.go = true;                                                        // Did the command result in a delay? True for most commands
          case 0: tgb.go = false; break;                                        // Most common 'action': Nohting received, no delay 
          case '?': cmdImHere(); break;                                                              
          case 'R': cmdRun(); break;                                            // Open command prompt to receive commands (pauzes all activities)
          case 'P': cmdPauze(); break;                                          // Suspend all actions untill P is pressed again
          case 'S': // cmdStopMeasuring(); break;                               // Be careful with this, needs certainty to be turned on again
          case 'T': // LiveMeasureT(); break; 
          case 'M': // LiveMeasureAll(); break; 
          case '>': // cmdPlay(); break;                                        // Dump all data to serial
          default: Serial.println("Unknown command"); break;                    // No command or command not recognised 
        }
        if (tgb.go) {tmrCheckTime(); tgb.go = false;}                            // Correct timer (only necessary when there were delays, command actions). Also reset the generic variable to default.
      }

  //  Executing measurements
      if (tmrAction(sens01_T)) {msrT();}
      if (tmrAction(sens02_RH)) {msrRH();}
      if (tmrAction(sens03_P)) {msrP();}
      //...                                                                     // Room for other sensors (up to sens14_X)
      if (tmrAction(sensLed)) {msrBlink();}                                     // Place last: a blink not followed by a pauze

  //  Sleep or delay                                                            // Depending on whether connected
  if  (com.USB || com.WAN) {
    delay(100);                                                                 // Stay responsive. Delay of 100 ms is acceptable for most input.
    tmrCheckTime();
  } else {
    tmpSleep();                                                                 // Sleep until next second has passed, and increase counters.
  }
}
