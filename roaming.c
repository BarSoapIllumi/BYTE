//roaming motion cycles: left right turn

void roaming(){ 
	wait1Msec(1000); //left
	motor[MBL] = 50;
	motor[MBR] = 0;

	wait1Msec(100);//right
	motor[MBL] = 0;
	motor[MBR] = 50;

	
	resetGyro; //turn
	motor[MBL] = 50;
	while(abs(getGyroDegrees[gyroPort]) < 360){}
	motor[MBL] = 0;



}




task main()
{
	
	roaming();
	



}
