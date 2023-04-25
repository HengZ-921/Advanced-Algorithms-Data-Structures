#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "heap.h"

void *safeMalloc(long int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%ld) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

lint readNumber() {
  int strLen = 12;
  char c = getchar();
  int i = 0;
  char *line = malloc((strLen+1)*sizeof(char));
  assert( line != NULL );
  while ( c != ' ' && c != '\n' ) {
    line[i] = c;
    i++;
    if ( i >= strLen ) {
      strLen = 2*strLen; /* s is not large enough, its length is doubled */
      line = realloc(line,(strLen+1)*sizeof(char));
      assert( line != NULL );
    }
    c = getchar();
  }
  line[i] = '\0';
  lint num = atol(line);
  free(line);
  return num;
}

char *readID() {
  int strLen = 4;
  char c = getchar();
  int i = 0;
  char *line = malloc((strLen+1)*sizeof(char));
  assert( line != NULL );
  while ( c != ' ' && c != '\n' ) {
    line[i] = c;
    i++;
    if ( i >= strLen ) {
      strLen = 1 + strLen; /* s is not large enough, its length is doubled */
      line = realloc(line,(strLen+1)*sizeof(char));
      assert( line != NULL );
    }
    c = getchar();
  }
  line[i] = '\0';
  return line;
}

Heap makeHeap(lint Length) {
  Heap h;
  h.qAr = safeMalloc( (Length + 1) * sizeof(lint));
  h.front = 1;
  return h;
}

void enqueue(char *id, lint qlv, Heap *hp, char *idAr) {
  lint fr = hp->front;
  hp->qAr[fr] = qlv;
  strcpy(&(idAr[fr * N]), id);
  upheap(hp, idAr, fr);
  hp->front = fr + 1;
}

void swap ( int a, int b, char *idAr, lint *qAr) {
  lint ti = qAr[a];
  qAr[a] = qAr[b]; qAr[b] = ti;
  char *sc = malloc(N), *sa = &(idAr[a * N]), *sb = &(idAr[b * N]);
  strcpy(sc, sa); strcpy(sa, sb); strcpy(sb, sc);
  free(sc);
}

void upheap(Heap *hp, char *idAr, lint fr) {
  if ( hp->qAr[fr] != hp->qAr[1] ) {
    if ( hp->qAr[fr] < hp->qAr[fr/2] ) {
      swap( fr, fr/2, idAr, hp->qAr);
      upheap(hp, idAr, fr/2);
    }
  }
}

void initList(Heap *hp, lint Length, char *idAr) {
  for (lint i = 0; i < Length; i++) {
    char *id = readID(); lint qlv = readNumber();
    enqueue(id, qlv, hp, idAr);
    free(id);
  }
}

void modifyList(Heap *hp, lint visit, lint total, char *idAr) {
  for (lint i = 0; i < total - visit; i++) {
    char *id = readID(); lint qlv = readNumber();
    if (qlv > hp->qAr[1]) {
      hp->qAr[1] = qlv;
      strcpy(&(idAr[N]), id);
      free(id);
      downheap(hp, visit, 1, idAr);
    } else { free(id); }
  }
}

void downheap(Heap *hp, lint Length, lint num, char *idAr) {
  lint lc = num * 2, rc = lc + 1;
  if (lc > Length) { return; }
  else if (rc > Length) {rc = lc;}
  if ( (hp->qAr[lc] < hp->qAr[num]) && (hp->qAr[lc] < hp->qAr[rc]) ) {
    swap( lc, num, idAr, hp->qAr);
    downheap(hp, Length, lc, idAr);
  } else if ( hp->qAr[rc] < hp->qAr[num] ) {
    swap( rc, num, idAr, hp->qAr);
    downheap(hp, Length, rc, idAr);
  }
}

void freeHeap(Heap hp) { free(hp.qAr); }

lint partition(lint Length, char *idAr, lint *qAr) {
    lint left = 0, right = Length;
    lint pvq = qAr[right/2];
    char *pvs = malloc(N), *temp = malloc(N);
    strcpy(pvs, &(idAr[right/2 * N]));
    /* place the middle element at index 0 */
    swap(0, right/2, idAr, qAr);
    /* the rest of the code is the same */
    while (left < right) {
        while ((left < right) && (qAr[left] >= pvq)) { left++; }
        while ((left < right) && (pvq > qAr[right-1])) { right--; }
        if (left < right) {
        /* (arr[left] > pivot) && (arr[right-1] <= pivot) : swap */
            right--;
            swap(left, right, idAr, qAr);
            left++;
        }
    }
    /* put pivot in right location: swap(0,left-1,arr) */
    left--;
    strcpy(temp, &(idAr[left * N]));
    qAr[0] = qAr[left]; strcpy(&(idAr[0]), temp);
    qAr[left] = pvq; strcpy(&(idAr[left * N]), pvs);
    free(pvs); free(temp);
    return left;
}

void quickSort(lint Length, char *idAr, lint *qAr) {
    lint boundary;
    if (Length <= 1) { return; }
    /* empty or singleton array: nothing to sort */
    boundary = partition(Length, idAr, qAr);
    quickSort(boundary, idAr, qAr);
    quickSort(Length - boundary - 1, &idAr[(boundary + 1) * N],&qAr[boundary + 1]);
}

