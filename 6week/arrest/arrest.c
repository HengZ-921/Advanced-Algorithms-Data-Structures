#include "arrest.h"

void *safeMalloc(int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

short readNumber() {
  short i = 0;
  char c = getchar(), s[7];
  while (c != '\n' && c != ' ') {
    s[i] = c; i++; c = getchar();
  }
  s[i] = '\0';
  short num = atoi(s);
  return num;
}

char getSymbol () {
  char c;
  while (1) {
    c = getchar();
    if ( c == '*' ) { return 'o'; }
    else if ( c == '-' ) { return 'x'; }
  }
}

void fillGraph ( short n, char **G ) {
  short i, j;
  for (i = 0; i < n; i++) { G[i] = safeMalloc( n * sizeof(char)); }
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) { G[i][j] = getSymbol(); } 
  }
}

void dfs (char **G, short x, short y, short n) {
  if ( G[x][y] == 'f' || G[x][y] == 'o' ) { return; }
  G[x][y] = 'f';
  if ( x < n - 1 ) { dfs(G, x + 1, y, n); }
  if ( x > 0 ) { dfs(G, x - 1, y, n); }
  if ( y < n - 1 ) { dfs(G, x, y + 1, n); }
  if ( y > 0 ) { dfs(G, x, y - 1, n); }
}

void searchGraph ( short n, char **G ) {
  short i;
  for (i = 0; i < n; i++) { dfs(G, i, 0, n); dfs(G, i, n - 1, n); }
  for (i = 1; i < n - 1; i++) { dfs(G, 0, i, n); dfs(G, n - 1, i, n); }
}

void countArrest ( short n, char **G ) {
  short i, j; int a = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) { if ( G[i][j] == 'x' ) { a += 1; } }
    free(G[i]);
  }
  free(G); printf("%d\n",a);
}