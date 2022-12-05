//Emerging Tech Final Project
//Connects to Quibtro to finalize 

#include <GoProControl.h>
#include <M5StickCPlus.h>

#include <QubitroMqttClient.h>
#include <WiFi.h>

//Has needed credentials
#include "Secrets.h"

WiFiClient wifiClient;
QubitroMqttClient mqttClient(wifiClient);

//Sets up wifi
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  M5.Lcd.println();
  M5.Lcd.print("Connecting to ");
  M5.Lcd.println(ssid);

  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println("");
  M5.Lcd.println("WiFi connected");
  M5.Lcd.println("IP address: ");
  M5.Lcd.println(WiFi.localIP());
}
//For Acceleration data
float accX = 0;
float accY = 0;
float accZ = 0;

void setup(){
  M5.begin();
  setup_wifi();
  qubitro_init();
//Acceleration init has to go after qubitro_init for whatever reason
  M5.IMU.Init();
}

//Quibtro Run
void qubitro_init() {
  char host[] = "broker.qubitro.com";
  //Unsecured port but it works
  int port = 1883;
  mqttClient.setId(deviceID);
  mqttClient.setDeviceIdToken(deviceID, deviceToken);
  M5.Lcd.println("Connecting to Qubitro...");
  if (!mqttClient.connect(host, port)){
    M5.Lcd.print("Connection failed. Error code: ");
    M5.Lcd.println(mqttClient.connectError());
    M5.Lcd.println("Visit docs.qubitro.com or create a new issue on github.com/qubitro");
  }
  M5.Lcd.println("Connected to Qubitro.");
  mqttClient.subscribe(deviceID);
  delay(5000);
}


void loop() {
  M5.update();
//Upon a hard jerk, Show a 1 for a crash
  M5.IMU.getAccelData(&accX, &accY, &accZ);
    if (accX >= 7 || accY >= 7) {
      M5.Lcd.print('Detecting Crash');
      mqttClient.poll();
      int number = 1;
      static char payload[256];
      snprintf(payload, sizeof(payload)-1, "{\"Crash Data b\":%d}", number);
      mqttClient.beginMessage(deviceID);
      mqttClient.print(payload); 
      mqttClient.endMessage();  
      M5.Lcd.print("Publishing new data-> ");
      M5.Lcd.println(payload);
      delay(500);
    }
//Show 0s when pressing main button for no crash
//Might be better to change to send one every 5 seconds or so.
  if (M5.BtnA.wasReleased()) { 
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    M5.Lcd.print('A');
    mqttClient.poll();
    int number = 0;
    static char payload[256];
    snprintf(payload, sizeof(payload)-1, "{\"Crash Data b\":%d}", number);
    mqttClient.beginMessage(deviceID);
    mqttClient.print(payload); 
    mqttClient.endMessage();  
    M5.Lcd.print("Publishing new data-> ");
    M5.Lcd.println(payload);
  }
} 
  

