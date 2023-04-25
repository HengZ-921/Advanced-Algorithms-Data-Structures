#ifndef HEAP_H
#define HEAP_H

/* The strategy for this challenge is to use heap to build a priority queue of time used,
 * the main function startProduction is a while loop, keep subtracting number of produced laptops
 * from the request number. Each time of subtraction, the factory another period of the factory
 * will be added to the corresponding element in the cumulative time priority queue,
 * and this new time will be sort to the proper position in the priority queue.
 * 
 * The worst case of each time of sorting is bounded to O(log(n)), which is well known for heap,
 * where n is the number of factories.
 * 
 * But for a large number of request, such iteration will last for a very long time, so we need to 
 * pre-process the request number by the function preProd.
 * The idea is to calculate the cumulative efficiency of factories, by summing up the efficiency
 * (number of labtops / days needed). Then make an intial guess for time needed by the equation
 * (request / sum of efficiency). Based on this estimated time, we can start our iteration on 
 * cycles got from here.
 * Because of the rounding errors in division, sometimes we will encounter that the production
 * is over the request in the estimated time, therefore, we need reserve some request to avoid
 * this overflow problem. The reserved number is (maxTime * sum of efficiency).
 * 
 * This function needs to iterate over all elements in the time and procdution array,
 * and gives the cycles for each factory.
 * and it is bounded to O(n).
 * 
 * So, basically we are dealing with this reserved request number, which requires approxiamately
 * one iteration of the max time factory, and the iteration number of the while loop is bounded to 
 * O(n), where the coefficients depends on the time range between the fastest factory and slowest
 * factory, how many iteration of faster factories can finish in the time of one cycle of the 
 * slowest factory.
 * 
 * Take all these analysis together, the overall time complexity of the program is
 * O(n*log(n) + n), where O(n* log(n)) comes from the heap sorting in the function sortTime and 
 * startProduction, and O(n) comes from the input reading and function preProd.
 * 
 */

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

#endif