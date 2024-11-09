#include <iostream>
using namespace std;




/* Suck and Spit: Need to suck in food, and spit it out */
string motor[motorA] = "m1";
string motor[motorB] = "m2";
string motor[motorC] = "m3";
string motor[motorD] = "m4";

const CONV = (5.5*PI)/360.0;

void Suck_Spit (bool indicator){
    if (indicator == 1){
        m3 = 25;
    }
    else{
        m3 = -25;
    }
    m3 = 0;
}

/* Attack when see Red: use color sensor value and move forward fast and hit touch sensor three times then stop*/

void attack(){
    int counter = 0;
    configureAllSensors();
    m1 = m4 = 50;
    if (SensorValue[T] == 1 && counter < 3){
        m1 = m4 = -25;
        while ((nMotorEncoder)* CONV) > 5){
        }
        counter += 1;
        m1 = m4 = 50;
    }
    m1 = m4 = 0;
}

task main(){
    int initialDist = SensorValue[US];
    if ((SensorValue[C] == (int)ColorRed) && initialDist < 10){
        attack();
    }
}
