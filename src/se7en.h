 //LICENSE
 /*
	se7en.h Arduino Library to print to IoT7egment.Latest version at https://github.com/technochatter/IoT7egment
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

/*
 * 74HC595-7_SEGMENT
 *      Q0-E
 *      Q1-DP
 *      Q2-D
 *      Q3-C
 *      Q4-G
 *      Q5-A
 *      Q6-F
 *      Q7-B
 *      
*/

/*
To add new character add the character at the end of 
segCharacter[] array and the corresponding bit value to the digits[] array
*/

#ifndef se7en_h
#define se7en_h
#include <arduino.h>

const int numberOfDigits=6;
const byte mask=0b10000000;
const unsigned long scrollDelay=400;
typedef enum _status {ENGAGED, FREE} displayStatus;
typedef enum align {LEFT, RIGHT, APPEAR, SCROLL} Alignment;
typedef enum {HOURS=24, AM_PM=12} timeFormat;
typedef enum {Hi=1, No=2, Lo=3} Priority;
typedef enum {I, Q} Execute;//to be implemented Immediate or Queue when two subsequent prints are called

//Segments pins assignment in order a,b,c,d,e,f,g,dot
const uint8_t segpin[] = {5,7,3,2,0,6,4,1};//CONFIGURE ACCORDING TO CIRCUITRY Q-Numbers 5== Q5 of Shift Register
const char segCharacter[] = {'0','1','2','3','4','5','6','7','8','9','A','a','b','C','c','d','E','e','F','g','H','h','I','i','J','K','L','l','n','o','P','q',' ','r','S','t','U','u','y','z','-','_','!','?','=','\'',',',':'};
const byte digitNo[]={0b01111111,0b10111111,0b11011111,0b11101111,0b11110111,0b11111011,0b11111101,0b11111110};//index 0 is the RIGHTmost one LSB(Decimal)
const uint8_t digits[] = {
// bits       76543210
// digits     abcdefg(DP)
        0b11111100,//0 0x00 00
        0b01100000,//1 0x01 01
        0b11011010,//2 0x02 02
        0b11110010,//3 0x03 03
        0b01100110,//4 0x04 04
        0b10110110,//5 0x05 05
        0b10111110,//6 0x06 06
        0b11100000,//7 0x07 07
        0b11111110,//8 0x08 08
        0b11110110,//9 0x09 09
        0b11101110,//A 0x0A 10
        0b11111010,//a 0xFA 11
        0b00111110,//b 0x0B 12
        0b10011100,//C 0x0C 13
        0b00011010,//c 0x1A 14
        0b01111010,//d 0x0D 15
        0b10011110,//E 0x9E 16
        0b11011110,//e 0x0E 17
        0b10001110,//F 0x0F 18
        0b11110110,//g 0x10 19
        0b01101110,//H 0x11 20
        0b00101110,//h 0x2E 21
        0b00001100,//I 0x12 22
        0b10001000,//i 0x88 23
        0b01111000,//J 0x13 24
        0b01100010,//K 0x62 25
        0b00011100,//L 0x14 26
        0b01100000,//l 0x60 27
        0b00101010,//n 0x15 28
        0b00111010,//o 0x16 29
        0b11001110,//P 0x17 30
        0b10100110,//q 0xA6 31
        0b00000000,//Space  32
        0b00001010,//r 0x18 33
        0b10110110,//S 0x19 34
        0b00011110,//t 0x1A 35
        0b01111100,//U 0x7C 36
        0b00111000,//u 0x1B 37
        0b01110110,//y 0x1C 38
        0b01011010,//z 0x4A 39
        0b00000010,//- 0x02 40
        0b00010000,//_ 0x10 41
        0b01100001,//! 0x61 42
        0b11001011,//? 0xCB 43
        0b00010010,//= 0x12 44
        0b00000100,//' 0x04 45
        0b00001000,//, 0x08 46
        0b10010000,//: 0X90 47
};

class se7en {
  
public:

  se7en(int,int,int);
  void begin();
  void begin(Alignment);
  void scrollDisplay(String ,unsigned long);
  void print(String str);
  boolean printlp(String str);//print low priority if disply is engaged then it doesn't print and returns false
  displayStatus segStatus=FREE;
private:

  int _datapin;
  int _clockpin;
  int _latchpin;
  unsigned int _nOfDots;
  unsigned int _nOfChars;
  unsigned int _charIndex[numberOfDigits]={32,32,32,32,32,32};
  unsigned int _dotBit[numberOfDigits];
  void _showData(byte, byte, boolean);
  void _char2index(String);
};
#endif
