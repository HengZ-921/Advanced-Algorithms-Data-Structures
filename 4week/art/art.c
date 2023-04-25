#include "art.h"

void *safeMalloc(int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

int readNumber() {
  int i = 0;
  char line[9];
  assert( line != NULL );
  char c = getchar();
  while ( c != ' ' && c != '\n' ) {
    line[i] = c;
    i++;
    c = getchar();
  }
  line[i] = '\0';
  int num = atoi(line);
  return num;
}

Heap makeHeap(int Length) {
  Heap h;
  h.dfar = safeMalloc( (Length + 1) * sizeof(int));
  h.skar = safeMalloc( (Length + 1) * sizeof(short));
  h.dfar[0] = 0; h.skar[0] = 0;
  h.front = 1;
  return h;
}

void fillHeap ( int *df, short *sk, short *type, int N, int c, Heap *Wh, Heap *Oh ) {
  for (int i = 0; i < N; i++) {
    if ( type[i] ) { enqueue(df[i], sk[i], c, Wh); }
    else { enqueue(df[i], sk[i], c, Oh); }
  }
  free(type); free(df); free(sk);
}

void enqueue(int df, short sk, int c, Heap *hp) {
  int fr = hp->front;
  hp->dfar[fr] = df; hp->skar[fr] = sk;
  upheap(hp, fr, c);
  hp->front = fr + 1;
}

void swap ( int a, int b, int *df, short *sk ) {
  int h = df[a]; df[a] = df[b]; df[b] = h;
  short k = sk[a]; sk[a] = sk[b]; sk[b] = k;
}

void upheap(Heap *hp, int fr, int c) {
  if (fr == 1) { return; }
  if ( hp->dfar[fr] > c ) {
    if (hp->dfar[fr] < hp->dfar[fr/2] ) { swap(fr, fr/2, hp->dfar, hp->skar); upheap(hp, fr/2, c); }
    else if ( (hp->dfar[fr] == hp->dfar[fr/2]) && (hp->skar[fr] > hp->skar[fr/2]) ) {
      swap(fr, fr/2, hp->dfar, hp->skar); upheap(hp, fr/2, c);
    }
  } else {
    if ( (hp->skar[fr] > hp->skar[fr/2]) || (hp->dfar[fr/2] > c) ) {
      swap(fr, fr/2, hp->dfar, hp->skar); upheap(hp, fr/2, c);
    }
  }
}

short startPoint ( int c, int Wnum, int ONum, Heap *Wh, Heap *Oh ) {
  if ( Wh->dfar[1] > c ) {
    if ( Oh->dfar[1] > c ) { return -1; }
    else { return 0; }
  } else {
    if ( Oh->dfar[1] > c ) { return 1; }
    else { return 2; }
  }
}

void copyHeap ( int *Wdf, int *Odf, short *Wsk, short *Osk, Heap *Wh, Heap *Oh ) {
  for ( int i = 0; i < Wh->front; i++) { Wdf[i] = Wh->dfar[i]; Wsk[i] = Wh->skar[i]; }
  for ( int i = 0; i < Oh->front; i++) { Odf[i] = Oh->dfar[i]; Osk[i] = Oh->skar[i]; }
}

void recover ( int N, int Wnum, int *Wdf, int *Odf, short *Wsk, short *Osk, Heap *Wh, Heap *Oh ) {
  for ( int i = 0; i <= Wnum; i++) { Wh->dfar[i] = Wdf[i]; Wh->skar[i] = Wsk[i]; }
  for ( int i = 0; i <= N - Wnum; i++) { Oh->dfar[i] = Odf[i]; Oh->skar[i] = Osk[i]; }
  free(Wdf); free(Wsk); free(Odf); free(Osk);
  Wh->front = Wnum + 1; Oh->front = N - Wnum + 1;
}

void downheap(Heap *hp, int node, int c) {
  int lc = 2 * node, rc = lc + 1;
  if (lc >= hp->front) { return; }
  else if (rc >= hp->front) { rc = lc; }

  if ( hp->dfar[node] > c ) {
    if ( (hp->dfar[lc] < hp->dfar[node]) && (hp->dfar[lc] < hp->dfar[rc]) ) {
      swap(lc, node, hp->dfar, hp->skar); downheap(hp, lc, c);
    } else if ( hp->dfar[rc] < hp->dfar[node] ) {
      swap(rc, node, hp->dfar, hp->skar); downheap(hp, rc, c);
    } else if ( (hp->dfar[rc] == hp->dfar[node]) && (hp->skar[rc] > hp->skar[node]) ) {
      swap(rc, node, hp->dfar, hp->skar); downheap(hp, rc, c);
    } else if ( (hp->dfar[lc] == hp->dfar[node]) && (hp->skar[lc] > hp->skar[node]) ) {
      swap(lc, node, hp->dfar, hp->skar); downheap(hp, lc, c);
    }
  } else {
    if ( (hp->dfar[lc] <= c) && (hp->skar[lc] > hp->skar[node]) && (hp->skar[lc] > hp->skar[rc]) ) {
      swap(lc, node, hp->dfar, hp->skar); downheap(hp, lc, c);
    } else if ( (hp->dfar[rc] <= c) && (hp->skar[rc] > hp->skar[node]) ) {
      swap(rc, node, hp->dfar, hp->skar); downheap(hp, rc, c);
    }
  }
}

int removeMax(Heap *hp, int c) {
  int n = hp->skar[1]; hp->front--;
  hp->skar[1] = hp->skar[hp->front];
  hp->dfar[1] = hp->dfar[hp->front];
  downheap(hp, 1, c);
  return n;
}

int replicate (short type, int c, Heap *Wh, Heap *Oh) {
  int n = 0;
  while ( 1 ) {
    if ( type ) {
      if ( (Wh->front == 1) || (c < Wh->dfar[1]) ) { break; }
      else { c += removeMax(Wh, c); n += 1; type = 0; }
    } else {
      if ( (Oh->front == 1) || (c < Oh->dfar[1])  ) { break; }
      else { c += removeMax(Oh, c); n += 1; type = 1; }
    }
  }
  return n;
}

void freeHeap(Heap h) {
  free(h.dfar); free(h.skar);
}

void paintingSteal(int N, int c) {
  
  int *df = safeMalloc(N * sizeof(int)), Wnum = 0, paintings = 0;
  short *type = safeMalloc(N * sizeof(short)), *sk = safeMalloc(N * sizeof(short));

  for (int i = 0; i < N; i++) {
    type[i] = readNumber(); Wnum += type[i];
    df[i] = readNumber(); sk[i] = readNumber();
  }

  Heap Wh = makeHeap(Wnum), Oh = makeHeap(N - Wnum);
  fillHeap(df, sk, type, N, c, &Wh, &Oh);
  short start = startPoint(c, Wnum, N - Wnum, &Wh, &Oh);

  if (start < 0) { printf("0\n"); freeHeap(Wh); freeHeap(Oh); return; }
  else if (start > 1) {
    int *Wdf = safeMalloc((Wnum + 1) * sizeof(int)), *Odf = safeMalloc((N - Wnum + 1) * sizeof(int));
    short *Wsk = safeMalloc((Wnum + 1) * sizeof(short)), *Osk = safeMalloc((N - Wnum + 1) * sizeof(int));
    
    copyHeap(Wdf, Odf, Wsk, Osk, &Wh, &Oh);
    paintings = replicate(0, c, &Wh, &Oh);
    recover(N, Wnum, Wdf, Odf, Wsk, Osk, &Wh, &Oh);    
    int temp = replicate(1, c, &Wh, &Oh);
    
    paintings = (temp > paintings) ? temp : paintings;
  } else { paintings = replicate(start, c, &Wh, &Oh); }

  printf("%d\n", paintings);

  freeHeap(Wh); freeHeap(Oh);
}