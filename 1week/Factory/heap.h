#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef long int lint;
typedef long long int lli;

typedef struct Heap {
  lint *prodN;
  lint *unitT;
  lint *sumT;
  lint front;
  // lint size;
} Heap;

void *safeMalloc(long int n);
lli readNumber();
lint readFactory();

void enqueue(lint t, lint p, lint cycles, Heap *hp);
void heapEmptyError();
int isEmptyHeap(Heap h);
Heap makeHeap();
void preProd(lli *request, lint facNum, lint *tArr, lint *pArr, lint *cArr);
void sortTime(lint facNum, lint *tArr, lint *pArr, lint *cArr, Heap *hp);
void swap ( lint *pa , lint *pb );
void upheap(Heap *hp, lint fr);
void startProduction(lli request, lint facNum, Heap *hp);
void downheap(Heap *hp, lint Length, lint num);
void freeHeap(Heap hp);

// void doubleHeapSize (Heap *hp);
// int removeMax(Heap *hp);
// int size(Heap *hp);

#endif