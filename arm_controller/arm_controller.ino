#include <Servo.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include "arm.h"

SoftwareSerial BTSerial(10, 11); // RX | TX

const int jointsCount = 5;
const Joint joints[] = {
        Joint(4, 0, 0),
        Joint(5, 0, 0),
        Joint(6, 0, 0),
        Joint(7, 0, 0),
        Joint(8, 0, 0)
};

Arm* arm;

String buffer = "";

int i = 0;
void parseBuffer() {
  int index;
  float angle;

  angle = atof(buffer.c_str() + 2);
  sscanf(buffer.c_str(), "%2d", &index); 
   
  if ( index >= jointsCount ) {
    Serial.print("Index out of range! Index = ");
    Serial.print(index);
    Serial.print(", jointsCount = ");
    Serial.println(jointsCount);
  } else {
    Serial.print("Receiving joints[");
    Serial.print(index);
    Serial.print("] = ");
    Serial.println(angle);
    
    joints[index].setCurrentAngle( angle );
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Arm initializing");

  for ( int i = 0; i < jointsCount; ++ i ) {
    joints[i].init();
  }
  arm = new Arm(joints, jointsCount);

  BTSerial.begin(9600);
}

void loop() {
  // fetch the values and update joints[]
  if (BTSerial.available()) {
    char c = BTSerial.read();
    if ( c == '\n' ) {
      parseBuffer();

      buffer = "";
    } else {
      buffer += c;
    }
  }

  arm->update();
}
