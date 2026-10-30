
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin configuration
#define ONE_WIRE_BUS 2
#define LED_PIN 7

// Initialize temperature sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Initialize I2C LCD (address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  sensors.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Temperature");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  sensors.requestTemperatures();

  float temperature = sensors.getTempCByIndex(0);

  lcd.setCursor(0, 0);
  lcd.print("Temperature:");

  if (temperature == DEVICE_DISCONNECTED_C) {
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error    ");
    digitalWrite(LED_PIN, LOW);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print(temperature, 2);
    lcd.print((char)223);
    lcd.print("C       ");

    if (temperature > 25.0) {
      digitalWrite(LED_PIN, HIGH);
    }
    else {
      digitalWrite(LED_PIN, LOW);
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
  }

  delay(1000);
}


