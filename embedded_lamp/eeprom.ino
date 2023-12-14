void saveCfgCheck() {
  if (millis() - eeprom_tmr < 10000) return;
  eeprom_tmr = millis();
  if (!cfg_changed) return;
  EEPROM.put(4, cfg);
  EEPROM.commit();
  cfg_changed = false;
  Serial.println("Saved to EEPROM");
}