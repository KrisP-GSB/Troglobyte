//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|
//  LED communication
//. Connections
//..Connection established
  void BlinkConnected() {
    BlinkFadeIn();
    delay(500);
  }
//..Connection lost
  void BlinkDisconnected() {
    BlinkFadeOut();
  }
  
//. Initialisation
    void BlinkInitiateSuccess(){
      digitalWrite(pin.led00, LOW);
      delay(1000);
      for (int i=0; i<=5; i++){
        digitalWrite(pin.led00, !digitalRead(pin.led00));                       // Most efficient code, avoiding a boolean
        delay(500);   
      }
      delay(1500);                                                              // Adding 1.5 s to have 2 s pauze before starting real code
    }
//. Fade out and in (the 'I'm present and alive' blink)
  void BlinkImHere(){
    BlinkFadeIn();
    BlinkFadeOut();
    delay(100);
    BlinkFadeIn();
    BlinkFadeOut();
  }
//. Short blink
  void BlinkShort(){
      digitalWrite(pin.led00, LOW);
      digitalWrite(pin.led00, HIGH);
      delay(10);
      digitalWrite(pin.led00, LOW);
  }
//. Morse confirmations                                                         // See: https://en.wikipedia.org/wiki/Morse_code
//..BlinkT      -
  void BlinkT() {
    BlinkDash();  // T
    EndWord();
  }
//..BlinkRH()   .-. ....
  void BlinkRH() {
    BlinkDot(); BlinkDash(); BlinkDot(); EndLetter();                           // R
    BlinkDot(); BlinkDot(); BlinkDot(); BlinkDot(); EndWord();                  // H
  }
//..BlinkP()    .--.
  void BlinkP() {
    BlinkDot(); BlinkDash(); BlinkDash(); BlinkDot(); EndWord();                // P
  }
//..BlinkX()    -..-
  void BlinkX() {
    BlinkDash(); BlinkDot(); BlinkDot(); BlinkDash(); EndWord();                // X
  }

//. Pauze indicater
//..Start of pauze
    void BlinkPauzeStart(){
      digitalWrite(pin.led00, HIGH);
    }
//..End of pauze
    void BlinkPauzeEnd(){
      digitalWrite(pin.led00, LOW);
    }

//. Generic code
  void BlinkFadeOut(){
    for (int i=0; i<=10000; i=i+100){                                           // LED fading out during ~1s (in 11 steps)
      digitalWrite(pin.led00, LOW);
      delayMicroseconds(i);
      digitalWrite(pin.led00, HIGH);
      delayMicroseconds(10000-i);        
    }      
    digitalWrite(pin.led00, LOW);
  }
  void BlinkFadeIn(){
    for (int i=0; i<=10000; i=i+100){                                           // LED fading out during ~1s (in 11 steps)
      digitalWrite(pin.led00, HIGH);
      delayMicroseconds(i);
      digitalWrite(pin.led00, LOW);
      delayMicroseconds(10000-i);        
    }      
  }

//. Morse code
  void BlinkDot(){
    digitalWrite(pin.led00, HIGH);
    delay(200);                                                                 // One unit
    digitalWrite(pin.led00, LOW);
    delay(200);                                                                 // One unit
  }
  void BlinkDash(){
    digitalWrite(pin.led00, HIGH);
    delay(600);                                                                 // Three unit
    digitalWrite(pin.led00, LOW);
    delay(200);                                                                 // One unit
  }
  void EndLetter() {
  delay(400);                                                                   // Plus two units
  }
  void EndWord() {
    delay(1200);                                                                // Plus six units
  }
