#include <AccelStepper.h>
#include <Servo.h>
#define HALFSTEP 8  
#define mtrPin1  8     
#define mtrPin2  9     
#define mtrPin3  10    
#define mtrPin4  11  
Servo serv;  
int flag=0;   
AccelStepper stepper1(HALFSTEP, mtrPin1, mtrPin3, mtrPin2, mtrPin4);
int readSleep;
int c;
int k;
int s;
int bzpin=3;
void setup() {
 
 Serial.begin(38400); 
 serv.attach(6);
 serv.write(0);
 stepper1.setMaxSpeed(1000.0);            
 Serial.println("CLEARDATA");        
 Serial.println("LABEL,Read Sleep,Condition"); 
 c=2; 
 stepper1.setSpeed(1000);
 stepper1.runSpeed();
 pinMode(bzpin,OUTPUT);
 
                                    
}
void callServo()
{
  digitalWrite(bzpin,HIGH);
  
  serv.write(0);
  stepper1.runSpeed();
  
  serv.write(90);
  stepper1.runSpeed();
  
  serv.write(180);
  stepper1.runSpeed();
  
  stepper1.runSpeed();
  
}

void loop() {
  Serial.println( (String) "CELL,GET,FROMSHEET,Sheet1,B,"+c);
  readSleep = Serial.readStringUntil(10).toInt();
  if(readSleep==0)
  {
  Serial.println("PAUSELOGGING");
  while(true)
  {}
  }
  else if(readSleep==1)
  {
    stepper1.setSpeed(100);
    
  }
 else if(readSleep==2)
 {
   stepper1.setSpeed(300);
   
 }
 else if(readSleep==3)
 {
   stepper1.setSpeed(1000);
   digitalWrite(bzpin,LOW);
    
 }

  Serial.print("DATA");
  Serial.print(",");
  Serial.print(readSleep);
  Serial.print(",");
  if(readSleep==3)
  {
  Serial.println("Very Awake");
  flag=0;
  }
  else if(readSleep==2)
  {
  flag=1;
  Serial.println("Awake");
  }
  else if(readSleep==1)
  {
  Serial.println("Asleep");
  flag=1;
  }
 
  
  c++;
  uint32_t period = 1 * 1000L;  //to keep as 1 minute to sync with data from #fitbit servers.
  for( uint32_t tStart = millis();  (millis()-tStart) < period;  )
  {
  stepper1.runSpeed();
  if(flag==1)
  {
    
  
  callServo();
  }
  }
  
  }
  

