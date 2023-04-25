#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

int main() {
  
  int spotsNum = readNumber();
  int visitNum = readNumber();
  if (visitNum <= 0) { return 0; }

  Heap minPQVisit = makeHeap(visitNum);
  initList(&minPQVisit, visitNum);
  modifyList(&minPQVisit, visitNum, spotsNum);
  
  quickSort(visitNum, minPQVisit.spotID,  minPQVisit.qltLv);

  for (int i = 0; i < visitNum; i++) {
    printf("%d %d\n", minPQVisit.spotID[i], minPQVisit.qltLv[i]);
  }

  freeHeap(minPQVisit);
  
  return 0;
}