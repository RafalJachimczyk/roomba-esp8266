void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password))
    {
      //    if (client.connect("ESP8266Client")) {
      Serial.println("MQTT connected");
      // Once connected, publish an announcement...
      client.publish("roomba/status", "{\"message\":\"roomba connected\"}");
      client.subscribe("roomba/command");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in a second");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
}

void setupWiFi()
{
    WiFi.mode(WIFI_STA); // added 300716
    WiFi.begin(ssid, password);
    Serial.println();
    Serial.print("Connecting");
    display.print("Connecting");
    display.display();

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        display.print(".");
        display.display();
    }

    Serial.println();
    display.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    display.println("Connected\nIP address: ");
    display.println(WiFi.localIP());
    display.display();
    delay(2000);
    display.clearDisplay();
}

void setupOTA()
{
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
      type = "sketch";
    }
    else
    { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
}
