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
