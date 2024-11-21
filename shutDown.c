
const string MT = "motorA"; // Tray motor


void Suck_Spit (bool indicator, int time){
    if (indicator == 1){
        motor[MT] = 25;
    }
    else{
        motor[MT] = -25;
    }
	wait1Msec(time);
    motor[MT] = 0;
}


void shutDown(){
	while(!getButtonPressed(ButtonEnter)){}
	while(getButtonPressed(ButtonEnter)){}
	wait1Msec(50);

	while(!getButtonPressed(ButtonEnter)){}
	while(getButtonPressed(ButtonEnter)){}

	Suck_Spit(0, 10000);

}

task main()
{
	configureSensors();
	shutDown();





}
