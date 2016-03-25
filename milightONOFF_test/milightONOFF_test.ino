#include <SPI.h>
#include "nRF24L01.h"
#include <RF24.h>
#include "printf.h"

// SETTINGS
#define CE_PIN 9
#define CSN_PIN 10
#define BUTTON_ON 5
#define BUTTON_OFF 4

RF24 radio(CE_PIN, CSN_PIN);

void setup()
{
  //Start serial
  Serial.begin(115200);

  //Enable button
  pinMode(BUTTON_ON,INPUT);
  pinMode(BUTTON_OFF,INPUT);

  //Enable Radio
  radio.begin();

  //Enable Radio diagnostic
  printf_begin();
  Serial.println("Milight remote Test");
  Serial.println("Values shouldn't be all set to 0x00");
  Serial.println("-----------------------");
  radio.printDetails();
  Serial.println("------------------------");
  Serial.println("Press Button 1 or Button 2 to check them");
}

void loop()
{
  //Check if buttons are pressed
  if(digitalRead(BUTTON_ON)){
    Serial.println("Button ON Pressed");
  }

  if(digitalRead(BUTTON_OFF)){
    Serial.println("Button OFF Pressed");
  }
}
