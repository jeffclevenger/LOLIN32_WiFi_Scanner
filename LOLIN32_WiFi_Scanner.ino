/*
  This code is made to display quick info on SSIDs in the area
  using ESP32 with integrated OLED (WEMOS-Lolin32)
  Board : WEMOS LOLIN32 (From ESP32 Arduino)
  Upload Speed : 921600
  CPU Frequency 240MHz(WiFi/BT)
  Flash Frequency : 80MHZ
  Partition Scheme : Default
  
*/


#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include "SSD1306.h"



SSD1306Wire  display(0x3c, 5, 4);


void setup()
{

  display.init();
  display.setContrast(255);
  delay(1000);
  display.clear();

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);
  display.println("Setup done");


}


void loop()
{
  display.init();
  // display.flipScreenVertically();
  display.setContrast(255);
  display.setLogBuffer(5, 30);

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();



  if (n == 0) {
    display.println("no networks found");
    display.display();
  } else {

    display.println((String)"SSIDs Found : " + (n));
    

    for (int i = 0; i < n; i++) {
      // Print SSID and RSSI for each network found
      display.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " ":" * ");
      display.println(WiFi.SSID(i));
      //display.println(" (");
      //display.println(WiFi.RSSI(i));
      //display.println(")");



      display.drawLogBuffer(0, 0);
      // Display it on the screen
      display.display();
      delay(2000);

      display.clear();


    }
  }
  display.clear();
  // Wait a bit before scanning again
  delay(5000);
}
