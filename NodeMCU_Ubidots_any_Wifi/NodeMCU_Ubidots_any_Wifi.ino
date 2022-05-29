// This example sends data along with timestamp in POSIX ms standard
// to a variable to Ubidots API through HTTP, TCP or UDP protocol.

/****************************************
 * Include Libraries
 ****************************************/
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-5zcBruZbdvVyGO4YswaqzubqY8QbC1";  // Put here your Ubidots TOKEN
Ubidots ubidots(UBIDOTS_TOKEN);
int value1 = 0;

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}


void setup() {
    // put your setup code here, to run once:
  Serial.begin(115200);
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset settings - for testing
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if(!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(1000);

//  #define WIFI_SSID WiFi.SSID();      // Put here your Wi-Fi SSID
//  #define WIFI_PASS  WiFi.psk();      // Put here your Wi-Fi password
  
//  const char* WIFI_SSID = WIFI;      // Put here your Wi-Fi SSID
//  const char* WIFI_PASS = SENHA;      // Put here your Wi-Fi password


  const char *WIFI = WiFi.SSID().c_str(); //Converte string para char* para não haver probvlema de leitura
  const char *SENHA =WiFi.psk().c_str();//Converte string parar char* para não haver probvlema de leitura

  
  ubidots.wifiConnect(WIFI, SENHA);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

}

void loop() {

  
  unsigned long timestamp_seconds = 1571615253L;  // Put here your timestamp in seconds
  unsigned int timestamp_milliseconds = 0;        // Put here the number of milliseconds to shift your timestamp
  ubidots.add("temperature", value1, NULL, timestamp_seconds, timestamp_milliseconds);  // Change for your variable name
  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  delay(2500);
  value1++;
}
