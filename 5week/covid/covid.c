#include "covid.h"

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
  char line[9], c = getchar();
  assert( line != NULL );
  while ( 1 ) {
    if ( isdigit(c) || c == '-') { line[i] = c; i++; }
    c = getchar();
    if ( i > 0 && (!isdigit(c)) ) { break; }
  }
  line[i] = '\0';
  return atoi(line);
}

void initialize (int m, int *ar) {
  int j, num = 0;
  ar[0] = readNumber() - 1;
  for (j = 1; j < m; j++) {
    num = readNumber() - 1 + ar[j - 1];
    if ( num > 0 && ar[j - 1] ) { ar[j] = num; }
    else { ar[j] = 0; }
  } 
}

void propagate (int n, int m, int *ar) {
  int i, j, up = 0, left = 0, num = 0;
  for (i = 1; i < n; i++) {
    num = ar[0] + readNumber() - 1;
    if ( (num + 1 - ar[0]) && ar[0] && (num > 0) ) { ar[0] = num; }
    else { ar[0] = 0; }
    for (j = 1; j < m; j++) {
      num = readNumber() - 1;
      if (num == -1) { ar[j] = 0; continue; }
      left = ( ar[j - 1] ) ? num + ar[j - 1] : 0;
      up = ( ar[j] ) ? num + ar[j] : 0;
      ar[j] = (left > up) ? left : up;
    }
  }
}