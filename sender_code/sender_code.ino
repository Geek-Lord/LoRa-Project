#include <TinyGPS++.h>
#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps; // The TinyGPS++ object

SoftwareSerial ss(RXPin, TXPin); // The serial connection to the GPS device

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop(){
  
 
  while (ss.available() > 0)
  {
    gps.encode(ss.read());
    if (gps.location.isUpdated())
    {
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      double la = gps.location.lat();
      double lo = gps.location.lng();
      LoRa.beginPacket();
      LoRa.print("*");
      LoRa.print(la, 6);
      LoRa.print("*");
      LoRa.print(lo, 6);
      LoRa.print("*");
      LoRa.endPacket();
      Serial.print("\nCordinates sent! \n");
      delay(10000);  //get cordinates every 10s
      /*Serial.print(" \nLongitude= "); 
      Serial.println(gps.location.lng(), 6);
      LoRa.beginPacket();
      LoRa.print(gps.location.lng(), 6);
      LoRa.endPacket();
      Serial.print("\n Latitude sent! \n");
      delay(5000);*/
    }
  }
}
