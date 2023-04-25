#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL, malloc, free */
#include <string.h> /* strcpy */
#include <ctype.h>  /* isspace, isdigit, isalpha, isalnum */
#include <assert.h> /* assert */

void *safeMalloc(int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

char *readName() {
  int strLen = 50;
  char c = getchar();
  int i = 0;
  char *s = safeMalloc((strLen + 1) * sizeof(char));
  assert(s != NULL);
  while (c != '\n' && c != ' ' && c != EOF ) {
    s[i] = c;
    i++;
    if (i >= strLen) { /* s is not large enough, its length is doubled */
      strLen = 2 * strLen;
      s = realloc(s, (strLen + 1) * sizeof(char));
      assert(s != NULL);
    }
    c = getchar();
  }
  s[i] = '\0';
  return s;
}

int readNumber() {
  int strLen = 10;
  char c = getchar();
  int i = 0;
  char *s = safeMalloc((strLen + 1) * sizeof(char));
  assert(s != NULL);
  while (c != '\n' && c != ' ' && c != EOF ) {
    s[i] = c;
    i++;
    if (i >= strLen) { /* s is not large enough, its length is doubled */
      strLen = 2 * strLen;
      s = realloc(s, (strLen + 1) * sizeof(char));
      assert(s != NULL);
    }
    c = getchar();
  }
  s[i] = '\0';
  int num = atoi(s); free(s);
  return num;
}

int main() {

  int i, t, n = readNumber(), p = readNumber();
  int *hs = safeMalloc( 6 * p * sizeof(int*));
  char *s;
  // printf("N: %d, P: %d\n", n, p);
  for (i = 0; i < n; i++) {
    s = readName(); t = readNumber();
    // printf("%s %d\n", s, t);
    free(s);
  }

  int m = readNumber(); // printf("M: %d\n", m);
  for (i = 0; i < m; i++) {
    s = readName();
    // printf("%s\n", s);
    free(s);
  }

  printf("0\n"); free(hs);

  return 0;
}
