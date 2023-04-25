#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

int main() {
  
  lli requestNum = readNumber();
  lint facNum = readNumber();
  if (requestNum <= 0) { printf("0\n"); return 0; }
  printf("Request: %lld\n",requestNum);

  lint *tArr = safeMalloc( facNum * sizeof(lint));
  lint *pArr = safeMalloc( facNum * sizeof(lint));
  lint *cArr = safeMalloc( facNum * sizeof(lint));
  preProd(&requestNum, facNum, tArr, pArr, cArr);
/* 
  for (lint i = 0; i < facNum; i++) { printf("%ld ",tArr[i]);}
  printf("\n\n");
  for (lint i = 0; i < facNum; i++) { printf("%ld ",pArr[i]);}
  printf("\n\n");
  for (lint i = 0; i < facNum; i++) { printf("%ld ",cArr[i]);}
  printf("\n\n");
*/
  Heap facPQ = makeHeap(facNum);
  sortTime(facNum, tArr, pArr, cArr, &facPQ);
  
/* 
  for (lint i = 0; i < facNum + 1; i++) { printf("%ld ",facPQ.prodN[i]);}
  printf("\n\n");
  for (lint i = 0; i < facNum + 1; i++) { printf("%ld ",facPQ.unitT[i]);}
  printf("\n\n");

  lint maxT = 0;
  for (lint i = 0; i < facNum + 1; i++) {
    if (maxT < facPQ.sumT[i]) {maxT = facPQ.sumT[i];}
    printf("%ld ",facPQ.sumT[i]- 57643581890880);
  }
  printf("\n\n");

  printf("Request: %lld\n",requestNum);
  printf("Max T: %ld\n",maxT - 57643581890880);
*/
  startProduction(requestNum,facNum,&facPQ);

  free(tArr); free(pArr); free(cArr); freeHeap(facPQ);
  return 0;
}