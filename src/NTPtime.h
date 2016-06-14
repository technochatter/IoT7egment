//LICENSE
 /*
	NTPtime.h handles timeSync with NTP server pool. Latest version at https://github.com/technochatter/IoT7egment
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

#ifndef NTPtime_h
#define NTPtime_h
#include <WiFiUdp.h>

static char* dayNames[]={"", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
static const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};
static char* monthNames[]={"","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
#define LEAP_YEAR(Y) ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )

struct  strDateTime
{
  byte hour;
  byte minute;
  byte second;
  int year;
  byte month;
  byte day;
  char* dayName;
} ;
  
WiFiUDP udp; // A UDP instance to let us send and receive packets over UDP
strDateTime DateTimeInstance;  

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; // Buffer to hold incoming and outgoing UDP packets
const unsigned int NTPport = 2390;  // Local port to listen for UDP packets
unsigned long epoch;
  
void ExtractFromUnixTime( unsigned long TimeStamp, struct strDateTime* DateTime)
{
    uint8_t year;
    uint8_t month, monthLength;
    uint32_t time;//unsigned int
    unsigned long days;
    time = (uint32_t)TimeStamp;
    DateTime->second = time % 60;
    time /= 60; // now it is minutes
    DateTime->minute = time % 60;
    time /= 60; // now it is hours
    DateTime->hour = time % 24;
    time /= 24; // now it is days
    unsigned int dayNumber = ((time + 4) % 7) + 1;  // Sunday is day 1 
    DateTime->dayName=dayNames[dayNumber];
    year = 0;  
    days = 0;
    while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {
    year++;
    }
    DateTime->year = year; // year is offset from 1970 
  
    days -= LEAP_YEAR(year) ? 366 : 365;
    time  -= days; // now it is days in this year, starting at 0
    days=0;
    month=0;
    monthLength=0;
    for (month=0; month<12; month++) {
    if (month==1) { // february
      if (LEAP_YEAR(year)) {
      monthLength=29;
      } else {
      monthLength=28;
      }
    } else {
      monthLength = monthDays[month];
    }
    
    if (time >= monthLength) {
      time -= monthLength;
    } else {
      break;
    }
    }
    DateTime->month = month + 1;  // jan is month 1  
    DateTime->day = time + 1;     // day of month
    DateTime->year += 1970;
 }
 
// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

//Receive NTP packet and Parse to UnixTime
boolean receiveNTPpacket()
{
    int NTPpacket = udp.parsePacket();//returns packet length
    if (!NTPpacket) {
      Serial.println("No packet received yet");
      return false;
    }
    else {
      Serial.print("packet received, length=");
      Serial.println(NTPpacket);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    // now convert NTP time into everyday time:
    // Unix time starts on Thursday, 1 January 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    epoch = secsSince1900 - seventyYears;//+19800;
    return true;
    }
}

boolean timeSync(char * ntpServerName, int timeZone)
{
  udp.begin(NTPport); // Open the UDP port for comms
  IPAddress timeServerIP; // server IP address
  //unsigned long UnixTime;
  if(WiFi.status() == WL_CONNECTED)
  {
   //get a random server from the pool
    WiFi.hostByName(ntpServerName, timeServerIP); 
    sendNTPpacket(timeServerIP); // send an NTP packet to a time server
    // wait to see if a reply is available
    //delay(1000);
    yield();
    // Serial.println(udp.localPort());
    if(receiveNTPpacket())//receive NTP packet
    {
      ExtractFromUnixTime(epoch +  (timeZone *  360) , &DateTimeInstance);//convert to Day Time
      return true;
    }
  }
  else{
    Serial.println("WiFi Not connected");
  }
  return false;
}

void y_delay(unsigned long millisecond)
{
  unsigned long prevmil=millis();
    while((millis()-prevmil) < millisecond)
   {
      yield();
   }
}

#endif
