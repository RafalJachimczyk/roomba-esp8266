#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <Wire.h>

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

#define OLED_RESET 0 //GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 25
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16

#define BRC_PIN 14

uint32_t freeMem;

// ---------- MQTT SETUP -----------//
WiFiClient espClient;
PubSubClient client(espClient);
// ---------- MQTT SETUP -----------//


void callback(char *topic, byte *payload, unsigned int length)
{
  prepareOledDisplay();
  
  String command;
  for (int i = 0; i < length; i++)
  {
    command += (char)payload[i];
  }

  if (command == "START")
  {
    roombaStartClean();
  }
  else if (command == "DOCK")
  {
    roombaGoToDock();
  }
  else if (command == "OFF")
  {
    roombaPowerOff();
  }
  else if (command == "WAKE")
  {
    roombaWakeUpOffDock();
  }
  else if (command == "WAKE_BRC")
  {
    roombaWakeUpOnDock();
  }

}

void setup()
{
  // High-impedence on the BRC_PIN
  pinMode(BRC_PIN, INPUT);
  Serial.begin(115200);
  prepareOledDisplay();

  setupWiFi();
  setupOTA();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop()
{
  ArduinoOTA.handle();

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}
