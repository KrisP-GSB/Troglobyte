//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  Initialise
  //  Pin assignments
      const int ledPin00 = LED_BUILTIN;                                         // LED_BUILTIN points to the internal led, D13 on the Nano (see https://www.arduino.cc/en/Tutorial/Blink)
  //  Variables
  //. Identification and information
      const String tgbWhoAmI = "NiphDomo.000.000.T_RH_P._.";                    // Type.Version.Serial.SensorInternal.SensorsExternal    // Consider using EEPROM or PROGMEM: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
      const String tgbStartTGB = "dd-mmm-yyyy hh:mm UCT";                       // Dummy: ask the clock
  //. Setting up timer
      const int tmrSleepInterval = 1000;                                        // Equal to the sleep duration (1 s or 1000 ms for most clocks)
      unsigned long tmrMillis0;                                                 // Reference value for the timer (needs to be unsigned to work properly)
  //. Connection
      boolean tgbUSB = false;                                                   // USB serial connection detected
      boolean tgbWAN = false;                                                   // LoRa connection active
  //. Counter
      long tmrBaseIntMS;
      byte tmrBaseCnt     = 0;                                                  // Base counter in seconds 
      byte tmrBlinkCnt    = 0;                                                  // Counter in times base counts 
      byte tmrBlinkAction = 0;                                                  // Flag indicating to take action
      byte tmrTCnt        = 0;          
      byte tmrTAction     = 0;       
      byte tmrRHCnt       = 0;         
      byte tmrRHAction    = 0;      
      byte tmrPCnt        = 0;          
      byte tmrPAction     = 0;   
      byte tmrXCnt        = 0;
      byte tmrXAction     = 0;    
  //. TGB-wide reusable parameters
      boolean tgbDo  = false;                                                   // Do or Don't parameter (see e.g. command switch)
  //. Input
  //..Initialising parameters
      int tmrBaseInt  ;                                                         // Take action every y counts
      int tmrBlinkInt ;                                                         // Take action every z base counts (i.e. multiples of base counts), 
      int tmrTInt     ;                                                         // use 0 to disable
      int tmrRHInt    ;    
      int tmrPInt     ;  
      int tmrXInt     ;
      byte setBlink   ;                                                         // Turn leds on or off

//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
void setup() {
  //  Initialise
  //. Hardware
      pinMode(ledPin00, OUTPUT);                                                // Pins are input buy default
  //. Communication
      Serial.begin(9600);                                                       // Default for most Arduinos
  //  Input
  //. Reading variables
      inpRead();                                                                // DUMMY: these variables will be provided externally, or have been stored in case of reboot
  //. Input dependent parameters
      tmrBaseIntMS = tmrBaseInt * tmrSleepInterval;                             // Take action every x milliseconds (base counter time step)
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
      tgbUSB = comUSBconnected(tgbUSB);                                         // Works as far as tested (i.e. it always detects the USB serial connection)
      tgbWAN = comWANconnected();                                               // DUMMY (always false)
      if (tgbUSB || tgbWAN) {
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
  if  (tgbUSB == 1 || tgbWAN == 1) {
    tmpSleep();           // Sleep until next second has passed, and increase counters.
  } else {
    delay(100);           // Delay of 100 ms is acceptable for most input.
  }
}
