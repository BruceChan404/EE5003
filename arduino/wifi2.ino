
/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using the WiFi module.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */


#include <SPI.h>
#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>
#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Redmi_7429";        // your network SSID (name)
char pass[] = "blowfish1";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int dataflag=0;
int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
//char server[] = "192.168.31.140";    // name address for Google (using DNS)
char server[] = "192.168.31.140";

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 1234)) {
    Serial.println("connected to server");
    // Make a HTTP request:
//    client.println("哈哈连上了这是arduino发来的第一行");
//    client.println("这是第二行");
//    client.println("这是第三行");
//    client.println();
  }
    if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  delay(10);
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
//    client.println("哈哈，连上了");
    char c = client.read();
    Serial.write(c);
    if (c == '0')//服务器返回了0
      {
        Serial.println("失败了");
        dataflag = 0;
//              Serial.print("dataflag=");
//      Serial.println(dataflag);
        }
      if (c == '1')//服务器返回了1
      {
//        Serial.println("成功了");
        dataflag = 1;
//        Serial.print("dataflag=");
//        Serial.println(dataflag);
        }
      }
//      Serial.print("dataflag=");
//      Serial.println(dataflag);
  if(dataflag==1) {
//        client.println("ok了");
//        Serial.println("ok了");
  
  float x, y, z;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
  }      
  float ax, ay, az;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }
  int sensorValue0 = analogRead(A0);
  sensorValue0 = analogRead(A0);
  float voltage0 = sensorValue0 *(3.3/1023.0)*10;
  int sensorValue1 = analogRead(A1);
  sensorValue1 = analogRead(A1);
  float voltage1 = sensorValue1 *(3.3/1023.0)*10;
  int sensorValue2 = analogRead(A2);
  sensorValue2 = analogRead(A2);
  float voltage2 = sensorValue2 *(3.3/1023.0)*10;

    client.print(voltage0);
    client.print(",");
    client.print(voltage1);
    client.print(",");
    client.print(voltage2);
    client.print(","); 
    client.print(x);
    client.print(",");
    client.print(y);
    client.print(",");
    client.print(z);
    client.print(",");
    client.print(ax);
    client.print(",");
    client.print(ay);
    client.print(",");
    client.print(az);
//    client.print(",");
    client.print("%");
    Serial.print(voltage0);
    Serial.print(",");
    Serial.print(voltage1);
    Serial.print(",");
    Serial.print(voltage2);
    Serial.print(","); 
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.print(",");
    Serial.print(ax);
    Serial.print(",");
    Serial.print(ay);
    Serial.print(",");
    Serial.print(az);
//    Serial.print(",");
    Serial.println(" ");
   }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
