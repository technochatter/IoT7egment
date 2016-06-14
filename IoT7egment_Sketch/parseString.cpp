 //LICENSE
 /*
	parseString.cpp Arduino Library to handle string and URL Parsing
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

#include "parseString.h"

Fragment parseString::extractFragments(String s, char ch)
{
  int prev,next,c,i;
  prev=next=c=i=0;
  Fragment newString;
  
  while(i<s.length())
  {
    if(s.charAt(i)==ch)
      newString.separator[c++]=i;//i increments so offset +1
    i++ ;      
   }

  newString.seperatorCount=c;
  i=0;
  while(i<newString.seperatorCount)
  {
    next=newString.separator[i];
    newString.fragments[i]=s.substring(prev,next);
    prev=next+1;
    next=newString.separator[i++];
	}
  newString.fragments[i]=s.substring(prev);
  return newString;
}

 String parseString::appendSpace(String wrds, int newLength, Append trm)//modifier: RIGHT, LEFT, JUSTIFY, DEF
 {
  int appendLength=newLength-(wrds.length());
  switch(trm)
  {
    case Append_LEFT:
        for(int i=0;i<appendLength;i++)
          wrds=wrds+' ';
          return wrds;
      break;

    case Append_RIGHT:
        for(int i=0;i<appendLength;i++)
          wrds=' '+wrds;
          return wrds;
      break;

    case Append_JUSTIFY:
        for(int i=0;i<(int)(appendLength/2);i++)
          wrds=' '+wrds;
          
        for(int i=0;i<appendLength-(int)(appendLength/2);i++)
          wrds=wrds+' ';
          return wrds;
      break;

    default:
        for(int i=0;i<newLength;i++)
          wrds=' '+wrds;
          
        for(int i=0;i<newLength;i++)
          wrds=wrds+' ';
          return wrds;
    }
 }
