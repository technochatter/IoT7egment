 //LICENSE
 /*
	parseString.h Arduino Library to handle string and URL Parsing
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

#ifndef parseString_h
#define parseString_h
#include <arduino.h>

typedef enum term {Append_RIGHT, Append_LEFT, Append_JUSTIFY, Append_DEF} Append;

typedef struct  stringFragment
{
  int separator[20];
  int seperatorCount;
  String fragments[21];
}Fragment;

class parseString {
public:
  //parseString(int,int,int);
  Fragment extractFragments(String , char);
  String appendSpace(String , int , Append);
private:
  
};

#endif
