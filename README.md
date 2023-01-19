# The SNS Dashcam

## Overview 
This project was initially created with the idea that we can connect an M5 Stick CPlus device to a GoPro Hero 8 camera to ultimately create a dash camera. The SNS Dashcam consists of 2 M5 Stick CPlus devices as well as a GoProHero8. The SNS Dashcam detects the sudden acceleration in motion and would
start recording as soon as the crash occurs. One M5 Stick detects the
sudden acceleration and starts the GoProHero8 camera while at the same time the other M5 Stick also
detects the acceleration and sends an SOS message (Qubitro shows crash). 

The project works extraordinary well and went above and beyond our expectations. The project also served as our Emerging Tech Final Project in Fall 2022. 

![My Image](/images/overviewpic.jpg)

## Motivation and Background
Accidents can happen all the time and often without warning. Accidents can be life
altering and can put people in positions where they can’t call for help such as a rolled
over car. Some people would want to call for emergency services or a loved one
depending on the severity of the accident. After accidents happen there are constant calls with insurance companies and police trying to figure out who or what caused the accident as well as who should pay. During accidents, a lot of
emotions can cloud what people remember and what actually occurred.
The situation of a crash involves the car experiencing a sudden “jerk” or increased
acceleration in motion and depending on the severity of the crash can leave the car
immovable. The driver and anyone else in the car experiences this motion and can be
hurt in the process. After the accident, the user can be seriously injured and may not be
able to call for help. The solution that would later become the SNS Dashcam would need
to detect the increased acceleration and send a call for help to a phone number whether
that be emergency services or a loved one to offer help.

![My Image](/images/hflowchart.png)

## Design and Implementation
The SNS Dashcam consists of 2 M5 Stick CPlus devices as well as a GoProHero8. The
GoProHero8 also needs to connect with a phone via WiFi for the M5 Sticks to connect to it
correctly. Overall, the SNS Dashcam detects the sudden acceleration in motion and would
start recording as soon as it happens to get an easy to share clip.
While the phone is connected to the GoPro via the GOPro app, one M5 Stick detects the
sudden acceleration and starts the camera while at the same time the other M5 Stick also
detects the acceleration and sends an SOS message (connect to Qubitro). 

![My Image](/images/flowchart.png)

A phone using the GoPro app needs to be connected to the GoPro is required to keep the connection
between the M5 Stick and GoPro alive. The code for sending the SOS message is included
with our GitHub repository but is not used (covered later). The message that gets sent to
Quibtro is a “1” so that on a graph it would show a spike up from 0s. If the user pushes
the button, a 0 gets sent to Quibtro so it simulates no crashes but changes when
acceleration is detected and sends a “1”. In the future this could be improved to
constantly send 0s but we didn’t want to overload the Qubitro server with spamming
numbers when it's not needed.

## Qubitro Chart
This chart updates on Qubitro with every crash that gets detected. 
![My Image](/images/chart.png)

## Improvements
The project was ultimately a success, however improvements can be made to create a better process and system. We included the code to send an SOS message but it was never used. Additionally, the code could be improved to be always recording and create a clip of the recording.

Big thanks to @aster94 for the GoPro Control library linked below.
https://github.com/aster94/GoProControl

**Group Members** :  Saiansh Raizada and Steven Hobson