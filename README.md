
# FitBit_Driver_Fatigue
## INTRODUCTION

## 1.1  AIM
To design a device prototype which will monitor the build-up of fatigue in drivers
and accordingly take steps so that there is no loss of control over the vehicle due to
the driver falling asleep at the wheels. This project’s purpose is to review
published journals regarding:
a) the scale of the sleep related road accident problem
b) to come up with solutions that minimise accidents due to the driver sleeping
off at the wheel and design a suitable prototype which acts as a detection and alert
system in real time.

### 1.2 OBJECTIVES

To Extract health-data from a wearable device, specifically the sleep data
(pre-made by the “Fitbit API”).
1. To process this data using a microcontroller and use the processed data to control
the speed of a stepper motor, which is, analogous to the speed of an actual engine
rotor.
2. To invoke an alarm system.
3. To activate direct speed control of the vehicle whenever alarm fails to alter the sleep state of the driver.

### 1.3 BASIC WORKING
1. The synced data of an individual from a Fitbit device has been successfully extracted in CSV format as shown in Fig 1.4
2. The data synchronises with Fitbit servers every minute and returns three Integer values: 1,2,3.
3. State 1: The subject is in the highest state of consciousness. “Very Awake”
4. State 2: Noticeable Fatigue which will/might be followed by loss of
consciousness. “Awake”
5. State 3: Complete Loss of consciousness. “Asleep”
6. Installation of haptic feedback using vibration motors.
7. Forced Stop of Motor using special parameters from the extracted data.

**Actual model:-**
![Model](https://github.com/souvikchakraborty98/FitBit_Driver_Fatigue/blob/master/actualModel.PNG?raw=true)

*For more info see [this.](https://github.com/souvikchakraborty98/FitBit_Driver_Fatigue/blob/master/Project%20Report.pdf)*
