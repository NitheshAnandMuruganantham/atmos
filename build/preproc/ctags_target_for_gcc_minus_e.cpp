# 1 "c:\\Users\\anand\\Desktop\\final\\sketch.ino"






# 8 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2

PMsensor PM;

# 12 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2
# 13 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2
# 14 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2
# 15 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2
# 16 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2
# 17 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2
# 18 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2
# 19 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2
# 20 "c:\\Users\\anand\\Desktop\\final\\sketch.ino" 2
# 33 "c:\\Users\\anand\\Desktop\\final\\sketch.ino"
char auth[] = "jLc6cHqEYR5QBPinJ2Q0NTUjpSSbWF4L";
char ssid[] = "anand";
char pass[] = "123123123";

DHT dht(18, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

void sendSensor()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Blynk.virtualWrite(15, temperature);
  Blynk.virtualWrite(16, humidity);
  Blynk.virtualWrite(19, ((float)analogRead((33)) * 100 / 4096));
  Blynk.virtualWrite(20, ((float)analogRead((32)) * 100 / 4096));
  Blynk.virtualWrite(21, ((float)analogRead((35)) * 100 / 4096));
  Blynk.virtualWrite(22, ((float)analogRead((34)) * 100 / 4096));
  Blynk.virtualWrite(23, (analogReadMilliVolts(27));
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
  lcd.print("DEVICE ID " + String("atmos"));
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
  Serial.println("MQ 2 " + String((float)analogRead((35)) * 100 / 4096));
  Serial.println("MQ 135 " + String((float)analogRead((33)) * 100 / 4096));
  Serial.println("MQ 7 " + String((float)analogRead((32)) * 100 / 4096));
  Serial.println("MQ 5 " + String((float)analogRead((34)) * 100 / 4096));
  Serial.println("========================");
  Blynk.run();
  timer.run();
  delay(1000);
}
