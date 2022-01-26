#include "Servo.h"
#include <map>
//#define ANGLE_TO_US(a) ((int)(map((a),0.0,180.0,MIN_LENGTH,MAX_LENGTH)))
// Constructor
Servo::Servo(int channel, PCA9685* driver, int min, int max) {
    // Initialization
    this->servo_angle = 90; // Angle the servo is to be set at.
    this->channel = channel; // Channel of servo to be controlled.
    this->driver = driver; // Driver of servo to be controlled.
    this->driver->setPWMFreq(FREQ); // Init driver to default frequency.
    this->min_angle = min; // Minimum angle of servo, in degs.
    this->max_angle = max; // Maximum angle of servo, in degs.
    this->max_length = MAX_LENGTH; // Maximum pulse width of pwm.
    this->min_length = MIN_LENGTH; // Minumum pulse width of pwm.
}

Servo::Servo() {
}

Servo::~Servo() {
}
/*
const float& Servo::constrain(const float &x,const float &a,const float &b){
    if(x < a){
        return a;
    }

    else if (b<x){
        return b;
    }
    else
        return x;
}
*/
int Servo::setAngle(float angle) {
    return this->setAngle(angle, angle);
}

int Servo::setAngle(float angle, float speed) {
    if ((angle > this->max_angle) || (angle < this->min_angle)) {
        cout << angle << " angle is out of range."<<"\n";
        return 1; // Parameter out of range.
    }
    angle=angle/270.0;
    int pwmLength_=angle*MAX_LENGTH+(1-angle)*MIN_LENGTH;
    if ((pwmLength_ >MAX_LENGTH) || (pwmLength_<MIN_LENGTH)){
        cout<<pwmLength_<<" pwmLength is out of range."<<"\n";
        return 1;
    }
    driver->setPWM(channel, 0, pwmLength_);
    return 0; // DONE
}
