
#include <ESP8266WiFi.h>                                                    // esp8266 library
#include <FirebaseArduino.h>                                                // firebase library
#define FIREBASE_HOST "logdata-pc.firebaseio.com"                         // the project name address from firebase id

#define WIFI_SSID "kunjuzzz"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "kunjuzzz"                                    //password of wifi ssid
                                                     
void setup() {
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST);                              // connect to firebase                                                              //Start reading dht sensor
}

void loop() { 
  
  String fireTemp ="anil";                                                    //convert integer temperature to string temperature
  delay(1000);
  Firebase.pushString("/DHT11/Humidity", fireTemp);                                  //setup path and send readings
}
