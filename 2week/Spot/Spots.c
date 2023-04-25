#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

int main() {
  
  lint spotsNum = readNumber();
  lint visitNum = readNumber();
  if (visitNum <= 0) { return 0; }

  Heap minPQVisit = makeHeap(visitNum);
  char *idAr = safeMalloc((visitNum + 1) * sizeof(char) * N);

  initList(&minPQVisit, visitNum, idAr);
  modifyList(&minPQVisit, visitNum, spotsNum, idAr);

  quickSort(visitNum, &idAr[N], &minPQVisit.qAr[1]);
  
  for (lint i = 1; i < visitNum + 1; i++) {
    printf("%s %ld\n", &idAr[i * N], minPQVisit.qAr[i]);
  } 

  freeHeap(minPQVisit); free(idAr);
  
  return 0;
}