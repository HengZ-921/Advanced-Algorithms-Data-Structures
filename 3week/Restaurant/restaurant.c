#include "restaurant.h"

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

char readChar() {
  char c = getchar();
  while ( !isdigit(c) ) { c = getchar(); }
  return c;
}

int record (int N, int r, int *y) {
  int mid = r / 2 + r % 2, idx = 0, xm = 0, row = 0;
  char c;
  while ( idx < r ) {
    for (int i  = 0; i < N; i++) {
      c = readChar();
      if ( c == '1' ) {
        y[idx] = i; idx++;
        if ( idx == mid ) { xm = row; }
      }
    }
    row++;
    if ( idx == r ) { break; }
  }
  return xm;
}

void swap ( int *ar, int a, int b ) {
  int h = ar[a]; ar[a] = ar[b]; ar[b] = h;
}

int partition(int *ar, int l, int r) {
  int idx = rand()%(r-l) + l;
  swap(ar,idx,r);
  int piv = ar[r], i = l - 1;
  for (int j = l; j < r; j++) {
    if ( ar[j] <= piv ) { i++; swap(ar, i, j); }
  }
  swap(ar, i + 1, r);
  return i + 1;
}

int quickSelect (int *ar, int l, int r, int i) {
  if (l == r) { return ar[l]; }
  int q = partition(ar, l, r),  k = q - l + 1;
  if (i == k) { return ar[q]; }
  else if ( i < k ) { return quickSelect(ar, l, q - 1, i); }
  else { return quickSelect(ar, q + 1, r, i - k); }
}
