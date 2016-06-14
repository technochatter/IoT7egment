 //LICENSE
 /*
	se7en.cpp Arduino Library to print to IoT7egment.Latest version at https://github.com/technochatter/IoT7egment
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
#include "parseString.h"

//initialize constructor
se7en::se7en(  int datapin, int clockpin, int latchpin)
{
  _datapin=datapin;
  _clockpin=clockpin;
  _latchpin=latchpin;
  pinMode(_latchpin,OUTPUT);
  pinMode(_clockpin,OUTPUT);
  pinMode(_datapin,OUTPUT);
  digitalWrite(_latchpin,LOW);
  digitalWrite(_clockpin,LOW);
  digitalWrite(_datapin,LOW);
  _prevmil=millis();
}

//Calculation
/*
 * (n+5-dots)*550 ms approx scroll time
 * 
 * 
 */

//#############################################################################################################################
//Finds corresponding index of the characters from the digits[] array
//#############################################################################################################################

//extracts the index of character to display to the corresponding digits
void se7en::_char2index(String str2print)
 {
    int i,j,k=0;
    int tempDot[numberOfDigits]={0};
    //Reset Dot 
    _nOfDots=0;
    //Reset The Digit Arrays
    for(i=0; i < numberOfDigits;i++)
    {
      _dotBit[i]=0;//dotbit
      _charIndex[i]=32;//Blank Space
    }

    for(i=0;(k<numberOfDigits)&&(i<str2print.length());i++)//array indexout of bound if word < 12
    {
    char char2print=str2print.charAt(i);
    boolean found=false;
    if(char2print=='.')
    {
      tempDot[_nOfDots++]=i;
      continue;
    }
    for(j=0;j<sizeof(segCharacter);j++)
    {
      if(char2print == segCharacter[j])
      {
        found=true;
        break;
       }
     }
  
      if((!found)&&isalpha(char2print))
       {
        if((char2print>='A')&&(char2print<='Z'))
          {
           for(j=0;j<sizeof(segCharacter);j++)
             if((char)(char2print+32) == segCharacter[j])
               {
                   found=true;
                   break;
                }
                  
           }
             else if((char2print>='a')&&(char2print<='z'))
                  {
                    for(j=0;j<sizeof(segCharacter);j++)
                      if((char)(char2print-32) == segCharacter[j])
                      {
                       found=true;
                       break;
                       }
                    }
         }

      if(found)
        _charIndex[k++]=j; //index of the character goes here
     else
     _charIndex[k++]=41;//show dash or underscore by default
    }

    //removing offset from the index of Dot(DP-Decimal Point)
    for(i=0;i<_nOfDots;i++)//if c=0 i.e no Dot present then loop doesn't run
      tempDot[i]=tempDot[i]-i-1;

    for(i=0; i < _nOfDots;i++)
      _dotBit[tempDot[i]]=1;//dotbit
    

    _nOfChars=k;//number of character
 }


//#############################################################################################################################################################################
//   showData(<index of the character to print from digits[] array>, <bit string to push to second register to activate the desired digit>, <true if Dot segment needs to set>)
//#############################################################################################################################################################################

 //shows raw data from digits[] array to a single digit (no muxing)
void se7en::_showData(byte index,byte digit,boolean dot)
{
  byte state;
  digitalWrite(_latchpin,LOW);//swithcing off display latch
  byte data=digits[index];
  if(dot)
  data=data+1;//append Decimal Point to the digit
  //starting with MSB first for shift register hence Q7-->Q0
    for(int i=7;i>=0;i--)
  {
    //searching for the state of the segment attached to corresponding Q pin of shift reg
   for(int j=0;j<8;j++)
   {
    if(segpin[j]==i)
    {
    state=(data & (mask>>j))?HIGH:LOW;
    //below use !state if Common Anode(+)
    digitalWrite(_datapin,state);//data already present at input
    digitalWrite(_clockpin,HIGH);//clock to enter data in storage register
    digitalWrite(_clockpin,LOW);

    break;
    }

   }
  }

   //activating the digits by sending the corresponding bit value to digit attached shift register
       for(int i=0;i<8;i++)
  {
    state=digit&(1<<i);
    //below use !state if Common Anode(+)
    digitalWrite(_datapin,state);//data already present at input
    digitalWrite(_clockpin,HIGH);//clock to enter data in storage register
    digitalWrite(_clockpin,LOW);

  }
  digitalWrite(_latchpin,HIGH);//swithcing on display latch

}


//#############################################################################################################################
//display.begin()  prints with Time MUxing in all the digits from the _charIndex[numberOfDigits] & _dotPos[numberOfDigits] array
//#############################################################################################################################
//Time Multiplex the 6 digit display

void se7en::begin(Alignment trm)//put this in an infinite loop or Ticker or void loop()
{

  if(trm==RIGHT)
  {
    int offset=numberOfDigits- _nOfChars;
    for(int i=0;i<numberOfDigits-offset;i++)
    {
      _showData(_charIndex[i],digitNo[numberOfDigits-i-1-offset],_dotBit[i]);//digitNo[5] activates the 5th digit by pushing the appropriate serial data to the second Shift Reg
      delay(1);
     }
   }
  else
    for(int i=0,l=0;i<numberOfDigits;i++)
    {
      _showData(_charIndex[i],digitNo[numberOfDigits-i-1],_dotBit[i]);//digitNo[5] activates the 5th digit by pushing the appropriate serial data to the second Shift Reg
      delay(1);
     }
}

void se7en::begin()
{
  begin(LEFT);
}

//###############################################################
//Scroll part
//###############################################################

void se7en::scrollDisplay(String str, unsigned long scrollDelay, boolean repeat, int *scroll_ctr)//, boolean repeat)
{
   //begin(LEFT);

   unsigned int lngth=str.length();
   //str="     "+str;
   _currentmil=millis();
   if((_currentmil-_prevmil)>scrollDelay)
   {
     _prevmil=_currentmil;    
     if(*scroll_ctr>str.length()-1)
      *scroll_ctr=0;  

     if(str.charAt(*scroll_ctr)=='.')//skipping the dot since it is not considered a seperate character hence increment counter to next character
      *scroll_ctr=*scroll_ctr+1;
     _char2index(str.substring(*scroll_ctr));//sending the substring starting from the next character

     if(((*scroll_ctr)<str.length()-6)||repeat)
     //{
        (*scroll_ctr)++;
        //return false;
     //}
    // else
      //  return true;

    }
 }

//###############################################################
//APPEAR 
//###############################################################

void se7en::displayWord(String str, unsigned long appearDelay, boolean repeat)//, Alignment val
{
  
  //declaring instances of the parseString class
  static int ctr=0;
  static boolean flag=false;


  parseString newStr;
  Fragment url;//instance of struct which stores the separator[]; seperatorCount; fragments[];
  String tempString;
  int lastWordIndex;
  
  url=newStr.extractFragments(str, ' ');//returns struct
  lastWordIndex=url.seperatorCount;//returns int index of last word
    
  
  unsigned int lngth=str.length();
  _currentmil=millis();
  //entering this section after every appearDelay interval
  if((_currentmil-_prevmil)>appearDelay)
   {
    _prevmil=_currentmil;
    
    if(ctr>lastWordIndex)
      ctr=0;
     
    tempString= url.fragments[ctr];
    if(tempString.length() <= numberOfDigits)
      _char2index(tempString);
    else
    {
     if(!flag)//printing first half of the word of length > number of digits
      {
        _char2index(tempString.substring(0));
        flag=true;
        return;
      }
      _char2index(tempString.substring(tempString.length()-6));//printing second half if first half is already printed(i.e flag=true)
      flag=false;//resetting flag for the next word to handle
    }
    if((ctr<lastWordIndex)||repeat)
    ctr++;
   }
 }

//NEEDS REVIEW
 void se7en::updateDigit(int digitIndex, char ch, boolean dot)
 {
  int i;
    for(i=0;i<sizeof(segCharacter);i++)
       if(ch == segCharacter[i])
        break;
      
    _charIndex[digitIndex]=i;
    _dotBit[digitIndex]=dot;
 }

void se7en::print(String str)//, boolean repeat)
{
   //begin(LEFT);
     _char2index(str);//sending the substring starting from the next character
 }
