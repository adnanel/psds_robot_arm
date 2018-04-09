#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "flex.h"

RF24 radio(A1, A0); // CE, CSN

const byte address[6] = "00001"; // mora biti ista na arm_controller

const int flexCount = 1;
const Flex flexes[]= {
        Flex(A2),
        Flex(A3),
        Flex(A4),
        Flex(A5)
        //Flex(A6)
};

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  char buffer[16];
  
  for ( int i = 0; i < flexCount; ++ i ) {
    Serial.print("Transmitting joints[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(flexes[i].getAngle());
    
    sprintf(buffer, "%2d %12f", i, flexes[i].getAngle());
    
    radio.write(&buffer, sizeof(buffer));
  }
}
