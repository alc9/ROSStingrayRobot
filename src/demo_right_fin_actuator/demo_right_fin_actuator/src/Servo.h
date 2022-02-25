#ifndef SERVO_H
#define SERVO_H

#include <iostream>
#include <cstddef>
#include <unistd.h>
#include <stdlib.h>
#include "PCA9685.h"

using namespace std;

class Servo {
public:

    Servo(void);
    Servo(int channel, PCA9685* driver, int min = -90, int max = 90);
    ~Servo();
    int setAngle(float);
    int setAngle(float, float);

private:
     // init constructor
    //int targetAngle; // init constructor
    //int speed; // init constructor
    int channel; // init constructor
    PCA9685 * driver; // init constructor
    int max_angle; // init in constructor parameters
    int min_angle; // init in constructor parameters
    int max_length; // init constructor
    int min_length; // init constructor
    static constexpr const float MAX_LENGTH =614.4;//614.4; //515;
    static constexpr const float MIN_LENGTH = 123.1;//123;//103;
    static const int PERIOD = 16667;//19920;//16667
    static const int FREQ =100;//60; //45;
    static const int FULL_RESOLUTION = 4096;
    static const int WIDTH_RESOLUTION = 208;
    int servo_angle; // init constructor
    int pwmLength;

};
#endif
