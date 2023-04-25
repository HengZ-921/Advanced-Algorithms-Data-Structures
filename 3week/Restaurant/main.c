#include "restaurant.h"

int main() {

  int N = readNumber(), r = readNumber();
  int *y = safeMalloc(r * sizeof(int));

  int xm = record(N, r, y);
  int ym = quickSelect(y, 0, r - 1, r / 2 + r % 2);

  printf("%d %d\n", xm, ym);
  free(y);
  return 0;
}
