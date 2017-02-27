// Identifiers for the different rooms. As of now:
// Livingroom, Bedroom, Kids room, Entry room.
const char *roomIds[] = {"RTB_LR", "RTB_BR", "RTB_KR", "RTB_ER"};

uint8_t room = 0;
uint8_t updateIntervalMinutes = 5;

bool connected;

void setup() {
  // We don't have anything that needs to be set dynamically and saved for later use
  // so we don't need ConfigSave. This also means we don't use any of the limited 
  // number of NVRAM writes.
  Bean.enableConfigSave(false);
}

void loop() {
    // Indicate that the bean is working. Led Green.
    Bean.setLed(0, 255, 0);

    // Get sensor data.
    uint8_t batteryLevel = Bean.getBatteryLevel();
    uint8_t temperature = Bean.getTemperature();
    uint8_t moisture = 0;

    // Construct new name
    String name = roomIds[room];
    name += batteryLevel;
    name += ";";
    name += temperature;
    name += ";";
    name += moisture;

    Bean.setBeanName(name);

    // Turn off LED.
    Bean.setLed(0, 0, 0);

    // Wait for the configured amount of time, then re-run;
    Bean.sleep(updateIntervalMinutes * 60000);
}
