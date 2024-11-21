int spd = -30; // Default speed
const int high = 50, low = 10; // Color reflection threshold

// Configures all necessary sensors
void configureSensors(){

	// Colors
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

	SensorType[S2] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Color_Reflected;
	wait1Msec(50);

	// Gyro
	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);

	// Sound
	SensorType[S] = sensorSoundDBA;
	wait1Msec(50);

}

void Suck_Spit(bool indicator){
    if (indicator == 1){
		motor[motorB] = -100;
	//while (SensorValue[T] == 0){}
    }
    else{
		motor[motorB] = 100;
	//while (SensorValue[T] == 1){}
    }
    wait1Msec(5000);
    motor[motorB] = 0;
}

// Follows black line
void followLine() {

	motor[motorA] = spd; // Start legs

	// Self correction
	if(SensorValue[S2] < low){ // Too far left, drive towards right

		clearTimer(T2); // Reset faulty case timer
		motor[motorC] = spd;
		motor[motorD] = spd + 30;
		wait1Msec(1000);
		motor[motorC] = motor[motorD] = spd;
		
//		displayTextLine(5, "%s%d", "The [low] value is ", SensorValue[S2]);

		} else if(SensorValue[S2] > high){ // Too far right, drive towards left

		motor[motorC] = spd + 15;
		motor[motorD] = spd;
		wait1Msec(1000);
		motor[motorC] = motor[motorD] = spd;
//		displayTextLine(10, "%s%d", "The [high] value is ", SensorValue[S2]);

		} else { // Following line, go straight

		clearTimer(T2); // Reset faulty case timer
		motor[motorC] = motor[motorD] = spd;

	}

	////////////////////////////////////// OBSTACLE

	// Faulty case: robot on the wrong side of the line
	/*	
	if(time1(T2) > 1000){
	 	spd = -spd; // Reverse speed (reverses correction direction)
		}
*/
}

/*
Follows indicated colored line
@param color indicated color to follow
@param home indicates if BYTE is home to complete home procedure
*/
void move(int color, bool home){

	if(home){ // If in home base (within encased rectangle)

		straight(1); // Move forward until it sees line
		while (SensorValue[S2] > high) {}

		resetGyro(S4); // Set current heading to 0 degrees

		// Turn right 90 degrees
		motor[motorC] = spd;
		motor[motorD] = -spd;
		while(abs(getGyroDegrees(S4)) < 90){}

		while (SensorValue[S3] != color) { // Follow black line ntil color reached
			followLine();
		}

		resetGyro(S4); // Set current heading to 0 degrees

		// Turn left 90 degrees
		motor[motorC] = -spd;
		motor[motorD] = spd;
		while(abs(getGyroDegrees(S4)) < 90){}

	}

	while(SensorValue[S3] != color){ // While destination not reached
		displayTextLine(0, "%d", SensorValue[S3]);
		followLine();

	}

	motor[motorA] = motor[motorC] = motor[motorD] = 0; // Stop all movement
}

/*
Brings robot to specified food pile, intakes food, then returns home
@param color indicated food pile color
@return time time taken to complete functions
*/
int getFood(int color){

	clearTimer(T1); // Start timer
	
	move(color, false); // Move from home to indicated color location
	
	Suck_Spit(true); // Intake food
	
	resetGyro(S4); // Set current heading to 0 degrees
		
	// Turn right 180 degrees
	motor[motorC] = spd; 
	motor[motorD] = -spd;
	while(abs(getGyroDegrees(S4)) < 90){}
	
	move(color, false); // Return home
	
	straight(1); // Go into box
	wait1Msec(3000);
	
	Suck_Spit(false); // Outtake food

	return time1[T1]; // Return total time taken

}

// BYTE startup procedure
void start(){

	while(!getButtonPress(buttonEnter)){} // Wait for button enter to be pressed
	setSoundVolume(100); // Set volume max
	playSoundFile("bark.MP3"); // Play bark noise
	

}

/*////////////////////////////////////////////////////////////////////////////////
Kiana Functions
*/////////////////////////////////////////////////////////////////////////////////

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

// Perform a trick when time exceeded
void punishHim(){ 

      for(int i=0; i<4; i++){ //spinning 360 4 times
      		resetGyro(G); // Set current heading to 0
            motor(MF)=70;
            motor(MBR)=-70;    
            motor(MBL)=70; 
            while(abs(getGyroDegrees(g) <= 360){} // Turn 360 degrees
      }
      
      for (int i=0; i<3; i++){ //moving forwards and backwards 3x
     		straight(1); // Move forwards
            wait1Msec(1000);
            straight(0); // Move backwards
            wait1Msec(1000);
      }
      
      motor[motorB] = motor[motorC] = motor[motorD] = 0; // Stops movement
      
}

// Main Function
task main()
{
	bool running = true;
	int runTime = 0;
	
	configureSensors(); // Configure all sensors
	start();
	
	while(running){
		
		while(!getButtonPressed(ButtonAny)){
			if(getButtonPressed(ButtonUp)) {
				while(!getButtonPressed(ButtonEnter)){}
				runTime = getFood((int)colorRed);
			} else if(getButtonPressed(ButtonRight)) {
				while(!getButtonPressed(ButtonEnter)){}
				runTime = getFood((int)colorBlue);
			} else if(getButtonPressed(ButtonLeft)) {
				while(!getButtonPressed(ButtonEnter)){}
				runTime = getFood((int)colorBlack);
			} else if(getButtonPressed(ButtonEnter)) {
				while(!getButtonPressed(ButtonEnter)){}
				running = false;
			}
		}
		
		if(runTime < 5000){
			punishHim();
		}
		
		// SOUND ATTACK THING
		
	}
	
	move((int)colorBlue, false);
}