/*
  LedSign library: Runs the "Computronics" LED Signs.
  The arduino is only spitting out TTL commands.
  Hardware is an arduino, and MAX485CPE to connect to the sign.
  
  The signs are either r/g/y or red and are 12 or 15 "Pixels" wide.
  
  We use a LCD Panel to display some data, and 4 input buttons for input.

  Written: Nathan Metcalf 09/09/13
 */
 
#include "Common.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TimedAction.h>

// Init the librarys
SoftwareSerial ledSign =  SoftwareSerial(rxPin, txPin);
LiquidCrystal lcd(lcd_rs, lcd_rw, lcd_d1, lcd_d2, lcd_d3, lcd_d4);

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
