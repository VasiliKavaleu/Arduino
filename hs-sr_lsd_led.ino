#include <NewPing.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define led_gr 7
#define led_red 4
#define PIN_TRIG 12
#define PIN_ECHO 9
#define MAX_DISTANCE 200  

LiquidCrystal_I2C lcd(0x3F,16,2); 
NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE);
int sound = 10;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(led_gr, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(sound, OUTPUT);
}
void loop() {
  digitalWrite(led_gr, LOW);
  delay(300);
  digitalWrite(led_gr, HIGH);
  unsigned int distance = sonar.ping_cm();
  if (distance < 25 ) {
    digitalWrite(led_red, HIGH);
    analogWrite(sound, 250);
  } else {
    digitalWrite(led_red, LOW);
    analogWrite(sound, 0);
  }
  Serial.print(distance);
  Serial.println("см");
  lcd.clear();
  lcd.print(distance); 
}
