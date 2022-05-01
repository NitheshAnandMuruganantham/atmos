#include <Arduino.h>
#line 1 "c:\\Users\\anand\\Desktop\\atmos\\sketch.ino"

#define BLYNK_TEMPLATE_ID "TMPLzOCxWyV6"
#define BLYNK_DEVICE_NAME "atmos"
#define BLYNK_AUTH_TOKEN "jLc6cHqEYR5QBPinJ2Q0NTUjpSSbWF4L"

#define BLYNK_PRINT Serial
#include <PMsensor.h>

PMsensor PM;

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <GP2YDustSensor.h>
#include <LiquidCrystal_I2C.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define LCD_I2C_ADDRESS 0x27
#define LCD_DISP_COLS 16
#define LCD_DISP_ROWS 2
#define Pin135 (33)
#define Pin7 (32)
#define Pin2 (35)
#define Pin5 (34)

#define BLYNK_PRINT Serial
#define DHTPIN 18
#define DHTTYPE DHT11

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "anand";
char pass[] = "123123123";

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, LCD_DISP_COLS, LCD_DISP_ROWS);
BlynkTimer timer;

void sendSensor()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Blynk.virtualWrite(V15, temperature);
  Blynk.virtualWrite(V16, humidity);
  Blynk.virtualWrite(V19, ((float)analogRead(Pin135) * 100 / 4096));
  Blynk.virtualWrite(V20, ((float)analogRead(Pin7) * 100 / 4096));
  Blynk.virtualWrite(V21, ((float)analogRead(Pin2) * 100 / 4096));
  Blynk.virtualWrite(V22, ((float)analogRead(Pin5) * 100 / 4096));
  Blynk.virtualWrite(V23, analogReadMilliVolts(27));
}

void setup()
{
  Serial.begin(115200);
  dht.begin();
  PM.init(5, 27);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("Team Atmos");
  lcd.setCursor(0, 1);
  lcd.print("KPC MECHATRONICS");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("connecting to cloud");
  lcd.setCursor(0, 1);
  lcd.print("please wait...");
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("DEVICE ID " + String(BLYNK_DEVICE_NAME));
  lcd.setCursor(0, 1);
  lcd.print("READY");

  Serial.println("  done!.");
}

void loop()
{
  float filter_Data = (float)PM.read();
  delay(1000);
  ArduinoOTA.handle();
  Serial.println("========================");
  Serial.println("temperature " + String(dht.readTemperature()));
  Serial.println("humidity " + String(dht.readHumidity()));
  Serial.println("Dust density: " + String(analogReadMilliVolts(27)));
  Serial.println("MQ 2 " + String((float)analogRead(Pin2) * 100 / 4096));
  Serial.println("MQ 135 " + String((float)analogRead(Pin135) * 100 / 4096));
  Serial.println("MQ 7 " + String((float)analogRead(Pin7) * 100 / 4096));
  Serial.println("MQ 5 " + String((float)analogRead(Pin5) * 100 / 4096));
  Serial.println("========================");
  Blynk.run();
  timer.run();
  delay(1000);
}

