#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"

void sortDate(lint websiteNum, lint dateArray[], char sellArray[]) {
    
    for (int i = 0; i < websiteNum; i++) {
        dateArray[i] = readNumber();
        sellArray[i] = 1;
        dateArray[i + websiteNum] = readNumber() + 1;
        sellArray[i + websiteNum] = 0;
    }
    quickSort(websiteNum * 2, dateArray, sellArray);

}

void findMax(lint websiteNum, lint dateArray[], char sellArray[]) {
    lint i = 0, maxDate = 0, maxNum = 0, tempNum = 0, tempDate = dateArray[0];
    while (i < websiteNum * 2 ) {
        if ( tempDate != dateArray[i] ) {
            /* if day changes, check if current GPU number is larger than previous max */
            if (tempNum > maxNum) { maxNum = tempNum; maxDate = tempDate; }
            tempDate = dateArray[i];
        }
        if (sellArray[i]) { tempNum += 1; }
        else { tempNum -= 1; }
        i ++;
    }
    printf("%d %d\n", maxDate, maxNum);
}

/* The function readNumber is adpated from ADS assignment 2 code.
 * It returns the interger read from the input.
 */

lint readNumber() {
  int strLen = 12;
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
  int num = atoi(line);
  free(line);
  return num;
}

/* The following functions swap, partition and quicksort are adapted
 * from Imperative Programming lecture note, they are used to sort
 * the array of the start and end date of GPU selling.
 * To fit the input number size, the int data type are changed to long long int.
 */

void swap(lint i, lint j, lint arr[]) {
    lint h = arr[i];
    arr[i] = arr[j];
    arr[j] = h;
}

void swapC(lint i, lint j, char sell[]) {
    char h = sell[i];
    sell[i] = sell[j];
    sell[j] = h;
}

lint partition(lint length, lint arr[], char sell[]) {
    lint left = 0;
    lint right = length;
    lint pivot, idx = rand()%length;
    char pvSell;
    swap(0, idx, arr); /* place a random element at index 0 */
    swapC(0, idx, sell);
    pivot = arr[0]; pvSell = sell[0];
    /* the rest of the code is the same */
    while (left < right) {
        while ((left < right) && (arr[left] <= pivot)) { left++; }
        while ((left < right) && (pivot < arr[right-1])) { right--; }
        if (left < right) {
        /* (arr[left] > pivot) && (arr[right-1] <= pivot) : swap */
            right--;
            swap(left, right, arr);
            swapC(left, right, sell);
            left++;
        }
    }
    /* put pivot in right location: swap(0,left-1,arr) */
    left--;
    arr[0] = arr[left]; sell[0] = sell[left];
    arr[left] = pivot; sell[left] = pvSell;
    return left;
}

void quickSort(lint length, lint arr[], char sell[]) {
    lint boundary;
    if (length <= 1) { return; }
    /* empty or singleton array: nothing to sort */
    boundary = partition(length, arr, sell);
    quickSort(boundary, arr, sell);
    quickSort(length - boundary - 1, &arr[boundary + 1],&sell[boundary + 1]);
}
