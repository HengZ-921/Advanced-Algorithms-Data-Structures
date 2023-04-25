#include "challenges.h"

void *safeMalloc(int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

lint readNumber() {
  short i = 0;
  char c = getchar(), line[12];
  while ( 1 ) {
    if ( isdigit(c) ) { line[i] = c; i++; }
    c = getchar();
    if ( i > 0 && (!isdigit(c)) ) { break; }
  }
  line[i] = '\0';
  return atol(line);
}

void fillIntv ( int n, lint **ar ) {
  int i;
  for (i = 0; i < 3; i++) { ar[i] = safeMalloc( n * sizeof(lint)); }
  for (i = 0; i < n; i++) {
    ar[0][i] = readNumber(); ar[1][i] = readNumber(); ar[2][i] = ar[1][i] - ar[0][i] + 1;
  }
}

void fillQr ( int m, lint **ar ) {
  int i;
  for (i = 0; i < 3; i++) { ar[i] = safeMalloc( m * sizeof(lint)); }
  for (i = 0; i < m; i++) {
    ar[0][i] = readNumber(); ar[1][i] = readNumber(); ar[2][i] = i;
  }
}

void swap( short row, int l, int r, lint **ar ) {
  lint h; short i;
  for ( i = 0; i < row; i++) {
    h = ar[i][l]; ar[i][l] = ar[i][r]; ar[i][r] = h;
  }
}

int part( short base, short row, int lo, int hi, lint **ar ) {
  int i, p = lo, idx = rand() % (hi - lo) + lo;
  swap(row, lo, idx, ar);
  lint pv = ar[base][hi];
  for ( i = lo; i < hi; i++) {
    if (ar[base][i] < pv) { swap(row, p, i, ar); p++; }
  }
  swap(row, p, hi, ar);
  return p;
}

void qkSort( short base, short row, int lo, int hi, lint **ar) {
  if ( lo < hi ) {
    int pv = part(base, row, lo, hi, ar);
    qkSort(base, row, lo, pv - 1, ar);
    qkSort(base, row, pv + 1, hi, ar);
  }
}

int loSearch(lint x, lint *ar, int n) {
  int l = 0, r = n - 1, pos = n, mid;
  while ( l <= r ) {
    mid = l + ((r - l) >> 1);
    if ( x <= ar[mid] ) { pos = mid; r = mid - 1; }
    else { l = mid + 1; }
  }
  return pos;
}

int hiSearch(lint x, lint *ar, int n) {
  int l = 0, r = n - 1, pos = n, mid;
  while ( l <= r ) {
    mid = l + ((r - l) >> 1);
    if ( x < ar[mid] ) { pos = mid; r = mid - 1; }
    else { l = mid + 1; }
  }
  return pos;
}



