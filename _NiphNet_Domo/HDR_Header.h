//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
#ifndef _HEADERFILE_H                                                           // Put these two lines at the top of your file. Do no use this name for other purposes.
#define _HEADERFILE_H                                                           // These opening and ending lines avoid that the header file would accidentally be loaded twice.

//  Code-wide initialisation
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
      } tmr;

  //  Identification and information
      struct {
        const String  tgbWhoAmI = "NiphTea.000.000.T_RH_P._.";                 // Type.Version.Serial.SensorInternal.SensorsExternal    // Consider using PROGMEM: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
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

#endif // _HEADERFILE_H                                                         // This line ends the file.
