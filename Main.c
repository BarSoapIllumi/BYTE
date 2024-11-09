// Motors
const string MF = "motorA"; // Front motor
const string MB = "motorD"; // Back motor
const string MW = "motorB"; // Turning wheel motor
const string MT = "motorD"; // Tray motor

// Sensors
const string T = "S1" // Touch sensor
const string US = "S2" // Ultrasonic sensor
const string C = "S3" // Color sensor
const string G = "S4" // Gyro sensor
const string IR = "S#" // IR Sensor

// Configures all necessary sensors
void configureSensors(){
	
	// Touch
	SensorType[T] = sensorEV3_Touch;
	wait1Msec(50);
	
	// Ultrasonic
	SensorType[US] = sensor_EV3_Ultrasonic;
	wait1Msec(50);
	
	// Color
	SensorType[C] = sensor_EV3_Color;
	wait1Msec(50);
	SensorMode[C] = mode_EV3_Color_Color;
	wait1Msec(50);
	
	// Gyro
	SensorType[G] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[G] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorMode[G] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
	
	// IR Sensor & Beacon 
	SensorType[IR] = sensorEV3_IR;
	wait1Msec(50);
	SensorMode[IR] = modeEV3IR_Seeker;
}

// Main Function
task main()
{
	configureSensors();
}
