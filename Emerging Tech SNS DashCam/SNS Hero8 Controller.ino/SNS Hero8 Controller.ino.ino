//Emerging Tech Project

#include <GoProControl.h>
#include <M5StickCPlus.h>
//#include <GoProControl.cpp>
//#include <Settings.h>
#include "Secrets.h"

#define KEEP_ALIVE 2500
#define MAX_WAIT_TIME 2000


enum camera
{
  HERO = 1,
  HERO2,
  HERO3,
  HERO4,
  HERO5,
  HERO6,
  HERO7,
  FUSION,
  HERO8,
  MAX
};

// The above settings must be between a "*_first" and "*_last" member
enum mode
{
  mode_first = 0,
  VIDEO_MODE,
  VIDEO_SUB_MODE,
  VIDEO_PHOTO_MODE,
  VIDEO_TIMELAPSE_MODE,
  VIDEO_LOOPING_MODE,
  VIDEO_TIMEWARP_MODE,

  PHOTO_MODE,
  PHOTO_SINGLE_MODE,
  PHOTO_NIGHT_MODE,

  MULTISHOT_MODE,
  MULTISHOT_BURST_MODE,
  MULTISHOT_TIMELAPSE_MODE,
  MULTISHOT_NIGHTLAPSE_MODE,

  BURST_MODE,
  TIMELAPSE_MODE,
  TIMER_MODE,
  PLAY_HDMI_MODE,
  mode_last
};

enum orientation
{
  orientation_first = mode_last + 1,
  ORIENTATION_UP,
  ORIENTATION_DOWN,
  ORIENTATION_AUTO,
  orientation_last
};

enum video_resolution
{
  video_resolution_first = orientation_last + 1,
  VR_5p6K,
  VR_4K,
  VR_2K,
  VR_2K_SuperView,
  VR_1440p,
  VR_1080p_SuperView,
  VR_1080p,
  VR_960p,
  VR_720p_SuperView,
  VR_720p,
  VR_WVGA,
  video_resolution_last
};

enum video_fov
{
  video_fov_first = video_resolution_last + 1,
  DUAL360_FOV,
  WIDE_FOV,
  MEDIUM_FOV,
  NARROW_FOV,
  LINEAR_FOV,
  video_fov_last
};

enum frame_rate
{
  frame_rate_first = video_fov_last + 1,
  FR_240,
  FR_120,
  FR_100,
  FR_90,
  FR_80,
  FR_60,
  FR_50,
  FR_48,
  FR_30,
  FR_25,
  FR_24,
  FR_15,
  FR_12p5,
  FR_12,
  frame_rate_last
};

enum video_encoding
{
  video_encoding_first = frame_rate_last + 1,
  NTSC,
  PAL,
  video_encoding_last
};

enum photo_resolution
{
  photo_resolution_first = video_encoding_last + 1,
  PR_12MP_WIDE,
  PR_12MP_MEDIUM,
  PR_12MP_NARROW,
  PR_12MP_LINEAR,
  PR_11MP_WIDE,
  PR_8MP_WIDE,
  PR_8MP_MEDIUM,
  PR_7MP_WIDE,
  PR_7MP_MEDIUM,
  PR_5MP_WIDE,
  PR_5MP_MEDIUM,
  photo_resolution_last
};

#if defined(ARDUINO_ARCH_ESP32)
const uint8_t BLE_WiFiOn[] = {17, 01, 01};
const uint8_t BLE_WiFiOff[] = {17, 01, 00};
const uint8_t BLE_RecordStart[] = {01, 01, 01};
const uint8_t BLE_RecordStop[] = {01, 01, 00};
const uint8_t BLE_ModeVideo[] = {02, 01, 00};
const uint8_t BLE_ModePhoto[] = {02, 01, 01};
const uint8_t BLE_ModeMultiShot[] = {02, 01, 02};
#endif


/*
  Control your GoPro with the Serial Monitor
  edit the file Secrets.h with your camera netword name and password
  CAMERA could be: HERO3, HERO4, HERO5, HERO6, HERO7, FUSION, HERO8, MAX
*/

#define CAMERA HERO8 // Change here for your camera

GoProControl gp(GOPRO_SSID, GOPRO_PASS, CAMERA);

float accX = 0;
float accY = 0;
float accZ = 0;

void setup(){
  gp.enableDebug(&Serial);
  M5.begin();
  M5.IMU.Init();
  // pinMode(10, OUTPUT);
  // digitalWrite(10, LOW);
}

void loop(){
  M5.update();
  //jerk detector
  while (1) {
      M5.IMU.getAccelData(&accX, &accY, &accZ);
      if (accX > 1.5 || accY > 1.5) {
          break;
      }
  }  

  //gopro controls
  gp.begin();
  M5.Lcd.fillScreen(TFT_RED);
  M5.Lcd.println(gp.isConnected() == true ? "connected" : "not connected");
  gp.setMode(VIDEO_MODE);
  gp.shoot();
  M5.Lcd.println(gp.isRecording() == true ? "recording" : "not recording");
  delay(30000);
  gp.stopShoot();
  M5.Lcd.println(gp.isRecording() == true ? "recording" : "stopped recording");
  gp.end();
  gp.keepAlive(); // not needed on HERO3
}


  //gopro func list
  // char in = 0;
  // if (Serial.available() > 0)
  // {
  //   in = Serial.read();
  // }

  // switch (in)
  // {
  // default:
  //   break;

  // // Connect
  // case 'b':
  //   gp.begin();
  //   break;

  // case 'c':
  //   Serial.print("Connected: ");
  //   Serial.println(gp.isConnected() == true ? "Yes" : "No");
  //   break;

  // case 'p':
  //   gp.confirmPairing();
  //   break;

  // case 's':

  //   if (CAMERA == HERO8)
  //   {
  //     char * statusChar;
  //     statusChar = gp.getStatus();
  //     Serial.println("Status :");
  //     for(int i = 0; i < 56; i++)
  //     {
  //       Serial.print(statusChar[i], HEX);Serial.print(" ");
  //     }
  //     Serial.println("");
  //     Serial.println("End Status.");
  //     if (statusChar[0] == 0x00){Serial.println("camera ON");}
  //     else{Serial.println("camera OFF");}
  //     free(statusChar); // Don't forget to free memory
  //   }

  //   else
  //   {
  //     char * statusChar;
  //     statusChar = gp.getStatus();
  //     Serial.println("Status :");
  //     Serial.println(statusChar);
  //     free(statusChar); // Don't forget to free memory
  //   }
    
  //   break;

  // case 'm': // DO NOT USE WHEN CAMERA IS OFF, IT FREEZE ESP
  //   char* medialist;
  //   medialist = gp.getMediaList();
  //   Serial.println("Media List:");
  //   Serial.println(medialist);
  //   free(medialist); // Don't forget to free memory
  //   break;

  // // Turn on and off
  // case 'T':
  //   gp.turnOn();
  //   break;

  // case 't':
  //   gp.turnOff();
  //   break;

  // // Take a picture of start a video
  // case 'A':
  //   gp.shoot();
  //   break;

  // // Stop the video
  // case 'S':
  //   gp.stopShoot();
  //   break;

  // // Check if it is recording
  // case 'r':
  //   Serial.print("Recording: ");
  //   Serial.println(gp.isRecording() == true ? "Yes" : "No");
  //   break;

  // // Set modes
  // case 'V':
  //   gp.setMode(VIDEO_MODE);
  //   break;

  // case 'P':
  //   gp.setMode(PHOTO_MODE);
  //   break;

  // case 'M':
  //   gp.setMode(MULTISHOT_MODE);
  //   break;

  // // Change the orientation
  // case 'U':
  //   gp.setOrientation(ORIENTATION_UP);
  //   break;

  // case 'D':
  //   gp.setOrientation(ORIENTATION_DOWN);
  //   break;

  // // Change other parameters
  // case 'f':
  //   gp.setVideoFov(MEDIUM_FOV);
  //   break;

  // case 'F':
  //   gp.setFrameRate(FR_120);
  //   break;

  // case 'R':
  //   gp.setVideoResolution(VR_1080p);
  //   break;

  // case 'h':
  //   gp.setPhotoResolution(PR_12MP_WIDE);
  //   break;

  // case 'L':
  //   gp.setTimeLapseInterval(60);
  //   break;

  // // Localize the camera
  // case 'O':
  //   gp.localizationOn();
  //   break;

  // case 'o':
  //   gp.localizationOff();
  //   break;

  // // Delete some files, be carefull!
  // case 'l':
  //   gp.deleteLast();
  //   break;

  // case 'g':
  //   gp.deleteAll();
  //   break;

  // Print useful data
  // case 'd':
  //   gp.printStatus();
  //   break;

  // Close the connection
  // case 'X':
  //   gp.end();
  //   break;
  // }
