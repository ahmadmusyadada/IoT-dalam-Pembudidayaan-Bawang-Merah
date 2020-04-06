#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define sensorLDR A0

const int trigPin = 2; //D4
const int echoPin = 0; //D3

LiquidCrystal_I2C lcd(0x27, 16, 2);
int pinLED = 12;
int sensorSuhu = 13;
int LEDBuild = 16;
int nilaiSensor;
int jarak;
long durasi;
dht DHT;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.home();
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
  pinMode(sensorSuhu, OUTPUT);
  pinMode(LEDBuild, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("LED Otomatis NODEMCU");
  delay(3000);
}

void loop() {
  DHT.read11(sensorSuhu);
  nilaiSensor = analogRead(sensorLDR);
  Serial.print("Nilai Sensor: ");
  Serial.println(nilaiSensor);
  Serial.print("Suhu = ");
  Serial.print(DHT.temperature);
  Serial.println(" C ");
  delay(500); 
  if(nilaiSensor > 500) {
    digitalWrite(pinLED, LOW);
    delay(1000);
  } else if (nilaiSensor < 500){
    digitalWrite(pinLED, HIGH);
    delay(1000);
  }
//
//  if(jarak == 1) {
//    digitalWrite(led1, LOW);
//    digitalWrite(led2, HIGH);
//    digitalWrite(led3, HIGH);
//  }
//  if(jarak == 2) {
//    digitalWrite(led1, HIGH);
//    digitalWrite(led2, LOW);
//    digitalWrite(led3, HIGH);
//  }
//  if(jarak == 3) {
//    digitalWrite(led1, HIGH);
//    digitalWrite(led2, HIGH);
//    digitalWrite(led3, LOW);
//  }
//  if(jarak > 3) {
//    delay(1000);
//    digitalWrite(led1, HIGH);
//    digitalWrite(led2, HIGH);
//    digitalWrite(led3, HIGH);
//    delay(1000);
//    digitalWrite(led1, LOW);
//    digitalWrite(led2, LOW);
//    digitalWrite(led3, LOW);
//  }
  deteksiJarak();
}

void deteksiJarak() {
  int suhu = DHT.temperature;
  lcd.clear();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durasi = pulseIn(echoPin, HIGH);
  jarak = durasi*0.034/2;
  lcd.setCursor(0,0);
  lcd.print("S:" + String(suhu) + "C. J:" + String(jarak) + "cm");
  if (suhu >= 28){
    scrollText(1, "Siram Tanaman", 250, 16);
  }
  if (jarak <= 10){
    scrollText(1, "Matikan Diesel", 250, 16);
  }
  delay(200);
}

void scrollText(int row, String message, int delayTime, int lcdColumns)
{
//  for (int i = 0; i < lcdColumns; i++)
//  {
//    message = " " + message;
//  }
//  message = message + " ";
//  for (int pos = 0; pos < message.length(); pos++)
//  {
    lcd.setCursor(0, row);
    lcd.print(message);
//    delay(delayTime);
//  }
}
