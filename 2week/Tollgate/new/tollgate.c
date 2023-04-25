#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tollgate.h"

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
  char line[15], c = getchar();
  assert( line != NULL );
  while ( c != ' ' && c != '\n' ) {
    line[i] = c; i++;
    c = getchar();
  }
  line[i] = '\0';
  int num = atoi(line);
  return num;
}

void init (long int *s, int *t, int h, int c) {
  int p;
  for (int i = 0; i <= h + c; i++) { t[i] = h; s[i] = 0; }
  t[h + c] = h + c;
  for (int i = 0; i < h + c; i++) {
    p = readNumber(); t[i] = t[i] % h;
    for (int j = 0; j <= h + c; j++) { s[j] += p; }
    for (int j = 0; j <= i; j++) {
      if ( t[j] < h ) { s[j] -= p; }
      t[j]++;
    }
  }
}

void update (long int *s, int *t, int h, int c, int N) {
  int p = readNumber();
  for (int j = 0; j < h + c; j++) {
    if ( ( t[h + c] <= N - h ) && ( t[j] >= h + c ) ) {
      t[j] = 0;
      if ( s[j] > s[h + c] ) { s[j] = s[h + c]; }
      else { s[h + c] = s[j]; }
    }
  }
  for (int i = 0; i <= h + c; i++) {
    if ( t[i] >= h ) { s[i] += p; }
    t[i]++;
  }
}

void longway(int h, int c, int N) {
  
  long int *Sums = safeMalloc( ( h + c + 1 ) * sizeof(long int) );
  int *States = safeMalloc( ( h + c + 1 ) * sizeof(int) );

  init(Sums, States, h, c);

  for (int i = 0; i < N - h - c; i++) {
    update(Sums, States, h, c, N);
  }
  long int s = Sums[0];
  for (int i = 1; i <= h + c; i++) { s = (s < Sums[i]) ? s : Sums[i]; }
  printf("%ld\n",s);
  
  free(Sums); free(States); 
}

long int bruteSkip (int *pl, int h, int c, int num) {
  long int s = 0, temp = 0;
  for (int i = 0; i < num; i++) { s += pl[i]; }

  if (num < h) { return s ; }

  for (int i = h; i < num; i++) { temp += pl[i]; }
  s = (s <= temp)? s : temp;
  for (int i = 0; i < num - h; i++) {
    temp = temp + pl[i] - pl[h + i];
    s = (s <= temp)? s : temp;
  }
  return s;
}

void shortway(int h, int c, int N) {
  
  int *priceList = safeMalloc( N * sizeof(int) );
  for (int i = 0; i < N; i++) { priceList[i] = readNumber(); }
  long int s = bruteSkip(priceList, h, c, N);
  printf("%ld\n",s); free(priceList);
}
