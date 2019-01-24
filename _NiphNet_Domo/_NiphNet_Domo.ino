//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Initialise
  //  Pin assignments
      const int ledPin00 = LED_BUILTIN;                         // LED_BUILTIN points to the internal led, D13 on the Nano (see https://www.arduino.cc/en/Tutorial/Blink)
  //  Variables
  //. Identification and information
      const String tgbWhoAmI = "NiphDomo.000.000.T_RH_P._.";    // Type.Version.Serial.SensorInternal.SensorsExternal    // Consider using PROGMEM: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
      const String tgbStartTGB = "dd-mmm-yyyy hh:mm UCT";       //Dummy: ask the clock
  //. Setting up timer
      const int tmrSleepInterval = 1000;   // Equal to the sleep duration (1s or 1000ms for most clocks)
      unsigned int tgbTmr = 0;          
      unsigned long tmrMillis0;
  //. Connection
      boolean tgbUSB = false;
      boolean tgbWAN = false;
  //. Counter
      long tmrBaseIntMS;

      // Good tutorial on using bits: https://playground.arduino.cc/Code/BitMath#bit_pack
      // 8, including the led (blink). Also including the base counter to save memory? --> better to move to int (16 bits)? --> warning, on some arduinos an int is 32 bits!
      byte tmrAction = 0; // B0000000 * 256 + B00000000; probably you can write 0b0000000000000000, but I'm not sure      // 16 slots to indicate no action (0) or action (1). To be tested: can bitSet() and bit() reach all 16? Note that this settin is explicit (a 0 would do). 
      int tmrCount[7];          // Array of 8 
      int tmrInterval[7];       // Array of 8
      enum tgbSensor{tgbLed, tgbT01, tgbRH01, tgbP01, tgbX04, tgbX05, tgbX06, tgbX07, tgbX08, tgbX09, tgbX10, tgbX11, tgbX12, tgbX13, tgbX14, tgbX15};               // C++ command, for explicitly naming the sensors
      
      
      byte tmrBaseCnt     = 0;  // Base counter in seconds 
      byte tmrBlinkCnt    = 0;  // Counter in times base counts 
      byte tmrBlinkAction = 0;  // Flag indicating to take action
      byte tmrTCnt        = 0;          
      byte tmrTAction     = 0;       
      byte tmrRHCnt       = 0;         
      byte tmrRHAction    = 0;      
      byte tmrPCnt        = 0;          
      byte tmrPAction     = 0;   
      byte tmrXCnt        = 0;
      byte tmrXAction     = 0;    
  //. Input
  //..Initialising parameters
    // I think the below should become a class (is being reused)
      int tmrBaseInt  ;    // Take action every y counts
      int tmrBlinkInt ;    // Take action every z base counts (i.e. multiples of base counts), 
      int tmrTInt     ;    // use 0 to disable
      int tmrRHInt    ;    
      int tmrPInt     ;  
      int tmrXInt     ;
      byte setBlink   ;

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
