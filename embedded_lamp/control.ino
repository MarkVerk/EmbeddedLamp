void handleSerial() {
  if (Serial.available() > 0) {
    char input[64];
    int received = Serial.readBytesUntil('\n', input, 63);
    input[received] = '\0';
    char* cmd_end = strchr(input, ' ');
    if (cmd_end != nullptr) {
      *cmd_end = '\0';
    }
    if (strcmp(input, "on") == 0) {
      cfg.state = LAMP_ON;
      Serial.println("Device is now ON");
    }
    else if (strcmp(input, "off") == 0) {
      cfg.state = LAMP_OFF;
      FastLED.showColor(CRGB::Black);
      Serial.println("Device is now OFF");
    }
    else if (strcmp(input, "effect") == 0) {
      cfg.effect = atoi(cmd_end + 1);
      FastLED.clear();
      FastLED.show();
      Serial.print("Effect set to ");
      Serial.println(cfg.effect);
    }
    else if (strcmp(input, "brightness") == 0) {
      cfg.brightness = atoi(cmd_end + 1);
      FastLED.setBrightness(cfg.brightness);
      Serial.print("Brightness set to ");
      Serial.println(FastLED.getBrightness());
    }
    else if (strcmp(input, "palette") == 0) {
      cfg.palette = atoi(cmd_end + 1);
      Serial.print("Palette set to ");
      Serial.println(cfg.palette);
    }
    cfg_changed = true;
  }
}
