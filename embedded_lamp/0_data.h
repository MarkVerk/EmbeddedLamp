#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <FastLED.h>
#include "palettes.h"
#include <EEPROM.h>

#define NUM_LEDS 256
#define MAX_POWER_AMP 2000
#define LED_PIN 2
#define BUTTON_PIN 4
#define LAMP_ON true
#define LAMP_OFF false
#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883
#define AP_NAME "ESP-LAMP"
#define AP_PASS "Technoblade"
#define EEPROM_SIZE 128

WiFiClient client;
PubSubClient mqtt(client);
WiFiManager wifiManager;
bool mqtt_connected;
String deviceId;

struct Config {
  bool state = LAMP_ON;
  int brightness = 50;
  int effect = 0;
  float effect_speed = 1.0f;
  int palette = 0;
};

CRGB leds[256];

bool btn_state;
bool brightness_dir;
unsigned long btn_tmr;
unsigned long last_btn_pressed;
unsigned long eeprom_tmr;
unsigned long clear_tmr;
bool cfg_changed = false;
float effect_param1 = 1.0f;
float effect_param2 = 1.0f;
float effect_param3 = 1.0f;
float effect_param4 = 1.0f;

Config cfg;