#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tollgate.h"

int main() {

  int h = readNumber(), c = readNumber(), N = readNumber();
  
  if ( N > h + c ) { longway(h, c, N); }
  else { shortway(h, c, N); }
  
  return 0;
}
