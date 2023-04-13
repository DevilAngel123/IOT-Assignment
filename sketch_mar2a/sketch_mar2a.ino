 
#include<SPI.h>
#include<MFRC522.h>
#include<Servo.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#define SS_PIN 8
#define RST_PIN 0
#define SERVO_PIN 3
MFRC522 mfrc522(SS_PIN,RST_PIN); // Create MFRC522 instance.
Servo servo;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
 Serial.begin(9600); // Initiate a serial communication
  SPI.begin();     // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
 Serial.println("Approximate your card to the reader...");
 Serial.println();
 servo.attach(SERVO_PIN);
 servo.write(0);
 lcd.init();              
 lcd.clear();      
 lcd.backlight();
 lcd.setCursor(2,0);
 lcd.print("Hello there.");
 lcd.setCursor(0,1);
 lcd.print("Please scan card!");
}
void loop()
{
 // Look for new cards
 if(!mfrc522.PICC_IsNewCardPresent())
 {
   return;
 }
 // Select one of the cards
 if(!mfrc522.PICC_ReadCardSerial())
 {
   return;
 }
 //Show UID on serial monitor
 Serial.print("UID tag :");
 String content="";
 byte letter;
 for(byte i=0;i<mfrc522.uid.size;i++)
 {
     Serial.print(mfrc522.uid.uidByte[i]<0x10?" 0":" ");
     Serial.print(mfrc522.uid.uidByte[i],HEX);
     content.concat(String(mfrc522.uid.uidByte[i]<0x10?" 0":" "));
     content.concat(String(mfrc522.uid.uidByte[i],HEX));
 }
 Serial.println();
 Serial.print("Message : ");
  content.toUpperCase();
 if(content.substring(1)=="83 20 87 1D")//change here the UID of the card/cards that you want to give access
 {
   Serial.println("Authorized access");
   Serial.println();
   servo.write(90);
   delay(3000);
   servo.write(0);
   delay(1000);
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.print("Authorized access"); 
   delay(1000);
   setup();
 }
 else {
   Serial.println(" Access denied");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Authorized denied");
    delay(2000);
    setup();
 }
}