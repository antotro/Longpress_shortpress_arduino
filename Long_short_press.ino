#include <Servo.h>
#define lim A6
#define button 7

Servo myservo;

float angle;
float incr = 0.05;
unsigned long delai = 500;
unsigned long now = 0;
unsigned long debounce_delay = 150;
unsigned long last_press;
bool inputstate;
bool ledstate = 1;
bool button_state = 0;
bool long_press = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  myservo.attach(4);
  angle = myservo.read();
}

void loop() {
  digitalWrite(LED_BUILTIN, button_state);
  if (digitalRead(button) && !inputstate && !long_press) {
    inputstate = true;
    last_press = millis();
  }
  if (!digitalRead(button) && long_press) {
    long_press = false;
    inputstate = false;
  }
  if (millis() - last_press >= debounce_delay && inputstate && digitalRead(button)) {
    long_press = true;
    angle += incr;
    if (angle > 180 || angle < 0) {
      incr *= -1;
    }
    myservo.write(angle);
  } else if (millis() - last_press >= debounce_delay && !long_press && inputstate && !digitalRead(button)) {
    long_press = false;
    inputstate = false;
    button_state = !button_state;
  }
}
