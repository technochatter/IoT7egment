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

	

//NOTE: USE y_delay(ms) or millis() function instead of delay(ms)

#include "IoT7egment.h"

Ticker sec;
Ticker disp;

const int latchpin = 12;
const int clockpin = 4;
const int datapin = 14;

IoT7egment Display(datapin,clockpin,latchpin);

char ssid[] = "SSID";  //  your network SSID (name)
char pass[] = "password";       // your network password

int timeout=5000;

//================================================CUSTOM FUNCTIONS================================================

//##################################################################################
//DECODES AND PRINTS THE TIME ACCORDING TO SPECIFIED FORMAT
//#################################################################################
void printTime(timeFormat tf)
    {
      static boolean colon=false;
      colon=!colon;
      String hh, mm, ss, AmPm;
      byte hrs=DateTimeInstance.hour;
      String str="";
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
      
      Display.printlp(str);//prints only if display is free

    }
//##########################################################################################
//EXECUTES EVERY SECOND INCREMENT SECONDS MINUTES AND HOURS ACCORDINGLY IN BETWEEN UPDATES
//##########################################################################################
void timeClock()//executes every second
{
  if(Display.segStatus==FREE)
      printTime(HOURS);//AM_PM
      
      if(DateTimeInstance.second<59)
        DateTimeInstance.second++;
      else{
        DateTimeInstance.second=0;
        if(DateTimeInstance.minute<59)
          DateTimeInstance.minute++;
        else{
          DateTimeInstance.minute=0;
          if(DateTimeInstance.hour<24)
            DateTimeInstance.hour++;
            else
              DateTimeInstance.hour=0;
             }
          }
 }
//##########################################################################
//UPDATES TIME ON FIRST START AND STARTS THE TIMECLOCK
//#########################################################################
    void setupDefault()
    {
        Display.print("Connecting to asia.pool.ntp.org");
        Display.print("Hours");
        y_delay(500);
        Display.print("Sync");
        y_delay(500);
        Display.print(" in ");
        y_delay(500);
        Display.print("Progrs");
        y_delay(500);

        while(!(timeSync("asia.pool.ntp.org", 55)))
        {
            yield();
          }

        Display.print("Done!!");
        y_delay(500);
  
        sec.attach(1,timeClock);
    }
//##########################################################################
//OTHER SUPPORT FUNCTIONS
//#########################################################################
    
void stopTime()
{
   sec.detach();
}
 void printDate()
{
  String str="";
  str=String(DateTimeInstance.dayName)+','+String(DateTimeInstance.day)+'-'+ monthNames[DateTimeInstance.month]+'-'+String(DateTimeInstance.year);
  if(Display.segStatus==FREE)
  Display.print(str);
}

void call()
{
  Display.begin();
}

//==============================================END OF CUSTOM FUCTIONS======================================

 
void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
 
        disp.attach_ms(1,call);//started the Display
        Display.print("Startd");
        y_delay(500);
        
  WiFi.begin(ssid, pass);//Started as Station
  
  Display.print("Connecting to HOTSPOT");
  
  while ((WiFi.status() != WL_CONNECTED)&&(timeout))
  {
    y_delay(500);
    Display.print(" . . .");
    timeout=timeout-500;
  }

  if(WiFi.status()!= WL_CONNECTED)
  {
    Display.print("Internet Connection FAILED!");
  }
 else{
  Display.print("Cnctd!");
  y_delay(1000);
 }
  Display.print("IoT7egment IP is " + WiFi.localIP().toString());
  y_delay(1000);

 setupDefault();
  
  y_delay(30000);
  printDate();

}


void loop()
{
  
}
