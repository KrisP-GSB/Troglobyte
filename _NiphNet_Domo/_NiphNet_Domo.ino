//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Initialise
  //  Pin assignments
      const int ledPin00 = LED_BUILTIN;                         // LED_BUILTIN points to the internal led, D13 on the Nano (see https://www.arduino.cc/en/Tutorial/Blink)
  //  Variables
  //. Identification and information
  //. Setting up timer
  //. Connection
      boolean tgbUSB = false;
      boolean tgbWAN = false;
  //. Counter
      long tmrBaseIntMS;

      // Good tutorial on using bits: https://playground.arduino.cc/Code/BitMath#bit_pack

      struct {
        int action = 0;                                                         // 0b0000000000000000 (so 16 flags).
        int actionOnCount[15];                                                  // User defined: 0: sensor not used, value: number of counts.
        int count[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};                      // count[0] -> base counter, others multiples of base counter. Range base counter: 1 s to ~18 days.
        const int Sleep_ms = 1000;                                              // Equal to the sleep duration (1s or 1000ms for most clocks)
        unsigned int timer = 0;          
        unsigned long timer0;
      } tmr;

      enum typSensor{ tgb00_Base,tgb01_Led, tgb02_T,  tgb03_RH, 
                      tgb04_P,   tgb05_X,   tgb06_X,  tgb07_X, 
                      tgb08_X,   tgb09_X,   tgb10_X,  tgb11_X, 
                      tgb12_X,   tgb13_X,   tgb14_X,  tgb15_X   };               // C++ command, for explicitly naming the sensors
      struct {
        typSensor sensor;      
        const String tgbWhoAmI = "NiphDomo.000.000.T_RH_P._.";    // Type.Version.Serial.SensorInternal.SensorsExternal    // Consider using PROGMEM: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
        String tgbStartTGB = "dd-mmm-yyyy hh:mm UCT";       //Dummy: ask the clock
      } tgb;
      
  //. Input
  //..Initialising parameters
    // I think the below should become a class (is being reused)
      byte setBlink   ;     // Blink the leds or not

//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void setup() {
  //  Initialise
  //. Hardware
      pinMode(ledPin00, OUTPUT);        
  //. Communication
      Serial.begin(9600);                                                       // Default for most Arduinos
  //  Input
  //. Reading variables
      inpRead();
  //. Input dependent parameters
      tmrBaseIntMS = tmrBaseInt * tmrSleepInterval; // Take action every x milliseconds
  //  Last things to do
  //. Confirm proper initialisation      
      BlinkInitiateSuccess();           // Pauze, three blinks, and a pauze to put Christian at ease (bootloader or arduino will have blinked before this)
  //. Reset parameters to start cycle with measurement
      if (tmrBlinkInt > 0)  {tmrBlinkAction = 1;}     // First action: measure everything 
      if (tmrTInt     > 0)  {tmrTAction     = 1;}       
      if (tmrRHInt    > 0)  {tmrRHAction    = 1;}      
      if (tmrPInt     > 0)  {tmrPAction     = 1;}             
      if (tmrXInt     > 0)  {tmrXAction     = 1;}
      tmrMillis0 = millis();                          // Reset the time
}

//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void loop() { 
  //  Receiving commands  
      tgbUSB = comUSBconnected(tgbUSB); //......................................Works as far as tested (i.e. it always detects the USB serial connection)
      tgbWAN = comWANconnected(); //............................................Dummy (always false)
      if (tgbUSB || tgbWAN) {
        switch(cmdGet()) {                    // Reacting to commands
          case ' ': 
            break;                              // Nothing received, proceed
          case '?': 
            cmdImHere();
            break;                            // For reasons not clear not me, code will fail when this break is not in place. It is in any case more efficient to have it. 
          case 'R':                           // Open command prompt to receive commands (pauzes all activities)
            cmdRun();                         
            break; 
          case 'P':                           // Suspend all actions untill P is pressed again
            cmdPauze();
            break; 
          case 'S':
            // cmdStopMeasuring();            // Be careful with this, needs certainty to be turned on again
            break; 
          case 'T': 
            // LiveMeasureT()
            break; 
          case 'M': 
            // LiveMeasureAll()
            break; 
          case '>':                           // Dump all data to serial
            // cmdPlay();
            break; 
          default:
            Serial.println("Unknown command");  // No command or command not recognised 
            break;
        }
      } else {
        // IF !(tgbCmd = 0x00) THEN CheckDelayCmd() END IF
      }
      tmrCheckTime();

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
      if (tmrBlinkAction == 1) {              // Placze last: a blink not followed by a pauze
        msrBlink();
        tmrBlinkAction = 0;
      }

  //  Sleep or short delay (depending on whether connected)
  if  (tgbUSB == 1 || tgbWAN == 1) {
    tmpSleep();           // Sleep until next second has passed, and increase counters.
  } else {
    delay(100);           // Delay of 100 ms is acceptable for most input.
  }
}
