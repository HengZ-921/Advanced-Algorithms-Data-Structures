#include "sobch.h"

void *safeMalloc(int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

char *readName() {
  int strLen = 50, i = 0;
  char c = getchar(), *s = safeMalloc((strLen + 1) * sizeof(char));
  assert(s != NULL);
  while (c != '\n' && c != ' ' && c != EOF ) {
    s[i] = c; i++;
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
  int strLen = 10, i = 0;
  char c = getchar(), *s = safeMalloc((strLen + 1) * sizeof(char));
  assert(s != NULL);
  while (c != '\n' && c != ' ') {
    s[i] = c; i++;
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
/*
int hashnum (char *T, int p) {
  int i, A = 31, q = 1000037, s = strlen(T);
  long long int  h = T[0] - 96;
  for (i = 1; i < s; i++) {
    h += ( T[i] - 96 + h * A ) % q;
  }
  return h % (p - 1);
}
*/

int hashnum (char *T, int p) {
  int i, len = strlen(T);
  unsigned long long int  h = 0x811c9dc5;
  for (i = 1; i < len; i++) {
    h *= 0x01000193;
    h ^= T[i];
  }
  return h % p ;
}

List addItem(char *s, int t, List li) {
  List new = safeMalloc(sizeof(struct ListNode));
  new->name = s; new->time = t; new->next = li;
  return new;
}

int searchList ( char *s, int t, List li ) {
  if ( li == NULL ) { return 1; }
  else if ( strcmp(s, li->name) ) { return searchList(s, t, li->next); }
  else { li->time += t; free(s); return 0; }
}

void buildHash( int n, int p, List *table) {
  char *s; int i, t, hid; List li;
  for (i = 0; i < p; i++) { table[i] = NULL; }
  //int cl = 0;
  for (i = 0 ; i < n; i++) {
    s = readName(); t = readNumber(); hid = hashnum(s, p); li = table[hid];
    //if ( li == NULL ) { cl += 1; }
    if ( searchList(s, t, li) ) { table[hid] = addItem(s, t, table[hid]); }
  }
  //printf("Collision: %d\n", p - cl);
}

int retrieve (char *s, List li) {
  if ( li == NULL ) { return 0; }
  else if ( strcmp(s, li->name) ) { return retrieve(s, li->next); }
  else { return li->time; }
}

void freeList (List li) {
  List li1;
  while ( li != NULL ) {
    li1 = li->next;
    // printf("%s %d\n", li->name, li->time);
    free(li->name); free(li); li = li1;
  }
  return;
}

void reportTime ( int m, int p, List *hs ) {
  char *s, *maxname = NULL;
  long int sumT = 0, maxT = 0, t;
  for (int i = 0; i < m; i++) {
    s = readName(); t = retrieve(s, hs[hashnum(s, p)]); sumT += t;
    if ( t > maxT ) {
      maxT = t;
      if ( maxname != NULL ) { free(maxname); }
      maxname = s;
    } else { free(s); }
  }
  for (int i = 0; i < p; i++) { freeList(hs[i]); } free(hs);
  printf("%ld\n", sumT);
  if (sumT) { printf("%s: %ld\n", maxname, maxT); free(maxname); }
}
