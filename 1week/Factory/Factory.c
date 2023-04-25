#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"

int main() {
  
  lli requestNum = readNumber();
  lint facNum = readNumber();
  if (requestNum <= 0) { printf("0\n"); return 0; }

  lint prodArr[facNum], timeArr[facNum];
  //lint *prodArr = safeMalloc(facNum * sizeof(lint));
  //lint *timeArr = safeMalloc(facNum * sizeof(lint));
  sortTime(facNum, prodArr, timeArr);
  //printf("%ld %ld\n",sizeof(prodArr), sizeof(timeArr));
  startProduction(facNum, requestNum, prodArr, timeArr);
  printf("0\n");

  //free(prodArr); free(timeArr);
  return 0;
}