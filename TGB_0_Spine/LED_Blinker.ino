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
      digitalWrite(ledPin00, LOW);
      digitalWrite(ledPin00, HIGH);
      delay(50);
      digitalWrite(ledPin00, LOW);
  }
//. Morse confirmations             // See: https://en.wikipedia.org/wiki/Morse_code
//..BlinkT      -
  void BlinkT() {
    BlinkDash();  // T
    EndWord();
  }
//..BlinkRH()   .-. ....
  void BlinkRH() {
    BlinkDot(); BlinkDash(); BlinkDot(); EndLetter();           // R
    BlinkDot(); BlinkDot(); BlinkDot(); BlinkDot(); EndWord();  // H
  }
//..BlinkP()    .--.
  void BlinkP() {
    BlinkDot(); BlinkDash(); BlinkDash(); BlinkDot(); EndWord();   // P
  }
//..BlinkX()    -..-
  void BlinkX() {
    BlinkDash(); BlinkDot(); BlinkDot(); BlinkDash(); EndWord();    // X
  }

//. Pauze indicater
//..Start of pauze
    void BlinkPauzeStart(){
      digitalWrite(ledPin00, HIGH);
    }
//..End of pauze
    void BlinkPauzeEnd(){
      digitalWrite(ledPin00, LOW);
    }

//. Generic code
  void BlinkFadeOut(){
    for (int i=0; i<=10000; i=i+100){                               // LED fading out during ~1s (in 11 steps)
      digitalWrite(ledPin00, LOW);
      delayMicroseconds(i);
      digitalWrite(ledPin00, HIGH);
      delayMicroseconds(10000-i);        
    }      
    digitalWrite(ledPin00, LOW);
  }
  void BlinkFadeIn(){
    for (int i=0; i<=10000; i=i+100){                               // LED fading out during ~1s (in 11 steps)
      digitalWrite(ledPin00, HIGH);
      delayMicroseconds(i);
      digitalWrite(ledPin00, LOW);
      delayMicroseconds(10000-i);        
    }      
  }

//. Morse code
  void BlinkDot(){
    digitalWrite(ledPin00, HIGH);
    delay(200);                             // One unit
    digitalWrite(ledPin00, LOW);
    delay(200);                             // One unit
  }
  void BlinkDash(){
    digitalWrite(ledPin00, HIGH);
    delay(600);                             // Three unit
    digitalWrite(ledPin00, LOW);
    delay(200);                             // One unit
  }
  void EndLetter() {
  delay(400);                               // Plus two units
  }
  void EndWord() {
    delay(1200);                             // Plus six units
  }
