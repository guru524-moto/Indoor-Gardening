#define RELAY_PIN   5
#define SOL_PIN   8

#include <LCD_I2C.h>
#include "Arduino.h"
#include "PCF8574.h"
#include "dht.h"
#include "includes.h"
#define dht_apin A1 // Analog Pin sensor is connected to
 bool tempF= 0;
 bool motorON = 0;
LCD_I2C lcd(0x20, 16, 2);
PCF8574 pcf8574(0x21);
dht DHT;

int time_rh=0;
  float dht_F;
  
void setup() {
  
  lcd.begin();
  Serial.begin(9600);
  lcd.print("     Sera       ");
  lcd.setCursor(0, 1);
  lcd.print("    smart v1    ");
    analogReference(INTERNAL);
  pcf8574.pinMode(P0, OUTPUT);
  pcf8574.pinMode(P1, OUTPUT);
  pcf8574.pinMode(P2, OUTPUT);
  pcf8574.pinMode(P3, OUTPUT);
  pcf8574.pinMode(P4, OUTPUT);
  pcf8574.pinMode(P5, OUTPUT);
//set timer0 interrupt at 2kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2 = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR2A = 249;// = (16*10^6) / (1000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 and CS20 bits for 64 prescaler
  TCCR2B |= (1 << CS21) | (1 << CS20);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  sei();//allow interrupts8888
  pcf8574.digitalWrite(P0, LOW);
  pcf8574.digitalWrite(P1, HIGH);
  pcf8574.digitalWrite(P2, HIGH);
  pcf8574.digitalWrite(P3, HIGH);
  pcf8574.digitalWrite(P4, HIGH);
  pcf8574.digitalWrite(P5, HIGH);
  pinMode(SOL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  delay(1000);
}

void loop() {
    

  // put your main code here, to run repeatedly:
  if((digitalRead(SOL_PIN))||(motorON))
  {
    digitalWrite(RELAY_PIN, LOW);
    pcf8574.digitalWrite(P1, LOW);
    lcd.setCursor(0, 1);
    lcd.print("   Sol uscat!   ");
  }
  else
  {
    digitalWrite(RELAY_PIN, HIGH);
    pcf8574.digitalWrite(P1, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("*** Sol umed ***");
  }
  delay(100);
  time_rh++;
  key_read();
  if(time_rh>40) //TODO CREATE FUNCTION FOR CHANGING TEMP IN C TO F
  {
    time_rh=0;
    DHT.read11(dht_apin);
    dht_F=(DHT.temperature*9/5)+32;
    lcd.setCursor(0,0);
    lcd.print("Rh= ");
    lcd.print(DHT.humidity);
    lcd.setCursor(6,0);
    lcd.print("% ");
    lcd.setCursor(8,0);
    lcd.print("Ta= ");
    if(tempF){
          lcd.print(dht_F);
    lcd.setCursor(14,0);
    lcd.print("F ");
    }else{
    lcd.print(DHT.temperature);
    lcd.setCursor(14,0);
    lcd.print("C ");
    }
  }
}
