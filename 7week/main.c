#include "garbage.h"

int main () {
  short n, s, t; char c;
  scanf("%hd%c%hd%c%hd%c", &n, &c, &s, &c, &t, &c);
  char *vmarks = markPortals(n, s, t);

  short m = n - t - s + 2;
  int **mPorts = fillGraph (n, s, t, m, vmarks);
  FordFulkerson(mPorts, m);

  return 0;
}