#include <NewPing.h>
#define PIN_TRIG 12
#define PIN_ECHO 11
#define MAX_DISTANCE 200 

NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE);
void setup() {
  Serial.begin(9600);
}
void loop() {
  delay(100);
  unsigned int distance = sonar.ping_cm();
  Serial.print(distance);
  Serial.println("см");
}
