//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Initialise
  //  Pin assignments
      struct {
        const int led00 = LED_BUILTIN;                                          // pin.led00 - LED_BUILTIN points to the internal led, D13 on the Nano (see https://www.arduino.cc/en/Tutorial/Blink)
        const int led01 = 0;                                                    //    .led01 - Open slots for three external leds
        const int led02 = 0;                                                    //    .led02
        const int led03 = 0;                                                    //    .led03
      } pin;
      
  //  Communication
      struct {
        boolean USB = false;                                                    // com.USB - USB serial connection detected
        boolean WAN = false;                                                    //    .WAN - LoRa connection active
      } com; 

  //  Timers and related counters
      struct {
        int           action = 0;                                               // tmr.action - 0b0000000000000000 (so 16 flags).
        int           countMax[16];                                             //  ` .countMax[] - User defined: 0: sensor not used, value: number of counts to take action.
        int           counts[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};           //    .count[] - count[0] -> base counter, others multiples of base counter. Range base counter: 1 s to ~18 days.
        const int     sleep_ms = 1000;                                          //    .sleep_ms - Equal to the sleep duration (1 s or 1000 ms for most clocks)
        unsigned int  timer_ms = 0;                                             //    .timer_ms - 
        unsigned long timer0_ms;                                                //    .timer0_ms - timer starting point (in ms)
        long          timerBaseMax_ms;                                          //    .timerBaseMax_ms - timer limit (in ms) for base counters (only base needs a timer, others can use counters)
      } tmr;


      // Good tutorial on using bits: https://playground.arduino.cc/Code/BitMath#bit_pack


      enum typSensor                                                            // Explicitly naming the sensors
        { sensBase,   sensLed,    sens01_T,  sens02_RH, 
          sens03_P,   sens04_X,   sens05_X,  sens06_X, 
          sens07_X,   sens08_X,   sens09_X,  sens10_X, 
          sens11_X,   sens12_X,   sens13_X,  sens14_X   
        };                                                          

  //. Identification and information
      struct {
        typSensor sensor;      
        const String tgbWhoAmI = "NiphDomo.000.000.T_RH_P._.";    // Type.Version.Serial.SensorInternal.SensorsExternal    // Consider using PROGMEM: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
        String tgbStartTGB = "dd-mmm-yyyy hh:mm UCT";       // Dummy: ask the clock
        String tgbLocation = ""; // Where is the Niph located (needs to be command controlled, e.g. when replacing one Niph with another)
      } tgb;
      
  //. Input
  //..Initialising parameters
  //. TGB-wide reusable parameters
      boolean tgbDo  = false;                                                   // Do or Don't parameter (see e.g. command switch)
  //. Input
  //..Initialising parameters
      byte setBlink   ;                                                         // Turn leds on or off

//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void setup() {
  //  Initialise
  //. Hardware
      pinMode(pin.led00, OUTPUT);                                                // Pins are input buy default
  //. Communication
      Serial.begin(9600);                                                       // Default for most Arduinos
  //  Input
  //. Reading variables
      inpRead();                                                                // DUMMY: these variables will be provided externally, or have been stored in case of reboot
  //. Input dependent parameters
      tmr.timerBaseMax_ms = tmrBaseInt * tmrSleepInterval;                             // Take action every x milliseconds (base counter time step)
  //  Last things to do
  //. Confirm proper initialisation      
      BlinkInitiateSuccess();                                                   // Three distincitve blinks to mark start (other native, always shorter blinks will have occured before)
  //. Reset parameters to start cycle with measurement
      if (tmrBlinkInt > 0)  {tmrBlinkAction = 1;}                               // First action: measure everything 
      if (tmrTInt     > 0)  {tmrTAction     = 1;}                               // Therefore all ...Actions to 1
      if (tmrRHInt    > 0)  {tmrRHAction    = 1;}      
      if (tmrPInt     > 0)  {tmrPAction     = 1;}             
      if (tmrXInt     > 0)  {tmrXAction     = 1;}
      tmrMillis0 = millis();                                                    // Reset the timer
}

//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void loop() { 
  //  Receiving commands  
      com.USB = comUSBconnected(com.USB);                                         // Works as far as tested (i.e. it always detects the USB serial connection)
      com.WAN = comWANconnected();                                               // DUMMY (always false)
      if (com.USB || com.WAN) {
        switch(comGet()) {                                                      // Reacting to commands. Note that even cmdGet is an int, and so is a character between single quotes ('')! (Only double quotes indicate a char/string.)
          tgbDo = true;                                                         // Did the command result in a delay? True for most commands
          case 0: 
            tgbDo = false;                                                      // No delay (maybe the only exception, but it happens a lot)
            break;                                                              // Nothing received, proceed
          case '?': 
            cmdImHere();
            break;                                                              
          case 'R':                                                             // Open command prompt to receive commands (pauzes all activities)
            cmdRun();                         
            break; 
          case 'P':                                                             // Suspend all actions untill P is pressed again
            cmdPauze();
            break; 
          case 'S':
            // cmdStopMeasuring();                                              // Be careful with this, needs certainty to be turned on again
            break; 
          case 'T': 
            // LiveMeasureT()
            break; 
          case 'M': 
            // LiveMeasureAll()
            break; 
          case '>':                                                             // Dump all data to serial
            // cmdPlay();
            break; 
          default:
            Serial.println("Unknown command");                                  // No command or command not recognised 
            break;
        }
        if (tgbDo) {
          tmrCheckTime();                                                       // Correct timer (only necessary when there were delays, command actions).
        }
      }

  //  Executing measurements
      if (tmrTAction == 1) {
        msrT(); 
        tmrTAction = 0;
      }
      if (tmrRHAction == 1) {
        msrRH();
        tmrRHAction = 0;
      }
      if (tmrPAction == 1) {
        msrP();
        tmrPAction = 0;
      }
      if (tmrXAction == 1) {
        msrX();
        tmrXAction = 0;
      }
      if (tmrBlinkAction == 1) {              // Place last: a blink not followed by a pauze
        msrBlink();
        tmrBlinkAction = 0;
      }

  //  Sleep or short delay (depending on whether connected)
  if  (com.USB || com.WAN) {
    tmpSleep();           // Sleep until next second has passed, and increase counters.
  } else {
    delay(100);           // Delay of 100 ms is acceptable for most input.
  }
}
