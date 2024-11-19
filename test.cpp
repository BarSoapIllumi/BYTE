// Motors
const string MF = "motorA"; // Front motor
const string MBL = "motorC"; // Back left motor
const string MBR = "motorD"; // Back right motor
//const string MT = "motorB"; // Tray motor

// Sensors
//const string T = "S1"; // Touch sensor
//const string US = "S2"; // Ultrasonic sensor
const string CColor = "S3"; // Color sensing color sensor
const string CRef = "S2"; // Reflection sensing color sensor
const string G = "S4"; // Gyro sensor
//const string S = "S####"; // Sound Sensor

const CONV = (5.5*PI)/360.0;
int spd = -30;
const int high = 70, low = 30;

// Configures all necessary sensors
void configureSensors(){

/*	// Touch
	SensorType[T] = sensorEV3_Touch;
	wait1Msec(50);

	// Ultrasonic
	SensorType[US] = sensorEV3_Ultrasonic;
	wait1Msec(50);
*/
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
//	SensorType[S] = sensorSoundDBA;
//	wait1Msec(50);

}

// Follows black line
void followLine() {
	
	motor[MF] = spd; // Start legs
	
	// Self correction
	if(SensorValue[CRef] < low){ // Too far left, drive towards right
			
		clearTimer(T2); // Reset faulty case timer
		motor[MBL] = spd + 10; 
		motor[MBR] = spd;
				
	} else if(SensorValue[CRef] > high){ // Too far right, drive towards left
		
		motor[MBL] = spd; 
		motor[MBR] = spd + 10; 
				
	} else { // Following line, go straight
		
		clearTimer(T2); // Reset faulty case timer
		motor[MBL] = motor[MBR] = spd;
				
	}
	
	////////////////////////////////////// OBSTACLE
	
	// Faulty case: robot on the wrong side of the line
	if(time1(T2) > 500){
		spd = -spd; // Reverse speed (reverses correction direction)
	}
	
}


/*
Follows indicated colored line
@param color indicated color to follow
@param home indicates if BYTE is home to complete home procedure
*/
void move(string color, bool home){

	if(home){ // If in home base (within encased rectangle)

		motor[MF] = motor[MBL] = motor[MBR] = spd; // Move forward until it sees line
		while (SensorValue[CRef] > high) {}
		
		resetGyro(G); // Set current heading to 0 degrees
		
		// Turn right 90 degrees
		motor[MBL] = spd; 
		motor[MBR] = -spd;
		while(abs(getGyroDegrees(G)) < 90){}
		
		while (SensorValue[CColor] != color) { // Follow black line ntil color reached
			followLine();
		}	
		
		resetGyro(G); // Set current heading to 0 degrees
		
		// Turn left 90 degrees
		motor[MBL] = -spd; 
		motor[MBR] = spd;
		while(abs(getGyroDegrees(G)) < 90){}
		
	}
		
	while(SensorValue[C] != color){ // While destination not reached

		followLine();

	}
	
	motor[MF] = motor[MBL] = motor[MBR] = 0; // Stop all movement
}

// Main Function
task main()
{
	configureSensors(); // Configure all sensors

	

}