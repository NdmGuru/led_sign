/*
  LedSign library: Runs the "Computronics" LED Signs.
  The arduino is only spitting out TTL commands.
  Hardware is an arduino, and MAX485CPE to connect to the sign.
  
  The signs are either r/g/y or red and are 12 or 15 "Pixels" wide.
  
  We use a LCD Panel to display some data, and 4 input buttons for input.

  Written: Nathan Metcalf 09/09/13
 */
 
// Add some funky librarys.
// PHI_prompt is what we want for the menu's.

#include "Common.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TimedAction.h>

// Init the librarys
SoftwareSerial ledSign =  SoftwareSerial(rxPin, txPin);
LiquidCrystal lcd(lcd_rs, lcd_en, lcd_d1, lcd_d2, lcd_d3, lcd_d4);

void setup() 
{ 
  // Setup the TX/RX Pins
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(ctsPin, OUTPUT);
  // Hold them low for now (Disabled)
  digitalWrite(ctsPin, LOW);
  digitalWrite(txPin, LOW);
  
  //Setup Buttons
  pinMode(btn_1, INPUT);
  pinMode(btn_2, INPUT);
  pinMode(btn_3, INPUT);
  pinMode(btn_4, INPUT);
  // Use internal Pullups.
  digitalWrite(btn_1, HIGH);
  digitalWrite(btn_2, HIGH);
  digitalWrite(btn_3, HIGH);
  digitalWrite(btn_4, HIGH);
  
  // Setup the debug led, and turn it off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Setup the serial ports
  ledSign.begin(9600);
  // Setup LCD
  lcd.begin(16,2);
    
  if(debug){
    Serial.begin(115200);
    Serial.println("Debug enabled");
    for(int j = 0; j > 3; j++){
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
    }
    lcd.print("Setup...");
    Serial.println("Startup complete...");
  }

  
} 

void loop() 
{    
    // Red   = {
    // Green = |
    // Yellow= }
    String Message = "Startup Message";
    
    while(1){
      if(digitalRead(btn_1) == LOW){
        String Message = "{ONE ONE ONE";      
        sendMsg(Message, Message.length(), cmdJump);
        lcd.setCursor(0,0);
        lcd.print(Message);
      }else if(digitalRead(btn_2) == LOW){
        String Message = "}TWO TWO TWO";
        sendMsg(Message, Message.length(), cmdJump);    
        lcd.setCursor(0,0);
        lcd.print(Message);
      }else if(digitalRead(btn_3) == LOW){
        String Message = "|THREE THREE THREE";
        sendMsg(Message, Message.length(), cmdJump);
        lcd.setCursor(0,0);
        lcd.print(Message);  
      }else if(digitalRead(btn_4) == LOW){
        String Message = "[FOUR FOUR FOUR";
        sendMsg(Message, Message.length(), cmdJump);
        lcd.setCursor(0,0);
        lcd.print(Message);
      }  
      delay(10);
          
    }
}
