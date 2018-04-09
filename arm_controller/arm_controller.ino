#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "arm.h"

const int jointsCount = 1;
const Joint joints[] = {
        Joint(9, 0, 0)
};

Arm* arm;

RF24 radio(A2, A0); // CE, CSN
const byte address[6] = "00001"; // mora biti ista na glove_controller

void setup() {
  arm = new Arm(joints, jointsCount);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // fetch the values and update joints[]
  if (radio.available()) {
    char buffer[16] = "";
    radio.read(&buffer, sizeof(buffer));

    int index;
    float angle;

    sscanf(buffer, "%2d %12f", &index, &angle);

    if ( index >= jointsCount ) {
      Serial.print("Index out of range! Index = ");
      Serial.print(index);
      Serial.print(", jointsCount = ");
      Serial.println(jointsCount);
    } else {
      joints[index].setCurrentAngle( angle );
    }
  }

  /*
  // stub
  for ( int i = 0; i < jointsCount; ++ i ) {
    joints[i].setCurrentAngle( static_cast<int>(joints[i].getCurrentAngle() + 1) % 360 );
  }
  */

  arm->update();
}
