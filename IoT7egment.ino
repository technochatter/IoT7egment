 //LICENSE
 /*
	This code uses Arduino Library IoT7egment.Latest version at https://github.com/technochatter/IoT7egment
    Copyright (C) 2016  Animesh Chatterjee(technochatter@yahoo.in)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/
#include "se7en.h"
#include <ESP8266WiFi.h>
#include "ntpCalculate.h"
#include <Ticker.h>

Ticker sec;
Ticker disp;
const int latchpin = 12;
const int clockpin = 4;
const int datapin = 14;

se7en dig(datapin,clockpin,latchpin);
String str="";

int counter=0;
char ssid[] = "SSID";  //  your network SSID (name)
char pass[] = "PIN-password";       // your network password


  //dig.scrollDisplay(str,500, true, &counter);
/*
void printTime()
{
  String hh, mm,ss;
  if(DateTimeInstance.hour<=9)
  hh="0"+String(DateTimeInstance.hour);
  else
  hh=String(DateTimeInstance.hour);
  if(DateTimeInstance.minute<=9)
  mm="0"+String(DateTimeInstance.minute);
  else
   mm=String(DateTimeInstance.minute);
  if(DateTimeInstance.second<=9)
  ss="0"+String(DateTimeInstance.second);
  else
  ss=String(DateTimeInstance.second);
  str=hh+"."+mm+"."+ss;
  dig.print(str);
  Serial.print("TIME:");
  Serial.print(DateTimeInstance.hour);
  Serial.print(":");
  Serial.print(DateTimeInstance.minute);
  Serial.print(":");
  Serial.println(DateTimeInstance.second);
  Serial.print("YEAR:");
  Serial.println(DateTimeInstance.year);
  Serial.print("MONTH:");
  Serial.println(DateTimeInstance.month);
  Serial.print("DATE:");
  Serial.println(DateTimeInstance.day);
  Serial.print("DAY:");
  Serial.println(DateTimeInstance.dayName);
}
*/
void printTime(timeFormat tf)
{
  static boolean colon=false;
  colon=!colon;
  String hh, mm, ss, AmPm;
  byte hrs=DateTimeInstance.hour;
  
  switch(tf)
  {
    case HOURS :

        if(hrs<=9)
            hh="0"+String(hrs);
        else
            hh=String(DateTimeInstance.hour);
          
         if(DateTimeInstance.minute<=9)
            mm="0"+String(DateTimeInstance.minute);
         else
            mm=String(DateTimeInstance.minute);
            
        if(DateTimeInstance.second<=9)
           ss="0"+String(DateTimeInstance.second);
        else
           ss=String(DateTimeInstance.second);

        str=hh+"."+mm+"."+ss;

        break;
    
    case AM_PM :
  //time formatting
        if(hrs<12)
        {
          AmPm="A";
          if(hrs==0)
            hrs=hrs+12;
        }
        else if(hrs>12)
        {
            hrs=hrs-12;
            AmPm="P";
          }
        else if(hrs==12)
           AmPm="P";
     //string formatting      
        if(hrs<=9)
            hh="0"+String(hrs);
        else
            hh=String(hrs);
          
         if(DateTimeInstance.minute<=9)
            mm="0"+String(DateTimeInstance.minute);
         else
            mm=String(DateTimeInstance.minute);

  
          if(colon)
              str=hh+":"+mm+AmPm;
          else
              str=hh+" "+mm+AmPm;

         break;

      }
      
  dig.print(str);

}

void timeClock()//executes every second
{
  printTime(AM_PM);
      if(DateTimeInstance.second<59)
        DateTimeInstance.second++;
      else{
        DateTimeInstance.second=0;
        if(DateTimeInstance.minute<59)
          DateTimeInstance.minute++;
        else{
          DateTimeInstance.minute=0;
          if(DateTimeInstance.hour<59)
            DateTimeInstance.hour++;
      }
   }
 }
void call()
{
  dig.begin();
}
 
void setup() 
{
  //Serial.begin(9600);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
        disp.attach_ms(1,call);
  // We start by connecting to a WiFi network
/*str="Connecting to..";
str=str+String(ssid);
scrolling.attach_ms(1,scroll);*/
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    y_delay(500);
    dig.print("-");
  }
  dig.print("Connected!!");
y_delay(1000);
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  dig.print(WiFi.localIP().toString());
y_delay(1000);
      
   dig.print("Sync");
      y_delay(1000);
  
  dig.print(" in ");
   y_delay(500);
   
  dig.print("Progrs");
   y_delay(1000);
   
  while(!(timeSync("asia.pool.ntp.org", 55)))
  {
    dig.print(" . . . . .");
    yield();
  }

  dig.print("Done!!");
  y_delay(500);
  
      sec.attach(1,timeClock);

 // prevmil=millis();
}

void manualSetTime()
{
  Serial.print("Set Hour:");
  while(Serial.available()<1) return;
  DateTimeInstance.hour=Serial.parseInt();
  Serial.print("Set Minutes:");
  while(Serial.available()<1) return;
  DateTimeInstance.minute=Serial.parseInt();
}


void loop()
{
//Displaying to SEDMENTS
//dig.begin();  //for scrolling   
//delay(1);
//dig.begin(RIGHT); 
//dig.scrollDisplay(str, 550, true);
//dig.displayWord(str, 1000, false);
//dig.updateDigit(2, 'A', true);

  //manualSetTime();
   // wait ten seconds before asking for the time again
  //delay(300000);

}
/* 
void loop1()
{
  currentmil=millis();
  if((currentmil-prevmil)>1000)
  {
    prevmil=currentmil;
    timeClock();
  }
      yield();
}
*/


/*
 * connected!
 * failed to connect
 * HotSpot SSID
 * 1.Network_Error
 * Time update in progress
 * Syncing with time server pool
 * Next update at 15:25 hrs or 3:25pm
 * New Client Connected?
 * Connect to hotspot?
 * IP Address-192.168.0.10
 * Time is: 
 * Date is:
 * Railway Time
 * Weather
 * Sending temperature Data to ThingSpeak
 * checking weather-
 * cloudy
 * sunny
 * rainfall
 */
