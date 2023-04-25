#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

void *safeMalloc(int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

/* The function readNumber is adpated from ADS assignment 2 code.
 * It returns the interger read from the input.
 */

int readNumber() {
  char c = getchar();
  int i = 0;
  char line[12];
  assert( line != NULL );
  while ( c != ' ' && c != '\n' ) {
    line[i] = c;
    i++;
    c = getchar();
  }
  line[i] = '\0';
  int num = atol(line);
  return num;
}

Heap makeHeap(int Length) {
  Heap h;
  h.spotID = safeMalloc( Length * sizeof(int));
  h.qltLv = safeMalloc( Length * sizeof(int));
  h.front = 1;
  return h;
}

void enqueue(int id, int lv, Heap *hp) {
  int fr = hp->front;
  hp->spotID[fr-1] = id;
  hp->qltLv[fr-1] = lv;
  upheap(hp, fr);
  hp->front = fr + 1;
}

void swap ( int *pa , int *pb ) {
  int h = *pa; *pa = *pb; *pb = h;
}

void upheap(Heap *hp, int fr) {
  int a = fr - 1, b = fr / 2 - 1;
  if ( hp->qltLv[a] != hp->qltLv[0] ) {
    if ( hp->qltLv[a] < hp->qltLv[b] ) {
      swap( &(hp->qltLv[a]), &(hp->qltLv[b]));
      swap( &(hp->spotID[a]), &(hp->spotID[b]));
      upheap(hp, fr/2);
    }
  }
}

void initList(Heap *hp, int Length) {
  for (int i = 0; i < Length; i++) {
    int spot = readNumber(), quality = readNumber();
    enqueue(spot, quality, hp);
  }
}

void modifyList(Heap *hp, int visit, int total) {
  for (int i = 0; i < total - visit; i++) {
    int spot = readNumber(), quality = readNumber();
    if (quality > hp->qltLv[0]) {
      hp->qltLv[0] = quality; hp->spotID[0] = spot;
      downheap(hp, visit, 1);
    }
  }
}

void downheap(Heap *hp, int Length, int pos) {
  int lc = pos * 2 - 1, rc = lc + 1, num = pos - 1;
  if (lc >= Length) { return; }
  else if (rc >= Length) {rc = lc;}
  if ( (hp->qltLv[lc] < hp->qltLv[num]) && (hp->qltLv[lc] < hp->qltLv[rc]) ) {
    swap( &(hp->qltLv[num]), &(hp->qltLv[lc]));
    swap( &(hp->spotID[num]), &(hp->spotID[lc]));
    downheap(hp,Length,lc+1);
  } else if ( hp->qltLv[rc] < hp->qltLv[num] ) {
    swap( &(hp->qltLv[num]), &(hp->qltLv[rc]));
    swap( &(hp->spotID[num]), &(hp->spotID[rc]));
    downheap(hp,Length,rc+1);
  }
}

void freeHeap(Heap hp) {
  free(hp.spotID); free(hp.qltLv);
}

int partition(int Length, int *sArr, int *qArr) {
    int left = 0;
    int right = Length;
    int pvs = sArr[right/2], pvq = qArr[right/2];
    /* place a random element at index 0 */
    swap(&(sArr[0]), &(sArr[right/2]));
    swap(&(qArr[0]), &(qArr[right/2]));
    /* the rest of the code is the same */
    while (left < right) {
        while ((left < right) && (qArr[left] >= pvq)) { left++; }
        while ((left < right) && (pvq > qArr[right-1])) { right--; }
        if (left < right) {
        /* (arr[left] > pivot) && (arr[right-1] <= pivot) : swap */
            right--;
            swap(&(sArr[left]), &(sArr[right]));
            swap(&(qArr[left]), &(qArr[right]));
            left++;
        }
    }
    /* put pivot in right location: swap(0,left-1,arr) */
    left--;
    qArr[0] = qArr[left]; sArr[0] = sArr[left];
    qArr[left] = pvq; sArr[left] = pvs;
    return left;
}

void quickSort(int length, int *sArr, int *qArr) {
    int boundary;
    if (length <= 1) { return; }
    /* empty or singleton array: nothing to sort */
    boundary = partition(length, sArr, qArr);
    quickSort(boundary, sArr, qArr);
    quickSort(length - boundary - 1, &sArr[boundary + 1],&qArr[boundary + 1]);
}

