#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 10, 5, 4, 3, 2);
 float dtime=0.0,ftime=500.0,f1time=0.0;
 signed int v=0;
 char text2[50];
 char text3[50];
 int rotation=0;
 int maxspeed;
 const int echoPin = 8; 
 const int pingPin = 9;
 char speed1[20];
 char speed2[20];
 int a=0;
 int b=0;
 float r=0.03;
 void setup()
 {
   Serial.begin(9600);
   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(11,INPUT);
   pinMode(6,INPUT);
   pinMode(13,OUTPUT);
}

int check=0;
int prespeed=0;
 void loop()
 {
      long duration,cm;
    if(check==0)
    {
        Serial.write("Name:Harry||Vehc_No:1423");
        check=1;
    }
    
    if(digitalRead(11)==HIGH)
    {
      rotation++;
    }
    if(millis()-dtime>=1000)
    {
      v = 2 *(3.14) * rotation * r * 5/ 18 ;
      dtime=millis();
      rotation=0;
    }
    while(Serial.available())
        {
            maxspeed=Serial.read();
        }
    sprintf(text2,"Speed limit:%d Current speed:%d ",maxspeed,v);
    sprintf(text3,"Warning speed=%d exceeded limit ",v);
    if(maxspeed>0)
        {
          if(maxspeed>=v)
          {
            lcd.setCursor(0,0);
            lcd.print(text2);
            a=0;
          }
          else
          {
            lcd.setCursor(0,0);
            lcd.print (text3);
          if(millis()-ftime>=500)
          {
            if(a==1)
            {
              sprintf(speed1,"%d",prespeed);
              Serial.write(speed1);
              a=0;
            }
            if(a==0)
            {
              a=1;
              prespeed=v;
            }
            ftime=millis();
            dtime=millis();
          }
          }
        }


    
  if(millis()-f1time>=500)
          {
            digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(pingPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); 
 
  cm = microsecondsToCentimeters(duration);



  if(cm<400 && digitalRead(6)==HIGH)
  {
    buzzer_beep();
  }
            f1time=millis();
      
          }
    

 }
void buzzer_beep()
{
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
}

long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}

 
