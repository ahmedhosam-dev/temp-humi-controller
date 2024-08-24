#include <LiquidCrystal.h>

// Over and Fan pins
const int OVEN_PIN = 7;
const int FAN_PIN = 4;

// Temprature pins and vars
const int temp_sensor = A0;
float temp, volt;

// Humidty pins and vars
const int humi_sensor = A1;
float humi, volt_ac;

// Time tracking
unsigned long elapsedMillis = 0;
unsigned long elapsedSeconds = 0;
unsigned long s = 0;
unsigned long m = 0;
unsigned long h = 0;
unsigned long d = 0;

// LCD init
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  // Over and Fan pin mode
  pinMode(OVEN_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // lcd x, y
  lcd.begin(32, 2);
}

void loop() {
  // Start time
  elapsedMillis = millis();

  // Read temprature sensor
  volt = analogRead(temp_sensor);
  temp = ((volt * 500) / 1023);

  // Read humidty sensor
  volt_ac = analogRead(humi_sensor);
  humi = ((volt_ac * (5.0 / 1023.0)) / 5.0) * 100;

  // Init messages
  lcd.setCursor(0, 0);
  lcd.print("(TEMP)");
  lcd.print("(HUMI)");
  lcd.print("(H)");
  lcd.print("(F)");

  // Print temp
  lcd.setCursor(0, 1);
  lcd.print(temp);

  // Print Humi
  lcd.setCursor(6, 1);
  lcd.print(humi);

  // Over status postion
  lcd.setCursor(12, 1);
  lcd.print("OFF");

  // Fan status postion
  lcd.setCursor(15, 1);
  lcd.print("OFF");
  
  // Temp is 75.0 (-/+ .5) by trun on/off heater and fan
  if (temp < 37.0) {
    digitalWrite(OVEN_PIN, HIGH);
    lcd.setCursor(12, 1);
    lcd.print("ON "); 
  } else if (temp > 38.0) {
    digitalWrite(FAN_PIN, HIGH);
    lcd.setCursor(15, 1);
    lcd.print("ON ");
  } else {
    digitalWrite(OVEN_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);
    lcd.setCursor(12, 1);
    lcd.print("OFF");
    lcd.setCursor(15, 1);
    lcd.print("OFF");
  }

  // Humi is between 55:65 by turn on/off heater
  if (humi < 55.0) {
    digitalWrite(OVEN_PIN, HIGH);
    lcd.setCursor(12, 1);
    lcd.print("ON "); 
  } else if (humi > 65.0) {
    digitalWrite(OVEN_PIN, LOW);
    lcd.setCursor(12, 1);
    lcd.print("OFF");
  } else {
    digitalWrite(OVEN_PIN, LOW);
    lcd.setCursor(12, 1);
    lcd.print("OFF");
  }

  // info | time
  lcd.setCursor(18, 0);
  lcd.print("|");
  lcd.setCursor(18, 1);
  lcd.print("|");

  lcd.setCursor(19, 0);
  lcd.print("TIME");

  // Calculate seconds, minutes, and hours
  elapsedSeconds = elapsedMillis / 1000;
  s = elapsedSeconds % 60;
  m = (elapsedSeconds / 60) % 60;
  h = (elapsedSeconds / 3600) % 24;
  d = (h == 24) ? d++ : d;

  // Print time
  lcd.setCursor(19, 1);
  lcd.print(d);
  lcd.print(":");
  lcd.print(h);
  lcd.print(":");
  lcd.print(m);
  lcd.print(":");
  lcd.print(s);

  // Clear screan every 1m after 500ms
  if (s == 59){
    delay(500);
    lcd.clear();      
  }
}
