#include "noster.h"

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
  char line[11];
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

int improve( int L, int preidx, int *idx, int *ar ) {
  int initHp, finalHp = ar[preidx];
  for (int i = 0; i < L - 1; i++) { preidx = idx[preidx]; }
  initHp = ar[preidx];
  return finalHp - initHp;
}

int binarySearch ( int i, int n, int *ar, int * idxAr, int *preAr) {
  int mid, lidx = 1, ridx = n + 1;
  while (lidx < ridx) {
    mid = lidx + (ridx - lidx) / 2;
    if ( ar[idxAr[mid]] <= ar[i] ) { lidx = mid + 1; }
    else { ridx = mid; }
  }
  idxAr[lidx] = i; preAr[i] = idxAr[lidx - 1];
  return lidx;
}

void nosterRelease( int N ) {
  int *happy = safeMalloc(N * sizeof(int)), i, nL, dif, num = 0;
  int *idxAr = safeMalloc((N + 1) * sizeof(int)), *preAr = safeMalloc(N * sizeof(int));  
  idxAr[N] = 0;
  
  for (i = 0; i < N; i++) { happy[i] = readNumber(); idxAr[i] = 0; preAr[i] = 0; }

  for (i = 0; i < N; i++) {
    nL = binarySearch(i, num, happy, idxAr, preAr);
    num = (nL > num) ? nL : num;
  }

  dif = improve(num, idxAr[num], preAr, happy);
  
  printf("%d %d\n", num, dif);
  free(happy); free(idxAr); free(preAr);
}