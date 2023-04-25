#include "arrest.h"

int main () {
  short n = readNumber();
  char **graph = safeMalloc( n * sizeof(char*));

  fillGraph(n, graph);
  searchGraph(n, graph);
  countArrest(n, graph);
  
  return 0;
}