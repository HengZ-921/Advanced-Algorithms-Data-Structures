#include "challenges.h"

int main () {
  short row = 3;
  lint **intvl = safeMalloc( row * sizeof(lint*));
  int i, n = readNumber();
  fillIntv(n, intvl);

  qkSort(2, row, 0, n - 1, intvl);

  int m = readNumber(); lint **query = safeMalloc( row * sizeof(lint*));
  lint *out = safeMalloc( m * sizeof(lint*));
  for (i = 0; i < m; i++) { out[i] = -1; }
  fillQr(m, query);
  qkSort(1, row, 0, m - 1, query);

  int a, b, j;
  for (i = 0; i < n; i++) {
    a = loSearch(intvl[0][i], query[1], m);
    b = hiSearch(intvl[1][i], query[1], m);
    for (j = a; j < b; j++) {
      if ( query[0][j] > 1 ) { query[0][j]--; }
      else if ( query[0][j] == 1 ) { out[query[2][j]] = intvl[2][i]; query[0][j]--; }
    }
  }

  for (i = 0; i < row; i++) { free(intvl[i]); } free(intvl);
  for (i = 0; i < row; i++) { free(query[i]); } free(query);
  for (i = 0; i < m; i++) { printf("%ld\n", out[i]); } free(out);

  return 0;
}