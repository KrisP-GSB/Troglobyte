//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  LED communication
//. Connections
//..Connection established
  void ledConnected() {
    ledFadeIn();
    delay(500);
  }
//..Connection lost
  void ledDisconnected() {
    ledFadeOut();
  }
  
//. Initialisation
    void ledInitialised(){
      digitalWrite(pin.led00, LOW);
      delay(1000);
      for (int i=0; i<=5; i++){
        digitalWrite(pin.led00, !digitalRead(pin.led00));                       // Most efficient code, avoiding a boolean
        delay(500);   
      }
      delay(1500);                                                              // Adding 1.5 s to have 2 s pauze before starting real code
    }
//. Fade out and in (the 'I'm present and alive' blink)
  void ledImHere(){
    ledFadeIn();
    ledFadeOut();
    delay(100);
    ledFadeIn();
    ledFadeOut();
  }
//. Short blink
  void ledShort(){
      digitalWrite(pin.led00, LOW);
      digitalWrite(pin.led00, HIGH);
      delay(10);
      digitalWrite(pin.led00, LOW);
  }
//. Morse confirmations                                                         // See: https://en.wikipedia.org/wiki/Morse_code
//..ledT      -
  void ledT() {
    ledDash();  // T
    ledEndWord();
  }
//..ledRH()   .-. ....
  void ledRH() {
    ledDot(); ledDash(); ledDot(); ledEndLetter();                                 // R
    ledDot(); ledDot(); ledDot(); ledDot(); ledEndWord();                          // H
  }
//..ledP()    .--.
  void ledP() {
    ledDot(); ledDash(); ledDash(); ledDot(); ledEndWord();                        // P
  }
//..ledX()    -..-
  void ledX() {
    ledDash(); ledDot(); ledDot(); ledDash(); ledEndWord();                        // X
  }

//. Pauze indicater
//..Start of pauze
    void ledPauzeStart(){
      digitalWrite(pin.led00, HIGH);
    }
//..End of pauze
    void ledPauzeEnd(){
      digitalWrite(pin.led00, LOW);
    }

//. Generic code
  void ledFadeOut(){
    for (int i=0; i<=10000; i=i+100){                                           // LED fading out during ~1s (in 11 steps)
      digitalWrite(pin.led00, LOW);
      delayMicroseconds(i);
      digitalWrite(pin.led00, HIGH);
      delayMicroseconds(10000-i);        
    }      
    digitalWrite(pin.led00, LOW);
  }
  void ledFadeIn(){
    for (int i=0; i<=10000; i=i+100){                                           // LED fading out during ~1s (in 11 steps)
      digitalWrite(pin.led00, HIGH);
      delayMicroseconds(i);
      digitalWrite(pin.led00, LOW);
      delayMicroseconds(10000-i);        
    }      
  }

//. Morse code
  void ledDot(){
    digitalWrite(pin.led00, HIGH);
    delay(200);                                                                 // One unit
    digitalWrite(pin.led00, LOW);
    delay(200);                                                                 // One unit
  }
  void ledDash(){
    digitalWrite(pin.led00, HIGH);
    delay(600);                                                                 // Three unit
    digitalWrite(pin.led00, LOW);
    delay(200);                                                                 // One unit
  }
  void ledEndLetter() {
  delay(400);                                                                   // Plus two units
  }
  void ledEndWord() {
    delay(1200);                                                                // Plus six units
  }
