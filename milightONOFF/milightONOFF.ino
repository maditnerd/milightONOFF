#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "PL1167_nRF24.h"
#include "MiLightRadio.h"

//Radio
#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
PL1167_nRF24 prf(radio);
MiLightRadio mlr(prf);
int sequence = 0x01;

//Buttons pinOut
const int OnPin = 5;
const int OffPin = 4;

// Put your own code here
// You don't need to put the last number as it will be increment each times you send a code 
int on [7] = { 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x01};
int off [7] = { 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x01};

void setup()
{
 pinMode(OnPin, INPUT);
 pinMode(OffPin, INPUT);
 mlr.begin();
}

void loop()
{
  //If ON button pressed send on
  if(digitalRead(OnPin)){
    radioSend(on);
  }

  //If OFF button pressed send off
  if(digitalRead(OffPin)){
    radioSend(off);
  }
}

void radioSend(int code [7] ){
  
  //Prepare message
  uint8_t outgoingPacket_tmp [7] ;
   for (int i = 0; i < 6;i++)
   {
    outgoingPacket_tmp[i] = (uint8_t)code[i];
   }

   outgoingPacket_tmp[6] = (uint8_t)sequence;

  //Send message
  mlr.write(outgoingPacket_tmp, sizeof(outgoingPacket_tmp));
  delay(1);
  mlr.resend();

  sequence++;
}
