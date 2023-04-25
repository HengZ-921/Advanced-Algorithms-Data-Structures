#include "stick.h"

void *safeMalloc(int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

int readNumber() {
  int i = 0;
  char line[10];
  assert( line != NULL );
  char c = getchar();
  while ( c != ' ' && c != '\n' ) {
    line[i] = c;
    i++;
    c = getchar();
  }
  line[i] = '\0';
  int num = atoi(line);
  return num;
}

void swap(int i, int j, int *arr, int *num) {
  int h = arr[i]; arr[i] = arr[j]; arr[j] = h;
  h = num[i]; num[i] = num[j]; num[j] = h;
}

int partition(int length, int *arr, int *num) {
    int left = 0, right = length;
    int pivot, pvN, idx = rand()%length;
    swap(0, idx, arr, num); /* place a random element at index 0 */
    pivot = arr[0]; pvN = num[0];
    /* the rest of the code is the same */
    while (left < right) {
      while ((left < right) && (arr[left] <= pivot)) { left++; }
      while ((left < right) && (pivot < arr[right-1])) { right--; }
      if (left < right) {
        /* (arr[left] > pivot) && (arr[right-1] <= pivot) : swap */
        right--; swap(left, right, arr, num); left++;
      }
    }
    /* put pivot in right location: swap(0,left-1,arr) */
    left--;
    arr[0] = arr[left]; num[0] = num[left];
    arr[left] = pivot; num[left] = pvN;
    return left;
}

void quickSort(int length, int *arr, int *num) {
    int boundary;
    if (length <= 1) { return; }
    /* empty or singleton array: nothing to sort */
    boundary = partition(length, arr, num);
    quickSort(boundary, arr, num);
    quickSort(length - boundary - 1, &arr[boundary + 1],&num[boundary + 1]);
}

void combine (int L, int *arr, int *num) {
  int i, j;
  for (i = 0; i <= L; i++) {
    for (j = i + 1; j < L; j++) {
      if ( arr[i] == arr[j] ) { num[i] += num[j]; num[j] = 0; arr[j] = arr[L +2]; }
    }
  }
}

void fileStore (int *type, int size, int amount, int *restMem, int *copies) {
  int i = 0, k, m = 1, L = 0;
  while ( amount > 0 ) {
    if ( size <= restMem[i] ) {
      m = restMem[i] / size; k = amount / m; 
      if ( copies[i] ) {
        if ( k >= copies[i]) { restMem[i] -= m * size; amount -= copies[i] * m; i++; } 
        else if ( k > 0 ) {
        copies[*type] = copies[i] - k; restMem[*type] = restMem[i]; restMem[i] -= m * size;
        amount -= k * m; copies[i] = k; *type +=1; i++;
        } else {
        restMem[*type] = restMem[i]; copies[*type] = copies[i] - 1; restMem[i] -= size * amount;
        amount = 0; copies[i] = 1; *type +=1;
        }
      } else {
        if ( k > 0 ) { restMem[i] -= m * size; amount -= k * m; copies[i] = k; i++; }
        else { restMem[i] -= size * amount; amount = 0; copies[i] = 1; }
        *type +=1;
      }
      quickSort( *type + 1, restMem, copies );
    } else { i++; } 
  }
  combine( *type + 1, restMem, copies );
  quickSort( *type + 1, restMem, copies );
  for (i = 0; i < *type + 1; i++) { if ( restMem[i] < restMem[*type + 1] ) { L += 1; } }
  *type = L + 1;
}

void firstFitStore ( int s, int f ) {

  int i, sum = 0, type = 1, t = (int)(log(s)/log(2)), temp = 0;
  int *size = safeMalloc( (t + 1) * sizeof(int) ), *amount = safeMalloc( (t + 1) * sizeof(int) );
  size[0] = 1; amount[0] = 0;
  for ( i = 1; i <= t; i++ ) { size[i] = size[i - 1] * 2; amount[i] = 0; }
  for ( i = 0; i < f; i++ ) { temp = (int)( log( readNumber() ) / log(2) ); amount[temp]++; }

  int *restMem = safeMalloc( t * 4 * sizeof(int) ), *copies = safeMalloc( t * 4 * sizeof(int) );
  for ( i = 0; i < t * 4; i++ ) { restMem[i] = s; copies[i] = 0; }
  if ( amount[t] ) { restMem[0] -= size[t]; copies[0] = amount[t]; }

  for ( i = t - 1; i >= 0; i-- ) { fileStore(&type, size[i], amount[i], restMem, copies); }
  for ( i = 0; i < type + 1; i++) { sum += copies[i]; } printf("%d\n", sum);

  free(size); free(amount); free(restMem); free(copies);
}