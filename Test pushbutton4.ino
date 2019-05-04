/*
:Project:Clock_Set_Date_Time
:Author: Tiziano Bianchettin
:Date: 13/01/2017
:Revision: 1
:License: Public Domain
thanks to:
  http://arduinoenonsolo.blogspot.it/2012/12/orologio-con-arduino-e-il-ds1307.html
  http://www.mauroalfieri.it/
  http://www.danielealberti.it/
  http://www.maffucci.it/
  My electronics laboratory professor "Perito Carli"  
*/
//************libraries**************//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//************************************//
LiquidCrystal_I2C lcd(0x27, 16, 2); // Display  I2C 16 x 2

//************Button*****************//
int P1 = 7; // Button SET MENU'
int P2 = 6; // Button +
int P3 = 5; // Button -
int ref = 8;

//************Variables**************//
int hours;
int minutes;
int seconds;
int year = 2020;
int month;
int day;
int menu =0;

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(P1,INPUT);
  pinMode(P2,INPUT);
  pinMode(P3,INPUT);
  pinMode(ref,OUTPUT);

  Serial.begin(9600);
  Wire.begin();
    
  int menu=0;
}
 
void loop()
{
    MenuSurveil();

    switch (menu) 
    {
        case 0:
        //do something when var equals 0
            incTime();
            DisplayDateTime();
            //MenuSurveil();
            break;
        case 1:
            DisplaySetHour();
            //MenuSurveil();
            break;
        case 2:
            DisplaySetMinute();
            //MenuSurveil();
            break;

        default:
            menu=0;
        break;
    }
}

void MenuSurveil()
{
    digitalWrite(ref, LOW);
    digitalWrite(P1,HIGH);
    Serial.print(ref);
    Serial.print(P1);

    if(digitalRead(P1)== LOW)
    {
        delay(100);
        if (digitalRead(P1)== LOW)
        {
            Serial.print(P1);
            menu++;
        }
        digitalWrite(ref, HIGH);
    }
}

void buttonSurveil(int Var,int param,int maxi,int mini,int math)
{
    digitalWrite(ref, LOW);
    digitalWrite(var,HIGH);

    if(digitalRead(Var)== LOW)
    {
        if (math == "+")
        {
            if (param == maxi)
            {
                param = mini;
            }
            else
            {
                param = param + 1;
            }
        }
        else if (math == "-")
        {
            if (param == mini)
            {
                param = maxi;
            }
            else
            {
                param = param - 1;
            }
        }
        digitalWrite(ref, HIGH);
        digitalWrite(Var, HIGH);
    }
}

void DisplayDateTime()
{
    lcd.clear();
    lcd.setCursor(6,1);
    char time[17];
    sprintf(time, "  %02i:%02i:%02i", hours, minutes, seconds);
    lcd.print(time);
}
  
void DisplaySetHour()
{
// Setting the hour
    lcd.clear();
  
    buttonSurveil(P2, hours, 23, 0, "+");
    buttonSurveil(P3, hours, 23, 0, "-");

    lcd.setCursor(0,0);
    lcd.print("Set hours:");
    lcd.setCursor(0,1);
    lcd.print(hours,DEC);
    delay(200);
}

void DisplaySetMinute()
{
// Setting the minutes
    lcd.clear();
  
    buttonSurveil(P2, minutes, 59, 0, "+");
    buttonSurveil(P3, minutes, 59, 0, "-");

    lcd.setCursor(0,0);
    lcd.print("Set minute:");
    lcd.setCursor(0,1);
    lcd.print(minutes,DEC);
    delay(200);
}

void incTime() {
    
    delay(1000);
    seconds++;

    if (seconds >= 60) {
        
        seconds = seconds - 60;
        minutes++;

        if (minutes == 60) {
        
        minutes = 0;
        hours++;

        if (hours == 24) 
        {
            hours = 0;
            day++;
        }
    }
    }
}