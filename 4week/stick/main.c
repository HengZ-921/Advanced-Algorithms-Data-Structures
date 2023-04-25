#include "stick.h"

int main () {

  int s = readNumber(), f = readNumber();
  if ( f == 0 ) { printf("%d\n", 0); return 0; }
  firstFitStore(s, f);
  
  return 0;
}
