#include <SoftwareSerial.h>
#include <FastLED.h>

const char UNDERGLOW_OFF = '0';
const char UNDERGLOW_ON = '1';
const char AMBIENT_OFF = '2';
const char AMBIENT_ON = '3';
const char STROBE_OFF = '4';
const char STROBE_ON = '5';

#define UNDERGLOW_DATA_PIN 5
#define NUM_LEDS 150
#define AMBIENT_LED_PIN 6
#define STROBE_LED_PIN 7

#define MAX_INT_VALUE 65536

SoftwareSerial ble(3, 4);
CRGB leds[NUM_LEDS];

uint8_t underglow_status = 0;
uint8_t animation = 0;
uint16_t animate_speed = 100;
uint16_t frame = 0;

uint8_t mediumBright = 42;
uint8_t highBright = 242;

void setup() {
  Serial.begin(9600);
  ble.begin(9600);

  pinMode(UNDERGLOW_DATA_PIN, OUTPUT);
  pinMode(AMBIENT_LED_PIN, OUTPUT);
  digitalWrite(AMBIENT_LED_PIN, HIGH);
  pinMode(STROBE_LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, UNDERGLOW_DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
}

void loop() {
  char instruction;

  if (ble.available()) {
    instruction = ble.read();
    Serial.print("DATA RECEIVED: ");
    Serial.println(instruction);
  }
  if (Serial.available())
    ble.write(Serial.read());

  processInstruction(instruction);
}

void processInstruction(char c) {
  switch (c) {
    case UNDERGLOW_OFF:
      Serial.println("0 - Turn off the underglow");
      underglow_status = 0;
      turnOffAll();
      digitalWrite(UNDERGLOW_DATA_PIN, LOW);
      break;
    case UNDERGLOW_ON:
      Serial.println("1 - Turning ON the underglow");
      underglow_status = 1;
      digitalWrite(UNDERGLOW_DATA_PIN, HIGH);
      showAnimation('b');
      break;
    case AMBIENT_OFF:
      Serial.println("2 - Turn off the ambient light");
      digitalWrite(AMBIENT_LED_PIN, HIGH);
      break;
    case AMBIENT_ON:
      Serial.println("3 - Turning ON the ambient light");
      digitalWrite(AMBIENT_LED_PIN, LOW);
      break;
    case STROBE_OFF:
      Serial.println("4 - Turn off the strobe");
      digitalWrite(STROBE_LED_PIN, LOW);
      break;
    case STROBE_ON:
      Serial.println("5 - Turning ON the strobe");
      digitalWrite(STROBE_LED_PIN, HIGH);
      break;
    default:
      showAnimation(c);
      break;
  }
}

void showAnimation(char animation) {
  if (underglow_status==1){
    switch (animation) {
      case 'a':
        Serial.println("a - Demo");
        rainbow(frame, 169);
        FastLED.show();
        frame += animate_speed;
        break;
      case 'b':
        Serial.println("b - Static medium");
        turnMedium();
        break;
      case 'c':
        Serial.println("c - Static high");
        turnHigh();
        break;
      case 'd':
        Serial.println("d - Breathing");
        breath();
        break;
      case 'e':
        Serial.println("e - Chase");
        chase();
        break;
      case 'f':
        Serial.println("f - Random fill");
        randomFill();
        break;
      case 'g':
        Serial.println("g - Strobe");
        strobe();
        break;
      case 'h':
        Serial.println("h - Alternate strobe");
        alternateStrobe();
        break;
      case 'i':
        Serial.println("i - Chase over");
        chaseOver();
        break;
      case 'j':
        Serial.println("j - Chase over 2");
        chaseOver2();
        break;
      case 'k':
        Serial.println("k - Random spark over");
        randomSparkOver();
        break;
      case 'l':
        Serial.println("l - Random spark");
        randomSpark();
        break;
      case 'm':
        Serial.println("m - Random spark 2");
        randomSpark2();
        FastLED.show();
        frame += animate_speed;
        break;
    }
  }
}

void rainbow(uint16_t animationFrame, uint8_t fade) {
  uint16_t rand = random16();

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(fade);
  }
  uint8_t hue = animationFrame / 255;
  leds[rand % NUM_LEDS].setHSV(hue, 255, 255);
}

void turnMedium() {
  FastLED.clear();
  //lightAllMedium();
  lightAll(42);
  delay(500);
  FastLED.show();
}

void turnHigh() {
  FastLED.clear();
  lightAllHigh();
  FastLED.show();
  delay(500);
}

void breath() {
  FastLED.clear();
  for (int i = 0; i < highBright; i++) {
    lightAll(i);
    FastLED.show();
    delay(10);
  }
  for (uint8_t i = highBright; i > 0; i--) {
    lightAll(i);
    FastLED.show();
    delay(10);
  }
  delay(1000);
}

void chase() {
  FastLED.clear();
  uint8_t barSize = 5;
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    for (uint8_t j = 0; j < barSize; j++) {
      uint8_t pos = i - j;
      if (pos >= 0 && pos < NUM_LEDS)
        lightMedium(pos);
    }
    uint8_t pos = i - barSize;
    if (pos >= 0 && pos < NUM_LEDS)
      turnOff(pos);
    delay(42);
  }
}

void randomFill() {
  randomSeed(millis());
  uint8_t all[NUM_LEDS];
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    all[i] = i;
  }
  FastLED.clear();
  uint8_t total = NUM_LEDS - 1;
  for (uint8_t i = total; i > 0; i--) {
    uint8_t x = random(i);
    uint8_t picked = all[x];
    for (uint8_t j = x; x < i; x++) {
      all[x] = all[x + 1];
    }
    lightMedium(picked);
    FastLED.show();
    delay(42);
  }
}

void strobe() {
  FastLED.clear();
  lightAllMedium();
  delay(50);
  turnOffAll();
  delay(100);
  lightAllMedium();
  delay(50);
  turnOffAll();
  delay(100);
  lightAllHigh();
  delay(50);
  turnOffAll();
  delay(3000);
}

void alternateStrobe() {
  FastLED.clear();
  turnOnHalf();
  delay(100);
  turnOffAll();
  delay(100);
  turnOnHalf();
  delay(100);
  turnOffAll();
  delay(100);
  turnOnHalf();
  delay(100);
  turnOffAll();
  delay(100);

  turnOnHalfInverted();
  delay(100);
  turnOffAll();
  delay(100);
  turnOnHalfInverted();
  delay(100);
  turnOffAll();
  delay(100);
  turnOnHalfInverted();
  delay(100);
  turnOffAll();
  delay(100);
}

void chaseOver() {
  FastLED.clear();
  lightAllMedium();
  overUp();
}

void chaseOver2() {
  FastLED.clear();
  lightAllMedium();
  overUp();
  overDown();
}

void randomSparkOver() {
  lightAllMedium();
  turnOnRandom();
}

void randomSpark() {
  turnOffAll();
  turnOnRandom();
}

void randomSpark2() {
  rainbowSpark(frame, 252);
}

void turnOnHalf() {
  uint8_t count = 0;
  uint8_t qty = 5;
  boolean turnOn = true;
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if (turnOn) {
      lightMediumPrep(i);
      count++;
    } else {
      count--;
    }
    if (count == qty)
      turnOn = false;
    else if (count == 0)
      turnOn = true;
  }
  FastLED.show();
}

void turnOnHalfInverted() {
  uint8_t count = 5;
  uint8_t qty = 5;
  boolean turnOn = false;
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if (turnOn) {
      lightMediumPrep(i);
      count++;
    } else {
      count--;
    }
    if (count == qty)
      turnOn = false;
    else if (count == 0)
      turnOn = true;
  }
  FastLED.show();
}

void overUp() {
  for (uint8_t i = 0; i < 149; i++) {
    lightHigh(i);
    delay(50);
    lightMedium(i);
  }
}

void overDown() {
  for (uint8_t i = 149; i > 1; i--) {
    lightHigh(i);
    delay(50);
    lightMedium(i);
  }
}

void turnOnRandom() {
  uint8_t r = random(NUM_LEDS);
  lightHigh(r);
  FastLED.show();
  delay(100);
  turnOff(r);
}

void rainbowSpark(uint16_t animationFrame, uint8_t fade) {
  sparkRandom(animationFrame, fade, animationFrame / 255);
  FastLED.show();
  delay(20);
}

void sparkRandom(uint16_t animationFrame, uint8_t fade, uint8_t hue) {
  uint8_t stripLength = NUM_LEDS;
  uint16_t rand = random16();
  for (uint8_t i = 0; i < stripLength; i++) {
    leds[i].nscale8(fade);
  }

  if (rand < (MAX_INT_VALUE / (256 - (constrain(animate_speed, 1, 256))))) {
    leds[rand % stripLength].setHSV(hue, 255, 255);
  }
}

void lightAll(uint8_t grad) {
  fill_solid(leds, NUM_LEDS, CRGB(0, grad, 0));
  FastLED.show();
}

void lightAllMedium() {
  fill_solid(leds, NUM_LEDS, CRGB(0, mediumBright, 0));
  FastLED.show();
}

void lightAllHigh() {
  fill_solid(leds, NUM_LEDS, CRGB(0, highBright, 0));
  FastLED.show();
}

void turnOffAll() {
  FastLED.clear();
  FastLED.show();
}

void lightMedium(uint8_t pos) {
  Serial.print("Prendiendo bajo ");
  Serial.println(pos);
  leds[pos] = CRGB(0, mediumBright, 0);
  FastLED.show();
}

void lightMediumPrep(uint8_t pos) {
  leds[pos] = CRGB(0, mediumBright, 0);
}

void lightHigh(uint8_t pos) {
  Serial.print("Prendiendo alto ");
  Serial.println(pos);
  leds[pos] = CRGB(0, highBright, 0);
  FastLED.show();
}

void turnOff(uint8_t pos) {
  Serial.print("Apagando ");
  Serial.println(pos);
  leds[pos] = CRGB(0, 0, 0);
  FastLED.show();
}
