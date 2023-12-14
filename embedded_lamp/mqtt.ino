#include <ArduinoJson.h>

void mqtt_task() {
  if (!mqtt_connected) {
    Serial.print("Connecting to ");
    Serial.println(MQTT_SERVER);
    mqtt.connect(deviceId.c_str(), (deviceId + "/connection").c_str(), 1, true, "DISCONNECTED");
    if (mqtt.connected()) {
      mqtt_connected = true;
      mqtt.subscribe((deviceId + "/control").c_str(), 1);
      mqtt.publish((deviceId + "/connection").c_str(), "CONNECTED", true);
      Serial.println("Connected");
      publishState();
    }
    return;
  }
  if (!mqtt.connected()) {
    mqtt_connected = false;
    Serial.println("Disconnected from mqtt server");
    return;
  }
  mqtt.loop();
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, (deviceId + "/control").c_str()) != 0) return;
  StaticJsonDocument<256> doc;
  deserializeJson(doc, payload, length);
  cfg.state = doc["isOn"];
  cfg.brightness = doc["brightness"];
  cfg.effect = doc["effect"];
  cfg.effect_speed = doc["effect_speed"];
  cfg.palette = doc["palette"];
  FastLED.setBrightness(cfg.brightness);
  publishState();
  FastLED.clear();
  FastLED.show();
  cfg_changed = true;
}

void publishState() {
  StaticJsonDocument<256> doc;
  doc["version"] = 1.0f;
  doc["type"] = "LAMP";
  doc["isOn"] = cfg.state;
  doc["brightness"] = cfg.brightness;
  FastLED.setBrightness(cfg.brightness);
  doc["effect"] = cfg.effect;
  doc["effect_speed"] = cfg.effect_speed;
  doc["palette"] = cfg.palette;
  Serial.println(measureJson(doc));
  char buf[256];
  serializeJson(doc, buf);
  mqtt.publish(deviceId.c_str(), buf, true);
}
