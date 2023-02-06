// #include <Servo.h>

// Servo servo;

int watchedPinState = 0;
int fanOn = 0;
unsigned long lastTriggerMillis;
const int debounceMillis = 3000;
const int fanOffMillis = 1500;
const int sensorInputPin = 4;

void setup() {
  pinMode(sensorInputPin, INPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(digitalRead(sensorInputPin));
  watchedPinState = digitalRead(sensorInputPin);
  checkPinState(watchedPinState);
}

void checkPinState(int state) {
  if (watchedPinState == 1 && ((lastTriggerMillis + debounceMillis) < millis()) && !fanOn) {
    lastTriggerMillis = millis();
    digitalWrite(7, HIGH);
    fanOn = 1;
    Serial.println("ON");
  } else if (((lastTriggerMillis + fanOffMillis) < millis()) && fanOn) {
    digitalWrite(7, LOW);
    fanOn = 0;
    Serial.println("OFF");
  }
  if (digitalRead(7) != 1 && digitalRead(7) != 0) {
    Serial.println("error - recover");
  }
}