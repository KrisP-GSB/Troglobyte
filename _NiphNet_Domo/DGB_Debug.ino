//..|....|....|....|....|....|....|....|....|....|....|....|....|....|....|....|

void dbgSerialPrint(char s[]) {                                                 // Debug and code testing (results in Serial monitor)
  Serial.print(millis()/1000.0);
  Serial.print(s);
}

void dbgSerialPrintLn(char s[]) {                                                 // Debug and code testing (results in Serial monitor)
  Serial.print(millis()/1000.0);
  Serial.println(s);
}
