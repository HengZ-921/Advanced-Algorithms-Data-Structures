#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LibQueue.h"

int main() {
  
  int h = readNumber(), c = readNumber(), N = readNumber();
  long int s = 0;
  int size = (h + c) * 4;

  Queue gates = newQueue( N );
  magicMirror(&gates, N);
/*
  while (gates.front <= N - size + 1) {
    s += dynamicSkip(&gates, h, c);
    magicMirror(&gates, N);
    // printf("Sum: %d \n",s);
  }
*/
  // printf("Front: %d \n",gates.array[gates.front%gates.size]);
  s += bruteSkip(&gates,gates.front,h,c);
  printf("%ld\n",s);

  freeQueue(gates);
  
  return 0;
}