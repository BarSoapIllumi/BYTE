# BYTE

### How to Get Files on Computer:
1. Download Git Bash
2. Go to the folder you want the BYTE folder to be in
  * Right click on folder and click "open git bash here"
3. Copy paste these lines in, in order (paste in git bash is shift + insert):
  * git config --global user.email “[your email here]”
  * git clone https://github.com/BarSoapIllumi/BYTE
Yipee! You have the folder linked to the repository!!

### How to Make Changes:
1. Right click the new BYTE folder and click "open git bash here"
2. Add the file(s) and push the changes into online repository. Copy paste these lines to Git Bash, in order:
  * git add <filename(not the file path)>
  * git commit -m "comments you want to add"
  * git push

### Making Changes While Using Branches:
1. Right click the new BYTE folder and click "open git bash here"
2. Check which branches are currently open
  * git branch
    - It outputs a list of active branches. The branch you are currently on is highlighted with * in front of the name
3. Create and/or switch to another branch
  * create --> git branch [branch name]
  * switch (must use this after create) --> git checkout [branch name]
4. Add the file(s) & create branch
  * git add <filename(not the file path)>
  * git commit -m "comments"
  * first time pushing branch --> git push -u origin [branch name]
  * not the first time --> git push
5. Idk how to merge the changes in git bash, so to merge:
  * Go to GitHub (the online one)
  * Top left, under "BYTE" you will see the branch drop down. Select your branch.
  * Press massive green "Compare & pull request" button
  * Give it a title(this is the same as commenting when committing) then press "Create pull request"
  * Git will automatically try to merge. If it works, just click "Merge pull request" and you're done! If it didn't, you have to revise the conflicts 1 by 1.

### Retriving Changes Made by Others:
https://docs.github.com/en/get-started/using-git/getting-changes-from-a-remote-repository

Note.
Branches are simultaneous versions of the code. Changes, like new functions or fixes, should first be done in a branch to make sure the main always stays functional. Only alter the main branch once the branch is fully functional. It helps keeps code organized when many people work on it.

# Coding Literacy
If you guys want to change these go ahead just a start so far!
### Names of Motors
* const string MF = motorA;
* const string MB = motorD;;
* const string MFW = motorC;
* const string MT = motorB;

### Names of Sensors
* const string T = "S1"; //touch
* const string US = "S2"; //ultrasonic
* const string C = "S3"; //color
* const string G = "S4"; //gyro


Sensor Config & Modes
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

### All RobotC Comomands
https://www.robotc.net/WebHelpMindstorms/index.htm
