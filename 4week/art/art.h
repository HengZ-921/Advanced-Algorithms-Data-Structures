#ifndef ART_H
#define ART_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Heap {
  int *dfar;
  short *skar;
  int front;
} Heap;

void *safeMalloc(int n);
int readNumber();

Heap makeHeap(int Length);
void enqueue(int df, short sk, int c, Heap *hp);
void swap ( int a, int b, int *df, short *sk );
void upheap(Heap *hp, int fr, int c);
void downheap(Heap *hp, int node, int c);
int removeMax(Heap *hp, int c);
void freeHeap(Heap h);

void fillHeap ( int *df, short *sk, short *type, int N, int c, Heap *Wh, Heap *Oh );
short startPoint ( int c, int Wnum, int ONum, Heap *Wh, Heap *Oh );
void copyHeap ( int *Wdf, int *Odf, short *Wsk, short *Osk, Heap *Wh, Heap *Oh );
void recover ( int N, int Wnum, int *Wdf, int *Odf, short *Wsk, short *Osk, Heap *Wh, Heap *Oh );
int replicate (short type, int c, Heap *Wh, Heap *Oh);
void paintingSteal(int N, int c);

#endif