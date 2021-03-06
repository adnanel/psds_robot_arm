#include <Servo.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "flex.h"

SoftwareSerial BTSerial(10, 11); // RX | TX

const int flexCount = 5;
const Flex flexes[]= {
        Flex(A2),
        Flex(A3),
        Flex(A4),
        Flex(A5),
        Flex(A6)
};

void setup() {
  Serial.begin(9600);
  Serial.println("Glove initializing");

  
  BTSerial.begin(9600);


  // Load calibration
  char magic;
  EEPROM.get(0, magic);
  if ( magic == 101 ) {
    int addr = 1;
    for (int i = 0; i < flexCount; ++i) {
      float vcc;
      float rDiv;
      float straightResistance;
      float BendResistance;

      EEPROM.get(addr, vcc);
      EEPROM.get(addr + sizeof(float) * 1, rDiv);
      EEPROM.get(addr + sizeof(float) * 2, straightResistance);
      EEPROM.get(addr + sizeof(float) * 3, BendResistance);

      flexes[i].calibrate({
                                  vcc,
                                  rDiv,
                                  straightResistance,
                                  BendResistance
                          });

      addr += sizeof(float) * 4;
    }
  }
}

void loop() {
  char buffer[20];
  
  for ( int i = 0; i < flexCount; ++ i ) {
    char temp[12];
    
    Serial.print("Transmitting joints[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(flexes[i].getAngle());

    BTSerial.print(i);
    BTSerial.print(' ');
    BTSerial.println(flexes[i].getAngle());
  }

  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }

  if ( Serial.available() ) {

  }
}


