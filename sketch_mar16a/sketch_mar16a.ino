#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6VHN-J8zC"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "TNH7tlZyOziFvhucTxtCf_AP0BFYiSXx"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define SS_PIN 8
#define RST_PIN 0
#define SERVO_PIN 15
MFRC522 mfrc522(SS_PIN,RST_PIN); // Create MFRC522 instance.
Servo servo;
LiquidCrystal_I2C lcd(0x27,16,2);

char auth[]= "TNH7tlZyOziFvhucTxtCf_AP0BFYiSXx";
char ssid[]= "POCO X3 NFC";
char pass[]= "123456789";

void setup()
{
  Serial.begin(9600);
  SPI.begin();     
  lcd.init();
  lcd.backlight();
  Serial.println();
  servo.attach(15);
  Blynk.begin(auth,ssid,pass,"Blynk.cloud",80);

  WiFi.begin("POCO X3 NFC", "123456789");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  servo.write(0);
}

void loop() 
{
  Blynk.run();
  
}
BLYNK_WRITE(V1)
{
  servo.write(param.asInt());
}
BLYNK_WRITE(V2)
{
  servo.write(0);
}
BLYNK_WRITE(V3)
{
  servo.write(90);
}


