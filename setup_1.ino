//include servo library
#include <Servo.h> 
int servoPin = 2;

// Create a servo object 
Servo Servo1; 
int servoPos = 0;
int changePos = 20;
int currentPos = 0;


//declare button pins
const int buttonPinL = 4;
const int buttonPinR = 8;
int buttonStateL = 0;
int buttonStateR = 0;


#include <dht.h>
#define dht_apin A2 // Analog Pin sensor is connected to
dht DHT;


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);


//Variables
int paValue = 0;          // Store value from photoresistor (0-1023)
const int pResistor = A0; // Photoresistor at Arduino analog pin A0


void setup() {
  // put your setup code here, to run once:
  pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)
  Servo1.attach(servoPin); 
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("temp (C):");
  lcd.setCursor(0,1);
  lcd.print("read:");
  lcd.setCursor(9,1);
  lcd.print("pos:");
 Serial.begin(9600);
 delay(1000);//Wait before accessing Sensor
}

void loop() {
  // put your main code here, to run repeatedly:
  //photoresistor
  paValue = analogRead(pResistor);

  //temperature
  DHT.read11(dht_apin);

  //servo & button
  buttonStateL = digitalRead(buttonPinL);
  buttonStateR = digitalRead(buttonPinR);

  if (buttonStateR == HIGH) {
    // turn servo to left:
    Servo1.write(servoPos+changePos);
    servoPos += changePos;
  } else {
    Servo1.write(servoPos);
  }

  if (buttonStateL == HIGH) {
    // turn servo to left:
    Servo1.write(servoPos-changePos);
    servoPos -= changePos;
  } else {
    Servo1.write(servoPos);
  }

  //lcd
  lcd.setCursor(9,0);
  lcd.print(DHT.temperature);
  lcd.setCursor(5,1);
  lcd.print(paValue);
  lcd.setCursor(13,1);
  lcd.print(servoPos);
  delay(1000); 
}
