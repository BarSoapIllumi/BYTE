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

<<<<<<< HEAD
int spd = -50;

=======
>>>>>>> kianas_functions
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
<<<<<<< HEAD

}

// Follows black line
void followLine() {
	
	motor[MF] = spd; // Start legs
	
	// Self correction
	if(SensorValue[CRef] < 15){ // Too far left, drive towards right
			
		clearTimer(T2); // Reset faulty case timer
		motor[MBL] = spd + 10; 
		motor[MBR] = spd;
				
	} else if(SensorValue[CRef] > 60){ // Too far right, drive towards left
		
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
		while (SensorValue[CRef] > 15) {}
		
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


/*
Brings robot to specified food pile, intakes food, then returns home
@param color indicated food pile color
@return time time taken to complete functions
*/
int getFood(int color){

	clearTimer(T1); // Start timer
	
	move(color, true); // Move from home to indicated color location
	
	Suck_Spit(1); // Intake food
	
	resetGyro(G); // Set current heading to 0 degrees
		
	// Turn right 180 degrees
	motor[MBL] = spd; 
	motor[MBR] = -spd;
	while(abs(getGyroDegrees(G)) < 90){}
	
	move(color, false); // Return home
	
	motor[MF] = motor[MBL] = motor[MBR] = spd; // Go into box
	wait1M(1000);
	
	Suck_Spit(0); // Outtake food

	return time1[T1]; // Return total time taken

}

// BYTE startup procedure
void start(){

	while(!getButtonPress(buttonEnter)){} // Wait for button enter to be pressed
	setSoundVolume(100); // Set volume max
	playSoundFile("bark.MP3"); // Play bark noise
	
	// SOUND SENSOR
	
	while(SensorValue(S) < 50){} // Wait for clap
	playSoundFile("bark.MP3");
	
	motor[MF] = motor[MBL] = motor[MBR] = 0; // End roaming mode

}


// Main Function
task main()
{
	configureSensors(); // Configure all sensors

	start();

	while(true){ // All processes here

		while(SensorValue() != (int)colorBlue){ // Wait till color shown
			getFood((int)colorBlue);
		}

	}
=======
>>>>>>> kianas_functions

}

// conversion factor
const CONV = (5.5*PI)/360.0;

// Suck and Spit
void Suck_Spit (bool indicator){
    if (indicator == 1){
	motor[MT] = 25;
	while (SensorValue[T] == 0)
		{}
    }
    else{
	motor[MT] = -25;
	while (SensorValue[T] == 1)
		{}
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
