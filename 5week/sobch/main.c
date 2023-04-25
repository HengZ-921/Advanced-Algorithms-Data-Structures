#include "sobch.h"

int main() {

  int n = readNumber(), p = readNumber();
  List *hsTable = safeMalloc( p * sizeof(List));
  
  buildHash(n, p, hsTable);

  int m = readNumber(); reportTime(m, p, hsTable);

  return 0;
}
