int GETPIX(int x, int y) {
  return (y & 1) ? (y * 16 + 15 - x) : (y * 16 + x);
}

void draw_frame() {
  FastLED.show();
  switch (cfg.effect) {
    case 0:
      if (millis() / 1000UL % 2 == 1) {
        leds[0] = CRGB::Green;
      }
      else {
        leds[0] = CRGB::Blue;
      }
      break;
    case 1:
      for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
          leds[GETPIX(x, y)] = CHSV((y * 2 + millis() / 20) & 255, 255, 255);
        }
      }
      break;
    case 2:
      for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
          int value = inoise8(x * 20, y * 20, millis() / 7);
          leds[GETPIX(x, y)] = ColorFromPalette(palettes[cfg.palette], value, value, LINEARBLEND);
        }
      }
      break;
    case 3:
      renderFire(1);
      break;
    case 4:
      fadeToBlackBy(leds, 256, 5);
      if (random8(0, 40) == 0) {
        renderLighting();
      }
      break;
    case 5:
      for (int y = 0; y < 16; y++) {
        int sine = sin8((y * 2 + millis() / 20) & 255);
        for (int x = 0; x < 16; x++) {
          leds[GETPIX(x, y)] = ColorFromPalette(palettes[cfg.palette], sine, sine, LINEARBLEND);
        }
      }
      break;
    case 6:

      break;
    case 7:
      fill_solid(leds, 256, CRGB::White);
      break;
    case 8:
      fadeToBlackBy(leds, 256, 1);
      if (random8(0, 20) == 0) {
        leds[random8(0, 255)] = CHSV(random8(0, 255), 255, 255);
      }
      break;
    case 9:
      
      break;
  }
}

void renderFire(byte scale) {
  static uint8_t deltaValue;
  static uint8_t deltaHue;
  static uint8_t step;
  static uint8_t shiftHue[50];
  static float trackingObjectPosX[100];
  static float trackingObjectPosY[100];
  static uint16_t ff_x, ff_y, ff_z;
  static bool loading = true;


  if (loading) {
    loading = false;
    deltaValue = map(scale, 0, 255, 8, 168);
    deltaHue = map(deltaValue, 8U, 168U, 8U, 84U);
    step = map(255U - deltaValue, 87U, 247U, 4U, 32U);
    for (uint8_t j = 0; j < 16; j++) {
      shiftHue[j] = (16 - 1 - j) * 255 / (16 - 1);
    }

    for (uint8_t i = 0; i < 16 / 8; i++) {
      trackingObjectPosY[i] = random8(16);
      trackingObjectPosX[i] = random8(16);
    }
  }
  for (uint8_t i = 0; i < 16; i++) {
    for (uint8_t j = 0; j < 16; j++) {
      leds[GETPIX(i, 16 - 1U - j)] = ColorFromPalette(palettes[cfg.palette], qsub8(inoise8(i * deltaValue, (j + ff_y + random8(2)) * deltaHue, ff_z), shiftHue[j]), 255U);
    }
  }
  for (uint8_t i = 0; i < 16 / 8; i++) {
    if (trackingObjectPosY[i] > 3U) {
      leds[GETPIX(trackingObjectPosX[i], trackingObjectPosY[i])] = leds[GETPIX(trackingObjectPosX[i], 3U)];
      leds[GETPIX(trackingObjectPosX[i], trackingObjectPosY[i])].fadeToBlackBy(trackingObjectPosY[i] * 2U);
    }
    trackingObjectPosY[i]++;
    if (trackingObjectPosY[i] >= 16) {
      trackingObjectPosY[i] = random8(4U);
      trackingObjectPosX[i] = random8(16);
    }
    if (!random8(step))
      trackingObjectPosX[i] = (16 + (uint8_t)trackingObjectPosX[i] + 1U - random8(3U)) % 16;
  }
  ff_y++;
  if (ff_y & 0x01) ff_z++;
}

void renderLighting() {
  int x = random8(0, 15);
  for (int y = 15; y >= 0; y--) {
    leds[GETPIX(x, y)] = CRGB::White;
    if (random8(0, 5) == 0) x += 1;
    else if (random8(0, 5) == 0) x -= 1;
    if (x > 15) x -= 16;
    else if (x < 0) x += 16;
  }
}
