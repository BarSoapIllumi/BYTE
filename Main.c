// Motors
const string MF = "motorA"; // Front motor
const string MBL = "motorC"; // Back left motor
const string MBR = "motorD"; // Back right motor
const string MT = "motorB"; // Tray motor

// Sensors
const string T = "S1"; // Touch sensor
const string US = "S2"; // Ultrasonic sensor
const string C = "S3"; // Color sensor
const string G = "S4"; // Gyro sensor
const string S = "S####"; // Sound Sensor

const int spd = 50;

// Configures all necessary sensors
void configureSensors(){

	// Touch
	SensorType[T] = sensorEV3_Touch;
	wait1Msec(50);

	// Ultrasonic
	SensorType[US] = sensorEV3_Ultrasonic;
	wait1Msec(50);

	// Color
	SensorType[C] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[C] = modeEV3Color_Color;
	wait1Msec(50);

	// Gyro
	SensorType[G] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[G] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorMode[G] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);

}

/*
Follows indicated colored line
@param color indicated color to follow
@param home indicates if BYTE is home to complete home procedure
*/
/*
void moveToBeacon(string color, bool home){

	bool follow;

	if(home){ // If in home base (within encased rectangle)

		while(SensorValue[C] != (int)color){ // While not seeing color

			follow = true;

			if(SensorValue[C] != (int)colorBlack){
				// Go forward
				motor[MBL] = spd;
				motor[MBR] = spd;
				motor[MF] = spd;
				follow = false;
			}
			while(SensorValue[C] != (int)colorBlack){ // While not following black line
				// Go forward
				motor[MBL] = spd;
				motor[MBR] = spd;
				motor[MF] = spd;
			}

			resetGyro(G); // Reset gyro degree

			// Turn
			motor[MBL] = spd;
			motor[MBR] = -spd;
			motor[MF] = -spd;
			while(abs(getGyroDegrees(G)) < 90){} // Wait for 90 degree turn



		}
	}

}
*/

/*
Brings robot to specified food pile, intakes food, then returns home
@param beacon indicated food pile beacon channel
@return time timeed taken to complete functions
*/
int getFood(int beacon){

	clearTimer(T1);

	return time1[T1];

}

// BYTE startup procedure
void start(){

	while(!getButtonPress(buttonEnter)){} // Wait for button enter to be pressed
//	roaming();
	//SOUND SENSOR STUFF


}

void testColor(){
	while(true){

	motor[MBL] = motor[MBR] = spd;
	while(getColorReflected(S3) < 1000) {}

	motor[MBL] = motor[MBR] = -spd;
	while(SensorValue[C] != (int)colorRed){}

	}
}

// Main Function
task main()
{
	configureSensors(); // Configure all sensors

	//start(); // Begin start procedure

	testColor();
/*
	while(true){ // All processes here

	}
*/
}
