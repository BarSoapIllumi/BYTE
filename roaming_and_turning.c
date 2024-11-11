//temporary config of motors, cna be changed later depending on the ports
string motorL = motorA;
string motorR = motorD;
string motorTurn = motorC;
string gyroPort = S3;



void roaming(){ //roaming motion cycles: left right sit&turn
	wait1Msec(1000); //left
	motor[motorL] = 50;
	motor[motorR] = 0;

	wait1Msec(100);//right
	motor[motorL] = 0;
	motor[motorR] = 50;

	wait1Msec(100); //sit
	motor[motorL] = motor[motorR] = 10;
	wait1Msec(500);
	motor[motorL] = motor[motorR] = 0;
	wait1Msec(100);
	resetGyro; //turn
	motor[motorTurn] = 50;
	while(abs(getGyroDegrees[gyroPort]) < 360){}
	motor[motorTurn] = 0;



}

void turn(string dir){
	int motorPow = 0;
	if(dir == "L"){
		motorPow = 50;
	}
	if(dir == "R"){
		motorPow = -50;
	}
	wait1Msec(100); //sit
	motor[motorL] = motor[motorR] = 10;
	wait1Msec(500);
	motor[motorL] = motor[motorR] = 0;
	wait1Msec(100);
	resetGyro; //turn

	motor[motorTurn] = 50;
	while(abs(getGyroDegrees[gyroPort]) < 360){}
	motor[motorTurn] = 0;
}



task main()
{
	roaming();
	turn("L");



}
