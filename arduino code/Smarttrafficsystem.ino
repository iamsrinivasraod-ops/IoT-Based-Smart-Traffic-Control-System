#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>

/* ------------ LCD ------------ */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ------------ PINS ------------ */
#define IR1 2
#define IR2 3
#define BUZZER 5
#define RED_LED 9
#define GREEN_LED 10
#define IR_RECEIVE_PIN 6
#define LDR A0

/* ------------ CONSTANTS ------------ */
const float DISTANCE_M = 0.25;
const unsigned long MAX_TIME_MS = 8000;
const int LDR_THRESHOLD = 500;
const float SPEED_LIMIT = 10.0;

/* ------------ VARIABLES ------------ */
unsigned long tStart = 0;
bool timingActive = false;

int lightState = 0;   // 0=RED,1=GREEN,2=YELLOW
int objectCount = 0;

bool lastIR1 = HIGH;
bool lastIR2 = HIGH;

float lastSpeed = 0;

bool violationActive = false;
bool overspeedWarning = false;

/* ------------ SETUP ------------ */
void setup() {

  pinMode(IR1, INPUT_PULLUP);
  pinMode(IR2, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  lcd.setCursor(0,0);
  lcd.print("Traffic System");
  lcd.setCursor(0,1);
  lcd.print("Starting...");
  delay(2000);

  updateLight();
}

/* ------------ LOOP ------------ */
void loop() {

  int ldrValue = analogRead(LDR);
  bool isNight = (ldrValue > LDR_THRESHOLD);

  /* ---------- IR REMOTE CONTROL ---------- */
  if (IrReceiver.decode()) {

    unsigned long value = IrReceiver.decodedIRData.decodedRawData;

    Serial.print("HEX: ");
    Serial.println(value, HEX);

    if (value == 0xF30CFF00) lightState = 0;
    else if (value == 0xE718FF00) lightState = 1;
    else if (value == 0xA15EFF00) lightState = 2;

    violationActive = false;
    overspeedWarning = false;

    updateLight();

    IrReceiver.resume();
    delay(200);
  }

  bool ir1 = digitalRead(IR1);
  bool ir2 = digitalRead(IR2);

  /* ---------- RED LIGHT VIOLATION ---------- */
  if (lightState == 0 && (ir1 == LOW || ir2 == LOW)) {

    violationActive = true;
    tone(BUZZER, 3000);

  } else {
    noTone(BUZZER);
  }

  /* ---------- IR1 START ---------- */
  if (lastIR1 == HIGH && ir1 == LOW) {
    tStart = millis();
    timingActive = true;
  }

  /* ---------- IR2 STOP ---------- */
  if (lastIR2 == HIGH && ir2 == LOW && timingActive) {

    unsigned long deltaT = millis() - tStart;
    timingActive = false;

    objectCount++;

    Serial.print("Objects: ");
    Serial.println(objectCount);

    if (deltaT > 0 && deltaT < MAX_TIME_MS) {

      lastSpeed = (DISTANCE_M / (deltaT / 1000.0)) * 3.6;

      Serial.print("Speed: ");
      Serial.println(lastSpeed);

      if (lightState == 2 && lastSpeed > SPEED_LIMIT) {

        overspeedWarning = true;

        tone(BUZZER, 2000, 500);
      }
    }
  }

  lastIR1 = ir1;
  lastIR2 = ir2;

  updateDisplay(isNight);
}

/* ------------ UPDATE LIGHT ------------ */
void updateLight() {

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  if (lightState == 0) digitalWrite(RED_LED, HIGH);

  else if (lightState == 1) digitalWrite(GREEN_LED, HIGH);

  else {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
  }
}

/* ------------ DISPLAY LOGIC ------------ */
void updateDisplay(bool nightMode) {

  lcd.clear();

  /* ---------- RED VIOLATION SCREEN ---------- */
  if (violationActive) {

    lcd.setCursor(0,0);
    lcd.print("TRAFFIC");
    lcd.setCursor(0,1);
    lcd.print("VIOLATION !");
    return;
  }

  /* ---------- YELLOW OVERSPEED ---------- */
  if (overspeedWarning) {

    lcd.setCursor(0,0);
    lcd.print("SLOW DOWN !");
    lcd.setCursor(0,1);
    lcd.print("LIMIT 10km/h");
    return;
  }

  /* ---------- NORMAL DISPLAY ---------- */

  lcd.setCursor(0,0);

  if (lightState == 0) lcd.print("RED ");
  else if (lightState == 1) lcd.print("GREEN ");
  else lcd.print("YELLOW ");

  if (nightMode) lcd.print("NIGHT");
  else lcd.print("DAY");

  lcd.setCursor(0,1);
  lcd.print("SPD:");
  lcd.print(lastSpeed,1);
  lcd.print("km/h");
}