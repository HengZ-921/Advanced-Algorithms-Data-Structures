#ifndef HEAP_H
#define HEAP_H

/* In this challenge two sort algorithms are used, heap sort and quick sort.
 * At first we take m input and use heap sort to make a minHeap, which is bounded to O(m * log(m)).
 * then all the (n-m) rest inputs will be compared with the first element of minHeap, which is O(1).
 * If the new spot has higher quality, the first element will be changed and then downheap O(log(m)).
 * The worst case is that all (n-m) following inputs are larger than the previous one, like test case 3,
 * and the time complexity is bounded to O( n * log(m) + n - m ).
 * 
 * After reading all the inputs, we have a minHeap, but this cannot be directly printed as output.
 * We still need to use quickSort to make sure the array is in order.
 * Since the minHeap is more or less sorted from smallest to largest, the quickSort can do it job
 * much quicker than from scratch. It is well known that for quick sort the time complexity is
 * bounded to O( m * log(m) ).
 * 
 * Take all these together, we have the program time complexity bounded to O( n * log(m) ).
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct Heap {
  int *spotID;
  int *qltLv;
  int front;
} Heap;

void *safeMalloc(int n);
int readNumber();
Heap makeHeap();

void enqueue(int id, int lv, Heap *hp);
void swap ( int *pa , int *pb );
void upheap(Heap *hp, int fr);
void downheap(Heap *hp, int Length, int num);
void freeHeap(Heap hp);

void initList(Heap *hp, int Length);
void modifyList(Heap *hp, int visit, int total);

int partition(int Length, int *sArr, int *qArr);
void quickSort(int length, int *sArr, int *qArr);

#endif