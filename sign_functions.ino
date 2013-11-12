/*
  Variables used throughout the program
  Any configuration should be done here.
  
  Written 09/09/2013 - Nathan Metcalf
 */
 
/*
 * Send a single cmd to the LED sign.
 * Should be quicker, and we can do some logic in here
 */

void sendCmd(byte Cmd){
  // Debugging
  if(debug){
    digitalWrite(ledPin, HIGH);
    Serial.println("CMD Sent.");
  }
  
  digitalWrite(ctsPin, HIGH);
  ledSign.write(startBit);
  ledSign.write(password);  
  ledSign.write(Cmd);  
  digitalWrite(ctsPin, LOW);
  
  // Turn off the LED.
  if(debug){digitalWrite(ledPin, LOW);}
}


// Send a Msg to the sign.
// use { } | for colors -- Listed in loop()
void sendMsg(String msg, int msgLen, byte action){
  
  //Setup a buffer (extra for stop bit)
  char charBuf[(msgLen + 1)];
  //Fill charBuf with the HEX of the String (Extra for stop bit)
  msg.toCharArray(charBuf, (msgLen + 1));
  
  if(debug){
    Serial.print("Message length: ");
    Serial.println(msgLen);
    digitalWrite(ledPin, HIGH);
  }
  
  // Reset just for good measure
  sendCmd(cmdReset);

  digitalWrite(ctsPin, HIGH);
  
  // Send the starting byte's (start bit/password)
  ledSign.write(startBit);
  ledSign.write(password);
  
  // Send the movement action.
  ledSign.write(action);
    
  for (int i = 0; i <= msgLen ; i++)  {            
    // Pick out the color identifiers, really bad way of doing it though
    switch(charBuf[i]){
      case 0x7B:
        ledSign.write(Red);
        break;
      case 0x7C:
        ledSign.write(Green);
        break;
      case 0x7D:
        ledSign.write(Yellow);
        break ;
      case 0x5B:
        ledSign.write(Rainbow);
        if(debug){Serial.println("Rainbow enabled");}
        break;
      default:
        // Its a normal characture, send it
        ledSign.write(charBuf[i]);
        break;
     }
    
    // debugging
    if(debug){
      Serial.print(charBuf[i], HEX);
      Serial.print(" ");
    }
  }
  ledSign.write(stopBit);
  digitalWrite(ctsPin, HIGH);
  
  if(debug){
    Serial.println();
    Serial.print("Message: '");
    Serial.print(msg);
    Serial.println("' Sent");
    digitalWrite(ledPin, LOW);
  }
}

