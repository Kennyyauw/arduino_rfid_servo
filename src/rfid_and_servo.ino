#include <MFRC522.h>
#include <Servo.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9
int red = 6;
int green =7;
int blue =8;
int buzzer =2;

MFRC522 mfrc522 (SS_PIN,RST_PIN);
Servo myServo ;

void setup(){
  Serial.begin(9600);
  myServo.attach (3);
  SPI.begin();  
  mfrc522.PCD_Init();
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(buzzer,OUTPUT);
}

void loop (){
  analogWrite(red,0);
  analogWrite(green,0);
  analogWrite(blue,255);
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return ;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return ;
  }
  Serial.println("uid tag:");
  String content = "" ;
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if(content.substring(1) == "4A 8A 95 B3") //設定你自己的uid
  { 
    Serial.println("access ok");
    Serial.println();
    delay(500);
    myServo.write(180);
    analogWrite(red,0);
    analogWrite(green,255);
    analogWrite(blue,0);
    delay(3000);
    myServo.write(0);
  }
   else {
    Serial.println("access denided");
    delay(500);
    analogWrite(red,255);
    analogWrite(green,0);
    analogWrite(blue,0);
    digitalWrite(buzzer,HIGH);
    delay(1000);
    digitalWrite(buzzer,LOW);
    delay(1000);
    
   }
}
