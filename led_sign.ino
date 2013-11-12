#include <SoftwareSerial.h>

// Pin definitions
#define rtsPin  2
#define ctsPin  3
#define dtrPin  4
#define rxPin   10
#define txPin   11
#define ledPin  13

// 
#define startBit      0x02
#define stopBit       0x03
#define password      0x80

// System cmds
#define cmdEnable     0xBB
#define cmdDisable    0xBC
#define cmdReset      0xBA
#define cmdPause      0x91

// Movement cmd's (NB: Rainbow cannot be used with all)
#define cmdHalt       0x8E
#define cmdJump       0x8F
#define cmdRolltop    0x93
#define cmdScrollltr  0x94
#define cmdRollbtm    0x95

// Color commands
#define Red      0xC0
#define Green    0xC1
#define Yellow   0xC2
#define Rainbow  0xC7 // Cycles through some funky patterns

#define debug   true
#define repeatInt 6000 // Sleep timer used to not repeat too fast for the sign (Usually when sending one message, with no pause)

// Serial for sign
SoftwareSerial ledSign =  SoftwareSerial(rxPin, txPin);

void setup() 
{ 
  // Setup the TX/RX Ping
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(ctsPin, OUTPUT);
  
  // Hold them low for now (Disabled)
  digitalWrite(ctsPin, LOW);
  digitalWrite(txPin, LOW);
  
  // Setup the debug led, and turn it off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Setup the serial ports
  ledSign.begin(9600);
    
  if(debug){
    Serial.begin(115200);
    Serial.println("Debug enabled");
    for(int j = 0; j > 3; j++){
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
    }
    Serial.println("Startup complete...");
  }
  
} 

// Send a single cmd to the LED sign.
// Should be quicker, and we can do some logic in here
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


void loop() 
{    
    // Red   = {
    // Green = |
    // Yellow= }

    String Message1 = "[** ARDUINO **";
    sendMsg(Message1, Message1.length(), cmdJump);
    delay(5000);
    
    String Message = "|-= {Nothing }Importent |Just {Testing }Scrolling }/  |Colors } =-";
    sendMsg(Message, Message.length(), cmdScrollltr);
    delay(14000);
}
