#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

void *safeMalloc(long int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%ld) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

/* The function readNumber is adpated from ADS assignment 2 code.
 * It returns the interger read from the input.
 */

lli readNumber() {
  int strLen = 20;
  char c = getchar();
  int i = 0;
  char *line = malloc((strLen+1)*sizeof(char));
  assert( line != NULL );
  while ( c != '\n' ) {
    line[i] = c;
    i++;
    if ( i >= strLen ) {
      strLen = 2*strLen; /* s is not large enough, its length is doubled */
      line = realloc(line,(strLen+1)*sizeof(char));
      assert( line != NULL );
    }
    c = getchar();
  }
  line[i] = '\0';
  lli num = atoll(line);
  free(line);
  return num;
}

lint readFactory() {
  int strLen = 9;
  char c = getchar();
  int i = 0;
  char *line = malloc((strLen+1)*sizeof(char));
  assert( line != NULL );
  while ( c != ' ' && c != '\n' ) {
    line[i] = c;
    i++;
    if ( i >= strLen ) {
      strLen = 2*strLen; /* s is not large enough, its length is doubled */
      line = realloc(line,(strLen+1)*sizeof(char));
      assert( line != NULL );
    }
    c = getchar();
  }
  line[i] = '\0';
  lint num = atol(line);
  free(line);
  return num;
}

Heap makeHeap(lint Length) {
  Heap h;
  h.prodN = safeMalloc( (Length + 1) * sizeof(lint));
  h.unitT = safeMalloc( (Length + 1) * sizeof(lint));
  h.sumT = safeMalloc( (Length + 1) * sizeof(lint));
  h.prodN[0] = 0; h.unitT[0] = 0; h.sumT[0] = 0;
  h.front = 1;
  return h;
}

int isEmptyHeap(Heap h) {
  return (h.front == 1);
}

void heapEmptyError() {
  printf("heap empty\n");
  abort();
}

void enqueue(lint t, lint p, lint c, Heap *hp) {
  lint fr = hp->front;
  hp->prodN[fr] = p;
  hp->unitT[fr] = t;
  hp->sumT[fr] = t * c;
  upheap(hp, fr);
  hp->front = fr + 1;
}

void preProd(lli *request, lint facNum, lint *tArr, lint *pArr, lint *cArr) {
  double sumV = 0;
  lint cycles, maxT = 0, reserve;
  for (lint i = 0; i < facNum; i++) {
    pArr[i] = readFactory(); tArr[i] = readFactory();
    maxT = (maxT >= tArr[i])? maxT : tArr[i];
    sumV += pArr[i]/(float)tArr[i];
  }
  reserve = sumV * maxT / 5;
  //printf("Reserve: %ld\n",reserve);
  lli rest = (*request > reserve)? (*request - reserve) : *request;
  lint sumTime = rest / sumV ;

  for (lint i = 0; i < facNum; i++) {
    cycles = sumTime / tArr[i];
    cArr[i] = cycles;
    if (cArr[i] < 1) { cArr[i] = 1; }
    *request -= (cArr[i]-1) * pArr[i];
  }
}

void sortTime(lint facNum, lint *tArr, lint *pArr, lint *cArr, Heap *hp) {
  for (lint i = 0; i < facNum; i++) {
    enqueue(tArr[i], pArr[i], cArr[i], hp);
  }
}

void swap ( lint *pa , lint *pb ) {
  lint h = *pa; *pa = *pb; *pb = h;
}

void upheap(Heap *hp, lint fr) {
  if ( hp->sumT[fr] != hp->sumT[1] ) {
    if ( hp->sumT[fr] < hp->sumT[fr/2] ) {
      swap( &(hp->unitT[fr]), &(hp->unitT[fr/2]));
      swap( &(hp->prodN[fr]), &(hp->prodN[fr/2]));
      swap( &(hp->sumT[fr]), &(hp->sumT[fr/2]));
      upheap(hp, fr/2);
    }
  }
}

void startProduction(lli request, lint facNum, Heap *hp) {
  lli rest = request;
  lint time = 0, count = 0;
  while (rest > 0) {
    count++;
    rest -= hp->prodN[1];
    time = hp->sumT[1];
    hp->sumT[1] += hp->unitT[1];
    downheap(hp, facNum, 1);
  }
  printf("%ld\n", time);
  // printf("%ld\n", count);
}

void downheap(Heap *hp, lint Length, lint num) {
  lint lc = num * 2, rc = lc + 1;
  if (lc > Length) { return;}
  else if (rc > Length) {rc = lc;}
  if ( (hp->sumT[lc] < hp->sumT[num]) && (hp->sumT[lc] < hp->sumT[rc]) ) {
    swap( &(hp->sumT[num]), &(hp->sumT[lc]));
    swap( &(hp->unitT[num]), &(hp->unitT[lc]));
    swap( &(hp->prodN[num]), &(hp->prodN[lc]));
    downheap(hp,Length,lc);
  } else if ( hp->sumT[rc] < hp->sumT[num] ) {
    swap( &(hp->sumT[num]), &(hp->sumT[rc]));
    swap( &(hp->unitT[num]), &(hp->unitT[rc]));
    swap( &(hp->prodN[num]), &(hp->prodN[rc]));
    downheap(hp,Length,rc);
  }
}

void freeHeap(Heap hp) {
  free(hp.prodN);
  free(hp.unitT);
  free(hp.sumT);
}
