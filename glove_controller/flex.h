#ifndef PSDS_FLEX_H
#define PSDS_FLEX_H

class Flex {
	int targetPin;

	static constexpr float VCC = 4.98;
	static constexpr float R_DIV = 47500.0;
	static constexpr float STRAIGHT_RESISTANCE = 37300.0;
	static constexpr float BEND_RESISTANCE = 90000.0;

public:
	inline Flex(int pin) {
		this->targetPin = pin;

		pinMode(pin, INPUT);
	}


	inline float getAngle() {
		int flexADC = analogRead(targetPin);
		float flexV = flexADC * VCC / 1023.0;
		float flexR = R_DIV * (VCC / flexV - 1.0);

		Serial.println(flexR);
		float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
						  0, 90.0);
		
		return angle;
	}
};


#endif //PSDS_FLEX_H


