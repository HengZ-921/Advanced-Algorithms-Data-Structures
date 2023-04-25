#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"

void *safeMalloc(long int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%ld) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

void sortTime(lint facNum, lint timeArr[], lint prodArr[]) {

  for (lint i = 0; i < facNum; i++) { prodArr[i] = readFactory(); timeArr[i] = readFactory(); }
  quickSort(facNum, timeArr, prodArr);
//*
  printf("Time:\n");
  for (lint i = 0; i < facNum; i++) { printf("%ld ",timeArr[i]); }
  printf("\n\n");

  lint sumProd = 0;
  
  printf("Production:\n");
  for (lint i = 0; i < facNum; i++) { sumProd += prodArr[i]; printf("%ld ",prodArr[i]); }
  printf("\n\n");

  printf("Sum Production: %ld\n", sumProd);
//*/
}

void startProduction(lint facNum, lli requestNum, lint timeArr[], lint prodArr[]) {
  lint sumTime[facNum], rest = requestNum, neededTime = 0;
  for (int i = 0; i < facNum; i++) { sumTime[i] = timeArr[i]; }
  /*
  while (rest > 0) {
    rest -= prodArr[0];
    printf("Rest: %lld\n", rest);
    neededTime = sumTime[0];
    sumTime[0] += timeArr[0];
    bubbleSort(facNum, sumTime, prodArr, timeArr);
  }
  */
  //for (int i = 0; i < facNum; i++) { printf("%lld ", sumTime[i]); }
  //printf("\n");
  printf("Rest: %llu\n", requestNum);

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
  lint num = atoll(line);
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

/* The following functions swap, partition, quicksort and bubbleSort
 * are adapted from Imperative Programming lecture note, 
 * they are used to sort the array of the start and end date of GPU selling.
 * To fit the input number size, the int data type are changed to long long int.
 */

void swap(lint i, lint j, lint arr[]) {
    lint h = arr[i];
    arr[i] = arr[j];
    arr[j] = h;
}

lint partition(lint length, lint tarr[], lint parr[]) {
    lint left = 0;
    lint right = length;
    lint tpivot, ppivot, idx = rand()%length;

    swap(0, idx, tarr); /* place a random element at index 0 */
    swap(0, idx, parr);
    tpivot = tarr[0]; ppivot = parr[0];
    /* the rest of the code is the same */
    while (left < right) {
        while ((left < right) && (tarr[left] <= tpivot)) { left++; }
        while ((left < right) && (tpivot < tarr[right-1])) { right--; }
        if (left < right) {
        /* (arr[left] > pivot) && (arr[right-1] <= pivot) : swap */
            right--;
            swap(left, right, tarr);
            swap(left, right, parr);
            left++;
        }
    }
    /* put pivot in right location: swap(0,left-1,arr) */
    left--;
    tarr[0] = tarr[left]; parr[0] = parr[left];
    tarr[left] = tpivot; parr[left] = ppivot;
    return left;
}

void quickSort(lint length, lint tarr[], lint parr[]) {
    lint boundary;
    if (length <= 1) { return; }
    /* empty or singleton array: nothing to sort */
    boundary = partition(length, tarr, parr);
    quickSort(boundary, tarr, parr);
    quickSort(length - boundary - 1, &tarr[boundary + 1],&parr[boundary + 1]);
}

void bubbleSort(lint length, lint starr[], lint parr[], lint tarr[]) {
    int j;
    for (j=0; j+1 < length; j++) {
        if (starr[j] > starr[j+1]) {
            swap(j, j+1, tarr);
            swap(j, j+1, parr);
            swap(j, j+1, starr);
        }
    }
}
