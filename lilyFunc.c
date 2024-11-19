void detectObstacle(){
      configureSensor();
      // moving forward, until ultrasonic detects something less than 10 cm away
      while(sensorValue[US]<=15){
            int x=0;
            motor(MF)=motor(MB)=0; // motor stop
            wait1Msec(2000);
            resetGyro(S3);
            motor(MF)=-50; // motor motor A = -50, B 50
            motor(MB)=50;
            
            while(sensorValue[US]<=20)
            {}
            motor(MF)=motor(MB)=0;  // motor stop
            x = getGyroDegrees(G); // record the degrees
            
            motor(MF)=motor(MB)=50; // motor forward
            
            while(sensorValue[G]<=-x)
            {}
            motor(MF)=50;
            motor(MB)=-50; // go back - x degrees, A 50 B -50
      }
      
}

void punishHim(){ //wait how do we indicate how byte will need to be punished
      for(int i=0; i<4; i++){ //spinning 360
            motor(MF)=70;
            motor(MB)=-70;    
      }
      
      for (int j=0; i<3;I++){ //moving forwards and backwards
            motor(MF)=50;
            motor(MB)=50;
            wait1Msec(500);
            motor(MF)=-50;
            motor(MB)=-50;
      }
      
      motor(MF)=motor(MB)=0;
      suck_spit(1); // spit suck function uncalled
}
