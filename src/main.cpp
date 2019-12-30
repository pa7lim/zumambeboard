// Example by David PA7LIM
// 
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include "SH1106.h"

#define SD_SELECT 32
#define ETHERNET_SELECT 5 // Ethernet
#define SDA_pin 25 // I2C
#define SCL_pin 26 // I2C
#define RX1_pin 13 // Debug
#define TX1_pin 14 // Debug
#define RX2_pin 16 // AMBE3000 RX
#define TX2_pin 17 // AMBE3000 TX
#define AMBE_RST 21 // AMBE reset PIN
#define XCODE_LED 27 // LED on Board  
#define STAT_LED 33 // LED on Board


#define VERSION 1
#define RELEASE 0

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 100);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 1, 1);
IPAddress dns(8, 8, 8, 8);

SH1106 display(0x3c, SDA_pin, SCL_pin);

String w5500LinkStatus()
{
  if (Ethernet.linkStatus() == Unknown)
  {
    return "Unknown";
  }
  else if (Ethernet.linkStatus() == LinkON)
  {
    return "Linked";
  }
  else if (Ethernet.linkStatus() == LinkOFF)
  {
    return "Not connected";
  }
  return "Unknown";
}


String DisplayAddress(IPAddress address)
{
  return String(address[0]) + "." +
         String(address[1]) + "." +
         String(address[2]) + "." +
         String(address[3]);
}

void displayStatus()
{
  display.clear();
  display.drawString(0, 0, "ZUMBOARD v" + String(VERSION) + "." + String(RELEASE));
  display.drawString(0, 10, "IP : " + DisplayAddress(Ethernet.localIP()));
  display.drawString(0, 20, "SUB: " + DisplayAddress(Ethernet.subnetMask()));
  display.drawString(0, 30, "GW : " + DisplayAddress(Ethernet.gatewayIP()));
  display.drawString(0, 40, "LAN : " + w5500LinkStatus());
  display.display();
}

void setup() {
  // put your setup code here, to run once:

  pinMode(XCODE_LED, OUTPUT); // initialize the XCODE LED

  pinMode(STAT_LED, OUTPUT); // initialize the STAT LED
  digitalWrite(STAT_LED,1); // Turn on the STAT LED

  Serial.begin(9600); // debug information to serial

  // EThernet 
  pinMode(ETHERNET_SELECT, OUTPUT);
  digitalWrite(ETHERNET_SELECT, LOW); // Enable Ehernet card
  Ethernet.init(ETHERNET_SELECT); // Init the W5500

  Ethernet.begin(mac); // DHCP 
  // Ethernet.begin(mac, ip, dns, gateway, subnet); // Uncomment for static IP

  // Show IP information to your serial port  
  Serial.println (F("DHCP configuration done:"));
	Serial.print (F("- IP: "));
	Serial.println (Ethernet.localIP());
	Serial.print (F("- Netmask: "));
	Serial.println (Ethernet.subnetMask());
	Serial.print (F("- Default Gateway: "));
	Serial.println (Ethernet.gatewayIP());

  display.init(); // Init the OLED
  displayStatus(); // Show Ethernet status on Display
}

void loop() {
  // put your main code here, to run repeatedly:
 
}