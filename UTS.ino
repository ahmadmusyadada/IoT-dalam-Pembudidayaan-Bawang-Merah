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
    text(1, "Siram Tanaman", 250, 16);
  }
  if (jarak <= 10){
    text(1, "Matikan Diesel", 250, 16);
  }
  delay(200);
}

void text(int row, String message, int delayTime, int lcdColumns){
    lcd.setCursor(0, row);
    lcd.print(message);
}
