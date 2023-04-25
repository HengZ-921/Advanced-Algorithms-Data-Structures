#include "challenges.h"

int main () {

  int i, n = readNumber();
  lint *starts = safeMalloc(n * sizeof(lint)), *ends = safeMalloc(n * sizeof(lint));
  for (i = 0; i < n; i++ ) { starts[i] = readNumber(); ends[i] = readNumber(); }

  int m = readNumber();
  lint *kqrs = safeMalloc(m * sizeof(lint)), *intvl = safeMalloc(n * sizeof(lint));

  int *ords = linesweep(n, m, starts, ends, intvl, kqrs);  
  findKthVal(n, m, ords, intvl, kqrs);
  for (i = 0; i < m; i++ ) { printf("%ld\n", kqrs[i]); } free(kqrs);

  return 0;
}