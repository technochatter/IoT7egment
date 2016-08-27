# IoT7egment
Seven Segment Highly Visible and Stylish Display with Swapable digit to suit your color! Connects to the internet using esp8266.Can be used as a clock by default or displaying Notifications Weather and what not. 

# Snapshots


NTP 12Hr Clock Mode:
![NTP_12Hr](https://github.com/technochatter/IoT7egment/blob/master/docs/Face.JPG?raw=true)


Connected to HOTSPOT Prompt:
![HOTSPOT_Connected](https://github.com/technochatter/IoT7egment/blob/master/docs/2.JPG?raw=true)


NTP 24Hr Clock Mode:
![NTP_24Hr](https://github.com/technochatter/IoT7egment/blob/master/docs/3.JPG?raw=true)


Time Sync Done:
![Sync_Prompt](https://github.com/technochatter/IoT7egment/blob/master/docs/4.JPG?raw=true)


_Photos dont justify the looks_:
![looks](https://github.com/technochatter/IoT7egment/blob/master/docs/5.JPG?raw=true)

#CONFIG MENU

Expandable Menu:
![Accordion list](https://github.com/technochatter/IoT7egment/blob/master/docs/6.png?raw=true)

Custom Pin Config:
![Menu 1](https://github.com/technochatter/IoT7egment/blob/master/docs/7.png?raw=true)

Device Name:
![Menu 3](https://github.com/technochatter/IoT7egment/blob/master/docs/9.png?raw=true)

ThingSpeak:
![Menu 4](https://github.com/technochatter/IoT7egment/blob/master/docs/10.png?raw=true)



# Features
* Stylish and Visible(Hence Seven Segment and not LCD)
* Compact pluggable design with multiple layers of vero
* Customizable: digits swapable to suit your color.
* ESP8266 inside.
* Least Number of pins to interface(Five-including VCC and GND)
* Digits expandable to Eight.
* Easy to use Arduino Coding : Example, Simply the statement:

`Display.print("String to Display")`

	will display the given string in the display. If the string has more characters than the number of Digits then it will Scroll the string from Left to Right.

* By default it shows Time according to configuration (AM/PM or HOURS or DATE Day Name interval) and syncs with internet NTP.
* The time display is overridden when any other string is printed (i.e. print() function is called with instance of the class) and Time Display resumes when display is free.
    
# Shortcomings
**characters: m, w, x and any other undefined symbols will be replaced with _(underscore or dash)**
	
# To Do
* Use PROGMEM to release heap
* Integrate task handling and priority(use callback function pointers)
* Formatting into a proper library with Keywords.txt etc
* Responsive Landing Page for login and ~~configure~~
* FileSystem to store config, Webpage
* Notification Display-Missed Call, Text, Email
* Weather
* Battery Low Indication etc
