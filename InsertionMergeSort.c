#include <stdlib.h>
#include <stdio.h>

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
  char line[9];
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


int searchIndex(int length, int *arr, int value) {
  int i = 0;
  while ((i < length) && (arr[i] <= value)) { i++; }
  return i;
}
void shiftRight(int length, int *arr, int *num, int idx) {
/* shift the elements with indices from [idx,length) one position to the right. */
  for (int i = length; i > idx; i--) { arr[i] = arr[i-1]; num[i] = num[i-1]; }
}
void insert(int length, int *arr, int *num) {
/* insert value in sorted array */
  int value = arr[length], temp = num[length];
  int idx = searchIndex(length, arr, value);
  shiftRight(length, arr, num, idx);
  arr[idx] = value; num[idx] = temp;
}
void insertionSort(int length, int *arr, int *num) {
  for (int i=1; i < length; i++) { insert(i, arr, num); }
}


void merge(int *arr, int *num, int p, int q, int r) {

  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1, n2 = r - q;
  int La[n1], Ma[n2], Ln[n1], Mn[n2];

  for (int i = 0; i < n1; i++) { La[i] = arr[p + i]; Ln[i] = num[p + i]; }
  for (int j = 0; j < n2; j++) { Ma[j] = arr[q + 1 + j]; Mn[j] = num[q + 1 + j]; }

  // Maintain current index of sub-arrays and main array
  int i = 0, j = 0, k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (La[i] <= Ma[j]) { arr[k] = La[i]; num[k] = Ln[i]; i++; }
    else { arr[k] = Ma[j]; num[k] = Mn[j]; j++; }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) { arr[k] = La[i]; num[k] = Ln[i]; i++; k++; }
  while (j < n2) { arr[k] = Ma[j]; num[k] = Mn[j]; j++; k++; }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int *arr, int *num, int l, int r) {
  if (l < r) {

    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(arr, num, l, m);
    mergeSort(arr, num, m + 1, r);

    // Merge the sorted subarrays
    merge(arr, num, l, m, r);
  }
}
