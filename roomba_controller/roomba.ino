void roombaStartClean()
{
  Serial.write(128);
  delay(50);
  Serial.write(131);
  delay(50);
  Serial.write(135);
  client.publish("roomba/status", "{\"message\":\"roomba cleaning\"}");
  Serial.println("Roomba cleaning");
  display.println("Roomba cleaning");
  display.display();
}

void roombaGoToDock()
{
  Serial.write(128);
  delay(50);
  Serial.write(131);
  delay(50);
  Serial.write(143);
  client.publish("roomba/status", "{\"message\":\"roomba going to dock\"}");
  Serial.println("Roomba going to dock");
  display.println("Roomba going to dock");
  display.display();
}

void roombaPowerOff()
{
  Serial.write(128);
  delay(50);
  Serial.write(131);
  delay(50);
  Serial.write(133);
  client.publish("roomba/status", "{\"message\":\"roomba powered off\"}");
  Serial.println("Roomba powered off");
  display.println("Roomba powered off");
  display.display();
}

void wakeup()
{
  pinMode(BRC_PIN, OUTPUT);

  digitalWrite(BRC_PIN, HIGH);
  delay(100);
  digitalWrite(BRC_PIN, LOW);
  delay(500);
  digitalWrite(BRC_PIN, HIGH);
  delay(2000);
  pinMode(BRC_PIN, INPUT);
  delay(200);
  Serial.write(128); // Start
}

void roombaWakeUpOnDock()
{
  wakeup();
  client.publish("roomba/status", "{\"message\":\"roomba wake up brc\"}");
  Serial.println("Roomba wake up brc");
  display.println("Roomba wake up brc");
  display.display();
}

void roombaWakeUpOffDock()
{
  Serial.write(131); // Safe mode
  delay(300);
  Serial.write(130); // Passive mode
  client.publish("roomba/status", "{\"message\":\"roomba wake up off dock\"}");
  Serial.println("Roomba wake up off dock");
  display.println("Roomba wake up off dock");
  display.display();
}
