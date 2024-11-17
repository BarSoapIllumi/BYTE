// Motors
const string MF = "motorA"; // Front motor
const string MBL = "motorC"; // Back left motor
const string MBR = "motorD"; // Back right motor
const string MT = "motorB"; // Tray motor

// Sensors
const string T = "S1"; // Touch sensor
const string US = "S2"; // Ultrasonic sensor
const string CColor = "S3"; // Color sensing color sensor
const string CRef = "S####"; // Reflection sensing color sensor
const string G = "S4"; // Gyro sensor
const string S = "S####"; // Sound Sensor

// Configures all necessary sensors
void configureSensors(){

	// Touch
	SensorType[T] = sensorEV3_Touch;
	wait1Msec(50);

	// Ultrasonic
	SensorType[US] = sensorEV3_Ultrasonic;
	wait1Msec(50);

	// Color
	SensorType[CColor] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[CColor] = modeEV3Color_Color;
	wait1Msec(50);
	
	SensorType[CRef] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[CRef] = modeEV3Color_Reflected;
	wait1Msec(50);

	// Gyro
	SensorType[G] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[G] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorMode[G] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
	
	// Sound
	SensorType[S] = sensorSoundDBA;
	wait1Msec(50);

}

// conversion factor
const CONV = (5.5*PI)/360.0;

// Suck and Spit
void Suck_Spit (bool indicator){
    if (indicator == 1){
        motor[MT] = 25;
    }
    else{
        motor[MT] = -25;
    }
    motor[MT] = 0;
}

// Attack when see red
void attack(){
    // counter to track number of times attack sequence happens
    int counter = 0;

    motor[MF] = motor[MBL] = motor[MBR] = spd;

    // byte goes towards object 3 times, moving back 5 cm each time it hits
    if (SensorValue[T] == 1 && counter < 3){
        motor[MF] = motor[MBL] = motor[MBR] = -spd;
        while ((nMotorEncoder)* CONV) > 5){
        }
        counter += 1;
        motor[MF] = motor[MBL] = motor[MBR] = spd;
    }

    // stop moving
    motor[MF] = motor[MBL] = motor[MBR] = 0; 
}

// Main Function
task main()
{
	configureSensors();
	while true {
        // all functions here
        	int initialDist = SensorValue[US];
		// if an object that is red is close to byte, attack
        	if ((SensorValue[CColor] == (int)ColorRed) && initialDist < 10){
            		attack();
        	}
    	}
	
	// get rid of objects inside byte at the end
	if (SensorValue[T] == 1){
		suck_spit(0);
		while (SensorValue[T] == 0)
			{}
	}
}
