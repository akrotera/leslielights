#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
include <FastLED.h>

#define UNDERGLOW_SERVICE_UUID      "8a32ae00-62dc-4672-aaf0-48a47099af60"
#define UNDERGLOW_CHARC_STATUS_UUID "8a32ae01-62dc-4672-aaf0-48a47099af60"
#define UNDERGLOW_CHARC_MODE_UUID   "8a32ae02-62dc-4672-aaf0-48a47099af60"
#define AMBIENT_SERVICE_UUID        "8a32ae10-62dc-4672-aaf0-48a47099af60"
#define AMBIENT_CHARC_STATUS_UUID   "8a32ae11-62dc-4672-aaf0-48a47099af60"

#define UNDERGLOW_DATA_PIN 22
#define NUM_LEDS 150
#define AMBIENT_LED_PIN 23

CRGB leds[NUM_LEDS];

uint8_t underglow_status = 0;
uint8_t animation = 0;
uint16_t animate_speed = 100;
uint16_t frame = 0;

uint8_t mediumBright = 42;
uint8_t highBright = 142;

class UnderglowCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic)
    {
      std::string uuid = pCharacteristic->getUUID().toString();
      std::string value = pCharacteristic->getValue();

      if (uuid == UNDERGLOW_CHARC_STATUS_UUID) {
        if (value == "1") {
          Serial.println("Turning ON the underglow");
          digitalWrite(UNDERGLOW_DATA_PIN, HIGH);
          underglow_status = 1;
        }

        if (value == "0") {
          Serial.println("Turning OFF the underglow");
          FastLED.clear();
          digitalWrite(UNDERGLOW_DATA_PIN, LOW);
          underglow_status = 0;
        }
      }

      if (uuid == UNDERGLOW_CHARC_MODE_UUID) {
        //Posible pasar a enum?
        if (value == "0") {#include <BLEDevice.h>#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <FastLED.h>

#define UNDERGLOW_SERVICE_UUID      "8a32ae00-62dc-4672-aaf0-48a47099af60"
#define UNDERGLOW_CHARC_STATUS_UUID "8a32ae01-62dc-4672-aaf0-48a47099af60"
#define UNDERGLOW_CHARC_MODE_UUID   "8a32ae02-62dc-4672-aaf0-48a47099af60"
#define AMBIENT_SERVICE_UUID        "8a32ae10-62dc-4672-aaf0-48a47099af60"
#define AMBIENT_CHARC_STATUS_UUID   "8a32ae11-62dc-4672-aaf0-48a47099af60"

#define UNDERGLOW_DATA_PIN 22
#define NUM_LEDS 150
#define AMBIENT_LED_PIN 23

#define MAX_INT_VALUE 65536

CRGB leds[NUM_LEDS];

uint8_t underglow_status = 0;
uint8_t animation = 0;
uint16_t animate_speed = 100;
uint16_t frame = 0;

uint8_t mediumBright = 42;
uint8_t highBright = 142;

class UnderglowCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic)
    {
      std::string uuid = pCharacteristic->getUUID().toString();
      std::string value = pCharacteristic->getValue();

      if (uuid == UNDERGLOW_CHARC_STATUS_UUID) {
        if (value == "1") {
          Serial.println("Turning ON the underglow");
          digitalWrite(UNDERGLOW_DATA_PIN, HIGH);
          underglow_status = 1;
        }

        if (value == "0") {
          Serial.println("Turning OFF the underglow");
          FastLED.clear();
          digitalWrite(UNDERGLOW_DATA_PIN, LOW);
          underglow_status = 0;
        }
      }

      if (uuid == UNDERGLOW_CHARC_MODE_UUID) {
        //Possible chabge to enum?
        if (value == "0") {
          Serial.println("Underglow anim default");
          animation = 0;
        }
        if (value == "1") {
          Serial.println("Underglow anim 1");
          animation = 1;
        }
        if (value == "2") {
          Serial.println("Underglow anim 2");
          animation = 2;
        }
        if (value == "3") {
          Serial.println("Underglow anim 3");
          animation = 3;
        }
        if (value == "4") {
          Serial.println("Underglow anim 4");
          animation = 4;
        }
        if (value == "5") {
          Serial.println("Underglow anim 5");
          animation = 5;
        }
        if (value == "6") {
          Serial.println("Underglow anim 6");
          animation = 6;
        }
        if (value == "7") {
          Serial.println("Underglow anim 7");
          animation = 7;
        }
        if (value == "8") {
          Serial.println("Underglow anim 8");
          animation = 8;
        }
        if (value == "9") {
          Serial.println("Underglow anim 9");
          animation = 9;
        }
        if (value == "10") {
          Serial.println("Underglow anim 10");
          animation = 10;
        }
        if (value == "11") {
          Serial.println("Underglow anim 11");
          animation = 11;
        }
        if (value == "12") {
          Serial.println("Underglow anim 12");
          animation = 12;
        }
      }
    }
};

class AmbientCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value == "1") {
        Serial.println("Turning ON the ambient light");
        digitalWrite(AMBIENT_LED_PIN, HIGH);
      }

      if (value == "0") {
        Serial.println("Turning OFF the ambient light");
        digitalWrite(AMBIENT_LED_PIN, LOW);
      }
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(UNDERGLOW_DATA_PIN, OUTPUT);
  pinMode(AMBIENT_LED_PIN, OUTPUT);

  BLEDevice::init("LeslieLights");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pServiceUnderglow = pServer->createService(UNDERGLOW_SERVICE_UUID);

  BLECharacteristic *pCharcUnderStatus = pServiceUnderglow->createCharacteristic(
      UNDERGLOW_CHARC_STATUS_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE);

  BLECharacteristic *pCharcUnderMode = pServiceUnderglow->createCharacteristic(
                                         UNDERGLOW_CHARC_MODE_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE);

  pCharcUnderStatus->setCallbacks(new UnderglowCallbacks());
  pCharcUnderMode->setCallbacks(new UnderglowCallbacks());

  pCharcUnderStatus->setValue("0");
  pCharcUnderMode->setValue("0");

  pServiceUnderglow->start();

  BLEService *pServiceAmbient = pServer->createService(AMBIENT_SERVICE_UUID);

  BLECharacteristic *pCharcAmbientStatus = pServiceAmbient->createCharacteristic(
        AMBIENT_CHARC_STATUS_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE);

  pCharcAmbientStatus->setCallbacks(new AmbientCallbacks());
  pCharcAmbientStatus->setValue("0");

  pServiceAmbient->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  BLEDevice::startAdvertising();

  FastLED.addLeds<WS2812B, UNDERGLOW_DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
}

void loop() {
  if (underglow_status == 1) {
    switch (animation) {
      case 0:
        Serial.println("0 - Demo");
        rainbow(frame, 169);
        FastLED.show();
        frame += animate_speed;
        break;
      case 1:
        Serial.println("1 - Static medium");
        turnMedium();
        break;
      case 2:
        Serial.println("2 - Static high");
        turnHigh();
        break;
      case 3:
        Serial.println("3 - Breathing");
        breath();
        break;
      case 4:
        Serial.println("4 - Chase");
        chase();
        break;
      case 5:
        Serial.println("5 - Random fill");
        randomFill();
        break;
      case 6:
        Serial.println("6 - Strobe");
        strobe();
        break;
      case 7:
        Serial.println("7 - Alternate strobe");
        alternateStrobe();
        break;
      case 8:
        Serial.println("8 - Chase over");
        chaseOver();
        break;
      case 9:
        Serial.println("9 - Chase over 2");
        chaseOver2();
        break;
      case 10:
        Serial.println("10 - Random spark over");
        randomSparkOver();
        break;
      case 11:
        Serial.println("11 - Random spark");
        randomSpark();
        break;
      case 12:
        Serial.println("12 - Random spark 2");
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
  lightAllMedium();
}

void turnHigh() {
  lightAllHigh();
}

void breath() {
  for (int i = 0; i < highBright; i++) {
    lightAll(i);
    FastLED.show();
    delay(25);
  }
  for (int i = highBright; i > 0; i--) {
    lightAll(i);
    FastLED.show();
    delay(25);
  }
}

void chase() {
  FastLED.clear();
  int raySize = 5;
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int j = 0; j < raySize; j++) {
      int pos = i - j;
      if (pos >= 0)
        lightMedium(pos);
      delay(33);
    }
    int minPos = i - raySize;
    for (minPos; minPos >= 0; minPos--) {
      turnOff(minPos);
    }
  }
}

void randomFill() {
  randomSeed(millis());
  int all[NUM_LEDS];
  for (int i = 0; i < NUM_LEDS; i++) {
    all[i] = i;
  }
  FastLED.clear();
  for (int i = NUM_LEDS; i > -1; i--) {
    int x = random(i);
    int picked = all[x];
    for (int j = x; x < i; x++) {
      all[x] = all[x + 1];
    }
    leds[picked] = CRGB(0, mediumBright, 0);
    FastLED.show();
    delay(300);
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
  turnOnHalfAlternate();
  delay(50);
  turnOffAll();
  delay(100);
  turnOnHalfAlternate();
  delay(50);
  turnOffAll();
  delay(100);
  turnOnHalfAlternate();
  delay(50);
  turnOffAll();
  delay(100);

  turnOnHalfInverted();
  delay(50);
  turnOffAll();
  delay(100);
  turnOnHalfInverted();
  delay(50);
  turnOffAll();
  delay(100);
  turnOnHalfInverted();
  delay(50);
  turnOffAll();
  delay(100);
}

void chaseOver() {
  fill_solid(leds, NUM_LEDS, CRGB(0, mediumBright, 0));
  overUp();
}

void chaseOver2() {
  fill_solid(leds, NUM_LEDS, CRGB(0, mediumBright, 0));
  overUp();
  overDown();
}

void randomSparkOver() {
  fill_solid(leds, NUM_LEDS, CRGB(0, highBright, 0));
  turnOnRandom();
}

void randomSpark() {
  turnOnRandom();
}

void randomSpark2() {
  rainbowSpark(frame, 252);
}

void turnOnHalfAlternate() {
  uint8_t count = 0;
  uint8_t qty = 5;
  boolean turnOn = true;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (turnOn) {
      lightMedium(i);
      count++;
    } else {
      turnOff(i);
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
  for (int i = 0; i < NUM_LEDS; i++) {
    if (turnOn) {
      lightMedium(i);
      count++;
    } else {
      turnOff(i);
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
  for (int i = 0; i < NUM_LEDS; i++) {
    lightHigh(i);
    delay(100);
    lightMedium(i);
  }
}

void overDown() {
  for (int i = NUM_LEDS; i > 0; i--) {
    lightHigh(i);
    delay(100);
    lightMedium(i);
  }
}

void turnOnRandom() {
  int r = random(NUM_LEDS);
  lightHigh(r);
  FastLED.show();
  delay(100);
  turnOff(r);
}

void rainbowSpark(uint16_t animationFrame, uint8_t fade) {
  sparkRandom(animationFrame, fade, animationFrame / 255);
  delay(20);
}

void sparkRandom(uint16_t animationFrame, uint8_t fade, uint8_t hue) {
  uint8_t stripLength = NUM_LEDS;
  uint16_t rand = random16();
  for (int i = 0; i < stripLength; i++) {
    leds[i].nscale8(fade);
  }

  if (rand < (MAX_INT_VALUE / (256 - (constrain(animate_speed, 1, 256))))) {
    leds[rand % stripLength].setHSV(hue, 255, 255);
  }
}

void lightAll(uint8_t grad) {
  fill_solid(leds, NUM_LEDS, CRGB(0, grad, 0));
}

void lightAllMedium() {
  fill_solid(leds, NUM_LEDS, CRGB(0, mediumBright, 0));
}

void lightAllHigh() {
  fill_solid(leds, NUM_LEDS, CRGB(0, highBright, 0));
}

void turnOffAll() {
  FastLED.clear();
  FastLED.show();
}

void lightMedium(uint8_t pos) {
  leds[pos] = CRGB(0, mediumBright, 0);
  FastLED.show();
}

void lightHigh(uint8_t pos) {
  leds[pos] = CRGB(0, highBright, 0);
  FastLED.show();
}

void turnOff(uint8_t pos) {
  leds[pos] = CRGB(0, 0, 0);
  FastLED.show();
}
#include <BLEUtils.h>
#include <BLEServer.h>
#include <FastLED.h>

#define UNDERGLOW_SERVICE_UUID      "8a32ae00-62dc-4672-aaf0-48a47099af60"
#define UNDERGLOW_CHARC_STATUS_UUID "8a32ae01-62dc-4672-aaf0-48a47099af60"
#define UNDERGLOW_CHARC_MODE_UUID   "8a32ae02-62dc-4672-aaf0-48a47099af60"
#define AMBIENT_SERVICE_UUID        "8a32ae10-62dc-4672-aaf0-48a47099af60"
#define AMBIENT_CHARC_STATUS_UUID   "8a32ae11-62dc-4672-aaf0-48a47099af60"

#define UNDERGLOW_DATA_PIN 22
#define NUM_LEDS 150
#define AMBIENT_LED_PIN 23

CRGB leds[NUM_LEDS];

uint8_t underglow_status = 0;
uint8_t animation = 0;
uint16_t animate_speed = 100;
uint16_t frame = 0;

uint8_t mediumBright = 42;
uint8_t highBright = 142;

class UnderglowCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic)
    {
      std::string uuid = pCharacteristic->getUUID().toString();
      std::string value = pCharacteristic->getValue();

      if (uuid == UNDERGLOW_CHARC_STATUS_UUID) {
        if (value == "1") {
          Serial.println("Turning ON the underglow");
          digitalWrite(UNDERGLOW_DATA_PIN, HIGH);
          underglow_status = 1;
        }

        if (value == "0") {
          Serial.println("Turning OFF the underglow");
          FastLED.clear();
          digitalWrite(UNDERGLOW_DATA_PIN, LOW);
          underglow_status = 0;
        }
      }

      if (uuid == UNDERGLOW_CHARC_MODE_UUID) {
        //Possible chabge to enum?
        if (value == "0") {
          Serial.println("Underglow anim default");
          animation = 0;
        }
        if (value == "1") {
          Serial.println("Underglow anim 1");
          animation = 1;
        }
        if (value == "2") {
          Serial.println("Underglow anim 2");
          animation = 2;
        }
        if (value == "3") {
          Serial.println("Underglow anim 3");
          animation = 3;
        }
        if (value == "4") {
          Serial.println("Underglow anim 4");
          animation = 4;
        }
        if (value == "5") {
          Serial.println("Underglow anim 5");
          animation = 5;
        }
        if (value == "6") {
          Serial.println("Underglow anim 6");
          animation = 6;
        }
        if (value == "7") {
          Serial.println("Underglow anim 7");
          animation = 7;
        }
        if (value == "8") {
          Serial.println("Underglow anim 8");
          animation = 8;
        }
        if (value == "9") {
          Serial.println("Underglow anim 9");
          animation = 9;
        }
        if (value == "10") {
          Serial.println("Underglow anim 10");
          animation = 10;
        }
        if (value == "11") {
          Serial.println("Underglow anim 11");
          animation = 11;
        }
      }
    }
};

class AmbientCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value == "1") {
        Serial.println("Turning ON the ambient light");
        digitalWrite(AMBIENT_LED_PIN, HIGH);
      }

      if (value == "0") {
        Serial.println("Turning OFF the ambient light");
        digitalWrite(AMBIENT_LED_PIN, LOW);
      }
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(UNDERGLOW_DATA_PIN, OUTPUT);
  pinMode(AMBIENT_LED_PIN, OUTPUT);

  BLEDevice::init("LeslieLights");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pServiceUnderglow = pServer->createService(UNDERGLOW_SERVICE_UUID);

  BLECharacteristic *pCharcUnderStatus = pServiceUnderglow->createCharacteristic(
      UNDERGLOW_CHARC_STATUS_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE);

  BLECharacteristic *pCharcUnderMode = pServiceUnderglow->createCharacteristic(
                                         UNDERGLOW_CHARC_MODE_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE);

  pCharcUnderStatus->setCallbacks(new UnderglowCallbacks());
  pCharcUnderMode->setCallbacks(new UnderglowCallbacks());

  pCharcUnderStatus->setValue("0");
  pCharcUnderMode->setValue("0");

  pServiceUnderglow->start();

  BLEService *pServiceAmbient = pServer->createService(AMBIENT_SERVICE_UUID);

  BLECharacteristic *pCharcAmbientStatus = pServiceAmbient->createCharacteristic(
        AMBIENT_CHARC_STATUS_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE);

  pCharcAmbientStatus->setCallbacks(new AmbientCallbacks());
  pCharcAmbientStatus->setValue("0");

  pServiceAmbient->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  BLEDevice::startAdvertising();

  FastLED.addLeds<WS2812B, UNDERGLOW_DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
}

void loop() {
  if (underglow_status == 1) {
    switch (animation) {
      case 0:
        Serial.println("0 - Demo");
        rainbow(frame, 169);
        FastLED.show();
        frame += animateSpeed;
        break;
      case 1:
        Serial.println("1 - Static medium");
        turnMedium();
        break;
      case 2:
        Serial.println("2 - Static high");
        turnHigh();
        break;
      case 3:
        Serial.println("3 - Breathing");
        breath();
        break;
      case 4:
        Serial.println("4 - Chase");
        chase();
        break;
      case 5:
        Serial.println("5 - Random fill");
        randomFill();
        break;
      case 6:
        Serial.println("6 - Strobe");
        strobe();
        break;
      case 7:
        Serial.println("7 - Alternate strobe");
        alternateStrobe();
        break;
      case 8:
        Serial.println("8 - Chase over");
        chaseOver();
        break;
      case 9:
        Serial.println("9 - Chase over 2");
        chaseOver2();
        break;
      case 10:
        Serial.println("10 - Random spark over");
        randomSparkOver();
        break;
      case 11:
        Serial.println("11 - Random spark");
        randomSpark();
        break;
      case 12:
        Serial.println("12 - Random spark 2");
        randomSpark2();
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
  lightAllMedium();
}

void turnHigh() {
  lightAllHigh();
}

void breath() {
  for (int i = 0; i < highBrigh; i++) {
    lightAll(i);
    FastLED.show();
    delay(25);
  }
  for (int i = highBrigh; i > 0; i--) {
    lightAll(i);
    FastLED.show();
    delay(25);
  }
}

void chase() {
  FastLED.clear();
  int raySize = 5;
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int j = 0; j < raySize; j++) {
      int pos = i - j;
      if (pos >= 0)
        lightMedium(pos);
      delay(33);
    }
    int minPos = i - raySize;
    for (minPos; minPos >= 0; minPos--) {
      turnOff(minPos);
    }
  }
}

void randomFill() {
  randomSeed(millis());
  int all[NUM_LEDS];
  for (int i = 0; i < NUM_LEDS; i++) {
    all[i] = i;
  }
  FastLED.clear();
  for (int i = NUM_LEDS; i > -1; i--) {
    int x = random(i);
    int picked = all[x];
    for (int j = x; x < i; x++) {
      all[x] = all[x + 1];
    }
    leds[picked] = CRGB(0, mediumBright, 0);
    FastLED.show();
    delay(300);
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
  turnOnHalfAlternate();
  delay(50);
  turnOffAll();
  delay(100);
  turnOnHalfAlternate();
  delay(50);
  turnOffAll();
  delay(100);
  turnOnHalfAlternate();
  delay(50);
  turnOffAll();
  delay(100);

  turnOnHalfInverted();
  delay(50);
  turnOffAll();
  delay(100);
  turnOnHalfInverted();
  delay(50);
  turnOffAll();
  delay(100);
  turnOnHalfInverted();
  delay(50);
  turnOffAll();
  delay(100);
}

void chaseOver() {
  fill_solid(leds, NUM_LEDS, CRGB(0, brilloMedio, 0));
  overUp();
}

void chaseOver2() {
  fill_solid(leds, NUM_LEDS, CRGB(0, brilloMedio, 0));
  overUp();
  overDown();
}

void randomSparkOver() {
  fill_solid(leds, NUM_LEDS, CRGB(0, brilloMedio, 0));
  turnOnRandom();
}

void randomSpark() {
  turnOnRandom();
}

void randomSpark2() {

}

void turnOnHalfAlternate() {
  uint8_t count = 0;
  uint8_t qty = 5;
  boolean turnOn = true;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (turnOn) {
      lightMedium(i);
      count++;
    } else {
      turnOff(i);
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
  for (int i = 0; i < NUM_LEDS; i++) {
    if (turnOn) {
      lightMedium(i);
      count++;
    } else {
      turnOff(i);
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
  for (int i = 0; i < NUM_LEDS; i++) {
    lightHigh(i);
    delay(100);
    lightMedium(i);
  }
}

void overDown() {
  for (int i = NUM_LEDS; i > 0; i--) {
    lightHigh(i);
    delay(100);
    lightMedium(i);
  }
}

void turnOnRandom() {
  int r = random(NUM_LEDS);
  lightHigh(r);
  FastLED.show();
  delay(100);
  turnOff(r);
}





void lightAll(uint8_t grad) {
  fill_solid(leds, NUM_LEDS, CRGB(0, grad, 0));
}

void lightAllMedium() {
  fill_solid(leds, NUM_LEDS, CRGB(0, mediumBright, 0));
}

void lightAllHigh() {
  fill_solid(leds, NUM_LEDS, CRGB(0, highBrigh, 0));
}

void turnOffAll() {
  FastLED.clear();
  FastLED.show();
}

void lightMedium(uint8_t pos) {
  leds[pos] = CRGB(0, mediumBright, 0);
  FastLED.show();
}

void lightHigh(uint8_t pos) {
  leds[pos] = CRGB(0, highBrigh, 0);
  FastLED.show();
}

void turnOff(uint8_t pos) {
  leds[pos] = CRGB(0, 0, 0);
  FastLED.show();
}

}
          Serial.println("Underglow anim default");
          animation = 0;
        }
        if (value == "1") {
          Serial.println("Underglow anim 1");
          animation = 1;
        }
        if (value == "2") {
          Serial.println("Underglow anim 2");
          animation = 2;
        }
        if (value == "3") {
          Serial.println("Underglow anim 3");
          animation = 3;
        }
        if (value == "4") {
          Serial.println("Underglow anim 4");
          animation = 4;
        }
        if (value == "5") {
          Serial.println("Underglow anim 5");
          animation = 5;
        }
        if (value == "6") {
          Serial.println("Underglow anim 6");
          animation = 6;
        }
        if (value == "7") {
          Serial.println("Underglow anim 7");
          animation = 7;
        }
        if (value == "8") {
          Serial.println("Underglow anim 8");
          animation = 8;
        }
        if (value == "9") {
          Serial.println("Underglow anim 9");
          animation = 9;
        }
        if (value == "10") {
          Serial.println("Underglow anim 10");
          animation = 10;
        }
        if (value == "11") {
          Serial.println("Underglow anim 11");
          animation = 11;
        }
      }
    }
};

class AmbientCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value == "1") {
        Serial.println("Turning ON the ambient light");
        digitalWrite(AMBIENT_LED_PIN, HIGH);
      }

      if (value == "0") {
        Serial.println("Turning OFF the ambient light");
        digitalWrite(AMBIENT_LED_PIN, LOW);
      }
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(UNDERGLOW_DATA_PIN, OUTPUT);
  pinMode(AMBIENT_LED_PIN, OUTPUT);

  BLEDevice::init("LeslieLights");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pServiceUnderglow = pServer->createService(UNDERGLOW_SERVICE_UUID);

  BLECharacteristic *pCharcUnderStatus = pServiceUnderglow->createCharacteristic(
      UNDERGLOW_CHARC_STATUS_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE);

  BLECharacteristic *pCharcUnderMode = pServiceUnderglow->createCharacteristic(
                                         UNDERGLOW_CHARC_MODE_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE);

  pCharcUnderStatus->setCallbacks(new UnderglowCallbacks());
  pCharcUnderMode->setCallbacks(new UnderglowCallbacks());

  pCharcUnderStatus->setValue("0");
  pCharcUnderMode->setValue("0");

  pServiceUnderglow->start();

  BLEService *pServiceAmbient = pServer->createService(AMBIENT_SERVICE_UUID);

  BLECharacteristic *pCharcAmbientStatus = pServiceAmbient->createCharacteristic(
        AMBIENT_CHARC_STATUS_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE);

  pCharcAmbientStatus->setCallbacks(new AmbientCallbacks());
  pCharcAmbientStatus->setValue("0");

  pServiceAmbient->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  BLEDevice::startAdvertising();

  FastLED.addLeds<WS2812B, UNDERGLOW_DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
}

void loop() {
  if (underglow_status == 1) {
    switch (animation) {
      case 0:
        Serial.println("0 - Demo");
        rainbow(frame, 169);
        FastLED.show();
        frame += animateSpeed;
        break;
      case 1:
        Serial.println("1 - Static medium");
        turnMedium();
        break;
      case 2:
        Serial.println("2 - Static high");
        turnHigh();
        break;
      case 3:
        Serial.println("3 - Breathing");
        ida();
        break;
      case 4:
        Serial.println("4 - Chase");
        poneMedio();
        break;
      case 5:
        Serial.println("5 - Random fill");
        ida();
        break;
      case 6:
        Serial.println("6 - Strobe");
        poneMedio();
        break;
      case 7:
        Serial.println("7 - Alternate strobe");
        ida();
        break;
      case 8:
        Serial.println("8 - Chase over");
        poneMedio();
        break;
      case 9:
        Serial.println("9 - Chase over 2");
        ida();
        break;
      case 10:
        Serial.println("10 - Random spark over");
        poneMedio();
        break;
      case 11:
        Serial.println("11 - Random spark");
        ida();
        break;
      case 12:
        Serial.println("12 - Random spark 2");
        poneMedio();
        break;
    }
  }
  delay(1000);
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
  lightAllMedium();
}

void turnHigh() {
  lightAllHigh();
}







void lightAllMedium() {
  fill_solid(leds, NUM_LEDS, CRGB(0, mediumBright, 0));
}

void lightAllHigh() {
  fill_solid(leds, NUM_LEDS, CRGB(0, highBrigh, 0));
}

void turnOffAll() {
  FastLED.clear();
  FastLED.show();
}

void lightMedium(uint8_t pos) {
  leds[pos] = CRGB(0, mediumBright, 0);
  FastLED.show();
}

void lightHigh(uint8_t pos) {
  leds[pos] = CRGB(0, highBrigh, 0);
  FastLED.show();
}

void turnOff(uint8_t pos) {
  leds[pos] = CRGB(0, 0, 0);
  FastLED.show();
}

}
