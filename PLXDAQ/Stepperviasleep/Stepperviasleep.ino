#include <AccelStepper.h>
#define HALFSTEP 8  //Half-step mode (8 step control signal sequence)
 
// Motor pin definitions
#define mtrPin1  8     // IN1 on the ULN2003 driver 1
#define mtrPin2  9     // IN2 on the ULN2003 driver 1
#define mtrPin3  10     // IN3 on the ULN2003 driver 1
#define mtrPin4  11     // IN4 on the ULN2003 driver 1
 
AccelStepper stepper1(HALFSTEP, mtrPin1, mtrPin3, mtrPin2, mtrPin4);
 
void setup() 
{
  stepper1.setMaxSpeed(1000.0);
}
 
void loop() 
{
stepper1.setSpeed(1000);
for(int i=0;i<32500;i++)
stepper1.runSpeed();
delay(1000);
stepper1.setSpeed(500);
for(int i=0;i<32500;i++)
stepper1.runSpeed();
delay(1000);
stepper1.setSpeed(100);
for(int i=0;i<32500;i++)
stepper1.runSpeed();
delay(1000);
stepper1.setSpeed(0);
for(int i=0;i<32500;i++)
stepper1.runSpeed();
delay(1000);
}
