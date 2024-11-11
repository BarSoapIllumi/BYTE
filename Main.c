// Motors
const string MF = "motorA"; // Front motor
const string MBL = "motorD"; // Back left motor
const string MBR = "motorB"; // Back right motor
const string MT = "motorD"; // Tray motor

// Sensors
const string T = "S1"; // Touch sensor
const string US = "S2"; // Ultrasonic sensor
const string C = "S3"; // Color sensor
const string G = "S4"; // Gyro sensor
const string IR = "S####"; // IR Sensor

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

	// IR Sensor & Beacon
	SensorType[IR] = sensorEV3_IRSensor;
	wait1Msec(50);
	SensorMode[IR] = modeEV3IR_Seeker;
	wait1Msec(50);
}

/*
Travels to an indicated IR beacon
@param beacon indicated beacon channel
*/
void moveToBeacon(int beacon){

	while(getIRBeaconChannelDirection(IR, beacon) < -5 || getIRBeaconChannelDirection(IR, beacon) > 5){ // Detects heading
		if (getIRBeaconChannelDirection(IR, beacon) < 0) { // If IR beacon is to the left, turn right
			motor[MBL] = -50;
			motor[MBR] = 50;
			motor[MF] = 50;
		} else { // If IR beacon is to the right, turn left
			motor[MBL] = 50;
			motor[MBR] = -50;
			motor[MF] = 50;
		}
	}
	motor[MBL] = motor[MBR] = motor[MF] = 0;

	motor[MBL] = motor[MBR] = motor[MF] = 50; // Move forwards
	while(getIRBeaconChannelStrength(IR, beacon) > 10) { // Detects distance from beacon
		// OBSTACLE AVOID FUNCTION
	}
	motor[MBL] = motor[MBR] = motor[MF] = 0;

}

/*
Brings robot to specified food pile, intakes food, then returns home
@param beacon indicated food pile beacon channel
@return time timeed taken to complete functions
*/
int getFood(int beacon){

	clearTimer(T1); // Reset timer

	moveToBeacon(beacon);

	Suck_Spit(1); // Intakes food

	moveToBeacon(0); //REPLACE WITH HOME

	Suck_Spit(0); // Spits out food

	return time1[T1];

}

// BYTE startup procedure
void start(){

	while(!getButtonPress(buttonEnter)){} // Wait for button enter to be pressed
	roaming();
	//SOUND SENSOR STUFF

	moveToBeacon(0); // REPLACE WITH HOME

}

// Main Function
task main()
{
	configureSensors(); // Configure all sensors

	start(); // Begin start procedure

	while(true){ // All processes here

	}

}
