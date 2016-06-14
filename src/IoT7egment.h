 //LICENSE
 /*
	IoT7egment.h Arduino Library to print to IoT7egment.Latest version at https://github.com/technochatter/IoT7egment
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

#ifndef IoT7egment_h
#define Iot7egment_h
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include "NTPtime.h"
#include "se7en.h"


class IoT7egment : public se7en//we can call IoTsegment.print()
{
  public:

    IoT7egment(int a,int b,int c):se7en(a,b,c)
    {
            
    }

  };


#endif
