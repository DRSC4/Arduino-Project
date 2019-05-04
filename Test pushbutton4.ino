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
        case 3:
            DisplaySetYear();
            //MenuSurveil();
            break;
        case 4:
            DisplaySetMonth();
            //MenuSurveil();
            break;
        case 5:
            DisplaySetDay();
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
    }
}





void DisplayDateTime()
{
    lcd.clear();
// We show the current date and time
      lcd.setCursor(0,0);
    char date[10];
    sprintf(date, "%02i/%02i/%04i",day,month,year);
    lcd.print(date);

    lcd.setCursor(6,1);
    char time[17];
    sprintf(time, "  %02i:%02i:%02i", hours, minutes, seconds);
    lcd.print(time);
}
  
void DisplaySetHour()
{
// Setting the hour
  lcd.clear();
  digitalWrite(ref, LOW);
  digitalWrite(P2,HIGH);
  igitalWrite(P3,HIGH);

  if(digitalRead(P2)==LOW)
  {
    if (hours==23)
    {
      hours=0;
    }
    else
    {
      hours=hours+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if (hours==0)
    {
      hours=23;
    }
    else
    {
      hours=hours-1;
    }
  }
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
  digitalWrite(ref, LOW);
  digitalWrite(P2,HIGH);
  igitalWrite(P3,HIGH);

  if(digitalRead(P2)==LOW)
  {
    if (minutes==59)
    {
      minutes=0;
    }
    else
    {
      minutes=minutes+1;
    }
    seconds=0;
  }
   if(digitalRead(P3)==LOW)
  {
    if (minutes==0)
    {
      minutes=59;
    }
    else
    {
      minutes=minutes-1;
    }
    seconds=0;
  }
  lcd.setCursor(0,0);
  lcd.print("Set minute:");
  lcd.setCursor(0,1);
  lcd.print(minutes,DEC);
  delay(200);
}

void DisplaySetYear()
{
// setting the year
  lcd.clear();
  digitalWrite(ref, LOW);
  digitalWrite(P2,HIGH);
  igitalWrite(P3,HIGH);

  if(digitalRead(P2)==LOW)
  {    
    year=year+1;
  }
   if(digitalRead(P3)==LOW)
  {
    year=year-1;
  }
  lcd.setCursor(0,0);
  lcd.print("Set Year:");
  lcd.setCursor(0,1);
  lcd.print(year,DEC);
  delay(200);
}

void DisplaySetMonth()
{
// Setting the month
  lcd.clear();
  digitalWrite(ref, LOW);
  digitalWrite(P2,HIGH);
  igitalWrite(P3,HIGH);

  if(digitalRead(P2)==LOW)
  {
    if (month==12)
    {
      month=1;
    }
    else
    {
      month=month+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if (month==1)
    {
      month=12;
    }
    else
    {
      month=month-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Month:");
  lcd.setCursor(0,1);
  lcd.print(month,DEC);
  delay(200);
}

void DisplaySetDay()
{
// Setting the day
  lcd.clear();
  digitalWrite(ref, LOW);
  digitalWrite(P2,HIGH);
  igitalWrite(P3,HIGH);

  if(digitalRead(P2)==LOW)
  {
    if (day==31)
    {
      day=1;
    }
    else
    {
      day=day+1;
    }
  }
   if(digitalRead(P3)==LOW)
  {
    if (day==1)
    {
      day=31;
    }
    else
    {
      day=day-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Day:");
  lcd.setCursor(0,1);
  lcd.print(day,DEC);
  delay(200);
}

void StoreAgg()
{
// Variable saving
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SAVING IN");
  lcd.setCursor(0,1);
  lcd.print("PROGRESS");
 // RTC.adjust(DateTime(yearupg,monthupg,dayupg,hourupg,minupg,0));
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

        if (hours == 24) {
            hours = 0;

            day++;
        }
    }
    }
}
