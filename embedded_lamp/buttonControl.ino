void button_task() {
  if (millis() - btn_tmr >= 100) {
    btn_tmr = millis();
    bool current_btn_state = digitalRead(BUTTON_PIN);
    if (!btn_state && current_btn_state) {
      last_btn_pressed = millis();
    }
    if (btn_state && !current_btn_state) {
      if (millis() - last_btn_pressed < 2000) {
        if (cfg.state == LAMP_ON) {
          cfg.state = LAMP_OFF;
          FastLED.clear();
          FastLED.show();
        }
        else {
          cfg.state = LAMP_ON;
        }
        publishState();
      }
      if (millis() - last_btn_pressed >= 2000) {
        brightness_dir = !brightness_dir;
      }
      cfg_changed = true;
    }
    if (btn_state && millis() - last_btn_pressed >= 2000) {
      cfg.brightness += (brightness_dir) ? -5 : 5;
      cfg.brightness = constrain(cfg.brightness, 0, 255);
      FastLED.setBrightness(cfg.brightness);
      cfg_changed = true;
      publishState();
    }
    btn_state = digitalRead(BUTTON_PIN);
  }
}
