#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

int main() {
  
  lli requestNum = readNumber();
  lint facNum = readNumber();
  if (requestNum <= 0) { printf("0\n"); return 0; }

  lint *tArr = safeMalloc( facNum * sizeof(lint));
  lint *pArr = safeMalloc( facNum * sizeof(lint));
  lint *cArr = safeMalloc( facNum * sizeof(lint));
  preProd(&requestNum, facNum, tArr, pArr, cArr);

  Heap facPQ = makeHeap(facNum);
  sortTime(facNum, tArr, pArr, cArr, &facPQ);
  free(tArr); free(pArr); free(cArr); 

  startProduction(requestNum,facNum,&facPQ);
  freeHeap(facPQ);
  
  return 0;
}