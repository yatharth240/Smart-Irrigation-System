//By HomeMade Electronics
//Subscribe to my channel https://www.youtube.com/channel/UC8isJR_71x1wIfw6jB106pg
//for more tutorial videos
//Subscribe, like, share and leave a comment if you need help

#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>


#define echo 9
#define trigger 10
#define tank_pump 4
#define watering_pump 13
#define moisture_sensor A0
long duration;
int distance;
int moisture_value;
int distance_percent;
int moist_percent;


SoftwareSerial SIM900(2, 3);
LiquidCrystal lcd(12,11,8,7,6,5);

void setup () {

lcd.begin(20,4);
SIM900.begin(9600);
Serial.begin(9600);
pinMode(echo,INPUT);
pinMode(moisture_sensor,INPUT);
pinMode(trigger,OUTPUT);
digitalWrite(trigger,LOW);
pinMode(watering_pump,OUTPUT);
pinMode(tank_pump,OUTPUT);
digitalWrite(watering_pump,LOW);
digitalWrite(tank_pump,LOW);

lcd.setCursor(0,1);
lcd.print("  SMART IRRIGATION  ");
lcd.setCursor(0,2);
lcd.print("HOMEMADE ELECTRONICS");
lcd.setCursor(0,3);
lcd.print("  ===============  ");

delay(500);
lcd.clear(); 
}


void loop(){
 //WATER LEVEL SENSOR
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10); 
 digitalWrite(trigger,LOW);
 duration=pulseIn(echo,HIGH);
 distance=duration*0.017; 
 distance_percent=map( distance,0,1023,0,100);
 moisture_value= analogRead(moisture_sensor);
 moist_percent=map(moisture_value,0,1023,0,100);
 condition();

}


void sms(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+233266302607\"");// recipient's mobile number
SIM900.println("IRRIGATION PUMP IS OFF"); // your message that needs to be sent
SIM900.println((char)26); // End AT command with a Upper Case Z, which is ASCII code 26
Serial.println((char)26);
SIM900.println();

}

void sms1(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+233266302607\"");// recipient's mobile number

SIM900.println("WATER TANK PUMP IS OFF"); // your message that needs to be sent
Serial.println("WATER TANK PUMP IS OFF");

SIM900.println((char)26); // End AT command with a Upper Case Z, which is ASCII code 26
Serial.println((char)26);
SIM900.println();

}


void sms2(){
SIM900.print("AT+CMGF=1\r"); 
SIM900.println("AT + CMGS = \"+233266302607\"");// recipient's mobile number

SIM900.println("IRRIGATION PUMP IS ON"); // your message that needs to be sent
Serial.println("IRRIGATION PUMP IS ON");
SIM900.println((char)26); // End AT command with a Upper Case Z, which is ASCII code 26
Serial.println((char)26);
SIM900.println();

}

void sms3(){
SIM900.print("AT+CMGF=1\r"); 
delay(1000);
SIM900.println("AT + CMGS = \"+233266302607\"");// recipient's mobile number

SIM900.println("WATER TANK PUMP IS ON"); // your message that needs to be sent
Serial.println("WATER TANK PUMP IS ON");
SIM900.println((char)26); // End AT command with a Upper Case Z, which is ASCII code 26
Serial.println((char)26);
SIM900.println();

}


void condition(){
if (distance_percent>65 &&moist_percent<85){
LCD_3();
digitalWrite(tank_pump,LOW);
digitalWrite(watering_pump,HIGH);
 sms1();
 sms2();
delay(500);
}
else if (distance_percent<65 &&moist_percent>85)
{
LCD_2();
digitalWrite(tank_pump,HIGH);
digitalWrite(watering_pump,LOW);
sms3();
sms();
delay(500);
}
else if (distance_percent>65 &&moist_percent>85)
{

LCD_4();
digitalWrite(tank_pump,LOW);
digitalWrite(watering_pump,LOW);

sms1();
sms();
delay(500);

}

else if (distance_percent<65 &&moist_percent<85)
{
LCD_1();
digitalWrite(tank_pump,HIGH);
digitalWrite(watering_pump,HIGH);
sms3();
sms2();
delay(500);

}
}



  void LCD_1()
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WATER TANK LEVEL=");
  lcd.print(distance_percent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("SOIL MOISTURE= ");
  lcd.print(moist_percent);
  lcd.print("%");
  lcd.setCursor(0,2);
  lcd.print("IRRIGATION PUMP");
  lcd.print("  ON");
  lcd.setCursor(0,3);
  lcd.print("WATER TANK PUMP");
  lcd.print("  ON");
  }

void LCD_2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WATER TANK LEVEL=");
  lcd.print(distance_percent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("SOIL MOISTURE= ");
  lcd.print(moist_percent);
  lcd.print("%");
  lcd.setCursor(0,2);
  lcd.print("IRRIGATION PUMP");
  lcd.print("  OFF");
  lcd.setCursor(0,3);
  lcd.print("WATER TANK PUMP");
  lcd.print("   ON");
  }
  void LCD_3(){
  lcd.clear();
  lcd.setCursor(0,0);
   lcd.print("WATER TANK LEVEL=");
  lcd.print(distance_percent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("SOIL MOISTURE= ");
  lcd.print(moist_percent);
  lcd.print("%");
   lcd.setCursor(0,2);
  lcd.print("IRRIGATION PUMP");
  lcd.print("  ON");
  lcd.setCursor(0,3);
  lcd.print("WATER TANK PUMP");
  lcd.print("  OFF");
  }

  void LCD_4(){
  lcd.clear();
  lcd.setCursor(0,0);
   lcd.print("WATER TANK LEVEL=");
  lcd.print(distance_percent);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("SOIL MOISTURE= ");
  lcd.print(moist_percent);
  lcd.print("%");
   lcd.setCursor(0,2);
  lcd.print("IRRIGATION PUMP");
  lcd.print("  OFF");
  lcd.setCursor(0,3);
  lcd.print("WATER TANK PUMP");
  lcd.print("  OFF");
  }
