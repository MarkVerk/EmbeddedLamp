#include "0_data.h"

void setup() {
  deviceId = WiFi.macAddress();
  Serial.begin(115200);
  Serial.println();
  Serial.println(deviceId);
  EEPROM.begin(EEPROM_SIZE);
  if (EEPROM.read(0) == 1) {
    Serial.println("Loading cfg from EEPROM");
    EEPROM.get(4, cfg);
  }
  else {
    EEPROM.write(0, 1);
    EEPROM.commit();
  }
  pinMode(BUTTON_PIN, INPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_POWER_AMP);
  FastLED.setBrightness(cfg.brightness);
  wifiManager.autoConnect(AP_NAME, AP_PASS);
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt.setCallback(mqtt_callback);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  mqtt_task();
  //button_task();
  handleSerial();
  if (cfg.state == LAMP_ON) {
    draw_frame();
  }
  else {
    if (millis() - clear_tmr >= 5000) {
      clear_tmr = millis();
      FastLED.clear();
      FastLED.show();
    }
  }
  saveCfgCheck();
}
