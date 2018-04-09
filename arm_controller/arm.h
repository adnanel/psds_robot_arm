#ifndef PSDS_ARM_H
#define PSDS_ARM_H

#include <Servo.h>

class Joint {
	Servo* servo;

	int servoPin;

	float angleOffset;
	float currentAngle;

public:
	inline Joint(int servoPin, float initialAngle, float angleOffset) {
		this->servoPin = servoPin;

		this->currentAngle = initialAngle;
		this->angleOffset = angleOffset;

		this->servo = new Servo();
		this->servo->attach(servoPin);

		this->servo->write(initialAngle);
	}

	inline Servo* getServo() {
		return servo;
	}

	inline float getAngleOffset() {
		return angleOffset;
	}
	inline float getCurrentAngle() {
		return currentAngle;
	}
	inline void setAngleOffset(float angleOffset) {
		this->angleOffset = angleOffset;
	}
	inline void setCurrentAngle(float currentAngle) {
		this->currentAngle = currentAngle;
	}

	inline ~Joint() {
		delete servo;
	}
};

class Arm {
	Joint* joints;
	int count;
public:
	inline Arm(const Joint* joints, int count) {
		this->count = count;

		this->joints = joints;
	}

	inline void update() {
		for ( int i = 0; i < count; ++ i ) {
			joints[i].getServo()->write(joints[i].getCurrentAngle() + joints[i].getAngleOffset());
		}
	}

	~Arm() {
		delete[] joints;
	}
};

#endif //PSDS_ARM_H
