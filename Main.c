// Sensors
const string T = "S1"; // Touch sensor
const string US = "S2"; // Ultrasonic sensor
const string CColor = "S3"; // Color sensing color sensor
const string CRef = "S####"; // Reflection sensing color sensor
const string G = "S4"; // Gyro sensor
const string S = "S####"; // Sound Sensor

const CONV = (5.5*PI)/360.0;
int spd = -50;
const int high = 70, low = 30;

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

void straight(bool dir){
	if (bool == 1){
		motor[motorB] = motor[motorD] = motor[motorC] = spd;
	}
	else{
		motor[motorB] = motor[motorD] = motor[motorC] = -spd;
	}
	
}
// Follows black line
void followLine() {
	
	straight(1) // Start legs
	
	// Self correction
	if(SensorValue[CRef] < low){ // Too far left, drive towards right
			
		clearTimer(T2); // Reset faulty case timer
		motor[motorD] = spd + 10; 
		motor[motorC] = spd;
				
	} else if(SensorValue[CRef] > high){ // Too far right, drive towards left
		
		motor[motorD] = spd; 
		motor[motorC] = spd + 10; 
				
	} else { // Following line, go straight
		
		clearTimer(T2); // Reset faulty case timer
		motor[motorD] = motor[motorC] = spd;
				
	}
	
	if(detectObstacle()){
		straight(1); // Move forward until it sees line
		while (SensorValue[CRef] > high) {}
		
		resetGyro(G); // Set current heading to 0 degrees
		
		// Turn right 90 degrees
		motor[motorD] = spd; 
		motor[motorC] = -spd;
		while(abs(getGyroDegrees(G)) < 90){}
		
	}
	
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

		straight(1); // Move forward until it sees line
		while (SensorValue[CRef] > high) {}
		
		resetGyro(G); // Set current heading to 0 degrees
		
		// Turn right 90 degrees
		motor[motorD] = spd; 
		motor[motorC] = -spd;
		while(abs(getGyroDegrees(G)) < 90){}
		
		while (SensorValue[CColor] != color) { // Follow black line ntil color reached
			followLine();
		}	
		
		resetGyro(G); // Set current heading to 0 degrees
		
		// Turn left 90 degrees
		motor[motorD] = -spd; 
		motor[motorC] = spd;
		while(abs(getGyroDegrees(G)) < 90){}
		
	}
		
	while(SensorValue[C] != color){ // While destination not reached

		followLine();

	}
	
	motor[motorB] = motor[motorD] = motor[motorC] = 0; // Stop all movement
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
	motor[motorD] = spd; 
	motor[motorC] = -spd;
	while(abs(getGyroDegrees(G)) < 90){}
	
	move(color, false); // Return home
	
	motor[motorB] = motor[motorD] = motor[motorC] = spd; // Go into box
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
	
	motor[motorB] = motor[motorD] = motor[motorC] = 0; // End roaming mode

}

/*////////////////////////////////////////////////////////////////////////////////
Kiana Functions
*/////////////////////////////////////////////////////////////////////////////////

// Suck and Spit
void Suck_Spit (bool indicator){
    if (indicator == 1){
	motor[motorA] = 25;
	while (time(T1) < 5/1000.0)
		{}
    }
    else{
	motor[motorA] = -25;
	while (time(T1) < 5/1000.0)
		{}
    }
    motor[motorA] = 0;
}

// Attack when see red
void attack(){
    // counter to track number of times attack sequence happens
    int counter = 0;

    motor[motorB] = motor[motorD] = motor[motorC] = spd;

    // byte goes towards object 3 times, moving back 5 cm each time it hits
    if (counter < 3){
        straight(1);
        while ((nMotorEncoder)* CONV) > 5){
        }
        counter += 1;
        straight(1);
    }

    // stop moving
    motor[motorB] = motor[motorD] = motor[motorC] = 0;
}


/*////////////////////////////////////////////////////////////////////////////////
Lily Functions
*////////////////////////////////////////////////////////////////////////////////

// Detects obstacle, avoids it, then returns to original path
bool detectObstacle(){
	
	bool obsDec=false;

    if(sensorValue[US]<=15){
    	obsDec=true;
        int degrees = 0;
        motor[motorB] = motor[motorD] = motor[motorC] = 0; // motor stop
        wait1Msec(1000);
        resetGyro(G);
           
	motor[motorC]= -spd; // motor motor A = -50, B 50 FUCKING TURN THaT SHIT AROUND
        straight(1); // fucking forward
		while(sensorValue[US]<=20){}
        degrees=getGyroDegrees(G);
        motor[motorD]=spd;
	motor[motorB]=spd;
           
        while(true){
            motor[motorD]=spd;
			motor[motorB]=spd;
			wait1Msec(1000);
			resetGyro(G);
			motor[motorC]= spd; // motor motor A = -50, B 50 FUCKING TURN THaT SHIT AROUND
			motor[motorC]=motor[motorB]= -spd;
			while(abs(getGyroDegrees(G)<=90+degrees)){}
			motor[motorB]=motor[motorD]=motor[motorC]=0;
			if(sensorValue[US]>=35){
            			break;
			}
			else
			{
				resetGyro(G);
				motor[motorC]= -spd; // motor motor A = -50, B 50 FUCKING TURN THaT SHIT AROUND
				motor[motorD]=motor[motorB]= spd;
				while(abs(getGyroDegrees(G)<=90+degrees)){}
			}
		}
   
      }
      return obsDec;
}

// Perform a trick when time exceeded
void punishHim(){ 

      for(int i=0; i<4; i++){ //spinning 360 4 times
      		resetGyro(G); // Set current heading to 0
            motor[motorB]=70;
            motor[motorD]=-70;    
            motor[motorC]=70; 
            while(abs(getGyroDegrees(g) <= 360){} // Turn 360 degrees
      }
      
      for (int j=0; i<3;I++){ //moving forwards and backwards 3x
     		motor[motorB]=70; // Move forward
            motor[motorD]=spd;
            motor[motorC]=spd;
            wait1Msec(500);
            motor[motorB]=-spd; // Move backwards
            motor[motorD]=70;
            motor[motorC]=-spd;
            wait1Msec(500);
      }
      // Stop movement
      motor[motorB]=0;
      motor[motorC]=motor[motorD]=0;
      
      Suck_Spit(1); // spit suck function uncalled
}



// Main Function
task main()
{
	configureSensors(); // Configure all sensors

	start();

	while(true){ // All processes here
	
		int initialDist = SensorValue[US];
	
		getFood((int)colorBlue);
       	
		// if an object that is red is close to byte, attack
        if (//input sound sensor thresholds here){
       		attack();
        }
    }
	
	// get rid of objects inside byte at the end
	if (shutdown()){
		suck_spit(0);
		while (time(T1) < 10){}
	}

}
