#ifndef PSDS_FLEX_H
#define PSDS_FLEX_H

class Flex {
public:
	struct CalibrationData {
		float vcc;
		float rDiv;
		float straightResistance;
		float BendResistance;
	};
private:
	int targetPin;

	static constexpr float DEFAULT_VCC = 4.98;
	static constexpr float DEFAULT_R_DIV = 47500.0;
	static constexpr float DEFAULT_STRAIGHT_RESISTANCE = 37300.0;
	static constexpr float DEFAULT_BEND_RESISTANCE = 90000.0;


	float vcc = 4.98;
	float rDiv = 47500.0;
	float straightResistance = 37300.0;
	float BendResistance = 90000.0;
public:
	inline Flex(int pin) {
		this->targetPin = pin;

		pinMode(pin, INPUT);
	}

	inline void calibrate(const CalibrationData& calibData) {
		this->vcc = calibData.vcc;
		this->rDiv = calibData.rDiv;
		this->straightResistance = calibData.straightResistance;
		this->BendResistance = calibData.BendResistance;
	}

	inline float getAngle() {
		int flexADC = analogRead(targetPin);
		float flexV = flexADC * vcc / 1023.0;
		float flexR = rDiv * (vcc / flexV - 1.0);

		// Serial.println(flexR);
		float angle = map(flexR, straightResistance, BendResistance,
						  0, 90.0);
		
		return angle;
	}
};


#endif //PSDS_FLEX_H


