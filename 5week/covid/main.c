#include "covid.h"

int main() {
  int n = readNumber(), m = readNumber(), *row = safeMalloc(m * sizeof(int));

  initialize(m, row); propagate(n, m, row);
  
  printf("%d\n", row[m - 1] + 1);
  free(row);
  
  return 0;
}