// Identifiers for the different rooms. As of now:
// Livingroom, Bedroom, Kids room, Entry room.

const char *roomIds[] = {"RTBeanLvR", "RTBeanBdR", "RTBeanKdR", "RTBeanEtR"};

bool connected;

void setup() {
  // We don't have anything that needs to be set dynamically
  // so we don't need ConfigSave. This also means we don't use
  // any of the limited number of NVRAM writes.
  Bean.enableConfigSave(false);

  // Sleep until the RPi connects to poll for the current
  // data.
  Bean.enableWakeOnConnect(true);


  // Bean Id, represents the room this bean is meant to be stored in.
  Bean.setBeanName(roomIds[0]);
  Serial.begin();
}

void loop() {
  connected = Bean.getConnectionState();

  if (connected) {
    // Indicate that the bean is being talked to. Led Green.
    Bean.setLed(0, 255, 0);

    // Wait a bit for the RPi to start listening to RX
    delay(500);

    // Get sensor data.
    uint8_t batteryLevel = Bean.getBatteryLevel();
    uint8_t temperature = Bean.getTemperature();
    uint8_t moisture = 0;

    // Write the data to the serial port.
    Serial.print("T");
    Serial.print(temperature);
    Serial.println(";B");
    Serial.print(batteryLevel);
    Serial.println(";M\n");
    Serial.print(batteryLevel);

    // A loop() pass can be quite fast, and e don't want to send
    // read and send the sensor data multiple times. Therefore,
    // after sending the data, we wait for 10 seconds.
    delay(10000);
  } else {
    // Turn off the LED.
    Bean.setLed(0, 0, 0);

    // Sleep for the maximum amount of time to preserve energy.
    // Bean will wake up upon connect.
    Bean.sleep(0xFFFFFFFF);
  }
}
