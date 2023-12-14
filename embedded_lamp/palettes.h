DEFINE_GRADIENT_PALETTE(Fire_gp) {
  0, 0, 0, 0,
  128, 255, 0, 0,
  224, 255, 255, 0,
  255, 255, 255, 255
};

DEFINE_GRADIENT_PALETTE(Lighting_gp) {
  0, 0, 0, 0,
  150, 0, 0, 100,
  200, 255, 255, 255,
  255, 255, 255, 255
};

const TProgmemRGBPalette16 WoodFireColors_p PROGMEM = {CRGB::Black, 0x330e00, 0x661c00, 0x992900, 0xcc3700, CRGB::OrangeRed, 0xff5800, 0xff6b00, 0xff7f00, 0xff9200, CRGB::Orange, 0xffaf00, 0xffb900, 0xffc300, 0xffcd00, CRGB::Gold};
const TProgmemRGBPalette16 NormalFire_p PROGMEM = {CRGB::Black, 0x330000, 0x660000, 0x990000, 0xcc0000, CRGB::Red, 0xff0c00, 0xff1800, 0xff2400, 0xff3000, 0xff3c00, 0xff4800, 0xff5400, 0xff6000, 0xff6c00, 0xff7800};
const TProgmemRGBPalette16 LithiumFireColors_p PROGMEM = {CRGB::Black, 0x240707, 0x470e0e, 0x6b1414, 0x8e1b1b, CRGB::FireBrick, 0xc14244, 0xd16166, 0xe08187, 0xf0a0a9, CRGB::Pink, 0xff9ec0, 0xff7bb5, 0xff59a9, 0xff369e, CRGB::DeepPink};
const TProgmemRGBPalette16 SodiumFireColors_p PROGMEM = {CRGB::Black, 0x332100, 0x664200, 0x996300, 0xcc8400, CRGB::Orange, 0xffaf00, 0xffb900, 0xffc300, 0xffcd00, CRGB::Gold, 0xf8cd06, 0xf0c30d, 0xe9b913, 0xe1af1a, CRGB::Goldenrod};
const TProgmemRGBPalette16 CopperFireColors_p PROGMEM = {CRGB::Black, 0x001a00, 0x003300, 0x004d00, 0x006600, CRGB::Green, 0x239909, 0x45b313, 0x68cc1c, 0x8ae626, CRGB::GreenYellow, 0x94f530, 0x7ceb30, 0x63e131, 0x4bd731, CRGB::LimeGreen};
const TProgmemRGBPalette16 AlcoholFireColors_p PROGMEM = {CRGB::Black, 0x000033, 0x000066, 0x000099, 0x0000cc, CRGB::Blue, 0x0026ff, 0x004cff, 0x0073ff, 0x0099ff, CRGB::DeepSkyBlue, 0x1bc2fe, 0x36c5fd, 0x51c8fc, 0x6ccbfb, CRGB::LightSkyBlue};


CRGBPalette16 palettes[] = {
  RainbowColors_p,
  LavaColors_p,
  WoodFireColors_p,
  NormalFire_p,
  LithiumFireColors_p,
  SodiumFireColors_p,
  CopperFireColors_p,
  AlcoholFireColors_p,
  HeatColors_p,
  Lighting_gp
};
