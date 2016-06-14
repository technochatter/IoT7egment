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
