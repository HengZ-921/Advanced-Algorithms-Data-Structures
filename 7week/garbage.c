#include "garbage.h"

char *markPortals ( short n, short s, short t) {
  short i, k; char c, *vmarks = safeMalloc( n * sizeof(char) );
  for ( i = 0; i < n; i++ ) { vmarks[i] = 'm'; }
  for ( i = 0; i < s; i++ ) { scanf("%hd%c", &k, &c); vmarks[k] = 's'; }
  for ( i = 0; i < t; i++ ) { scanf("%hd%c", &k, &c); vmarks[k] = 't'; }
  return vmarks;
}

int **fillGraph ( int n, int s, int t, int m, char *vmarks ) {
  char c; short i, j, x = 0, y;
  int temp, **mPorts = safeMalloc(m * sizeof(int*));
  for ( i = 0; i < m; i++ ) {
    mPorts[i] = safeMalloc( m * sizeof(int) );
    mPorts[i][0] = 0; mPorts[i][m - 1] = 0;
  }
  for ( i = 1; i < m - 1; i++ ) { mPorts[0][i] = 0; mPorts[m - 1][i] = 0; }  
  for ( i = 0; i < n; i++ ) {
    y = 0;
    if ( vmarks[i] == 's' ) {
      for ( j = 0; j < n; j++ ){
        scanf("%d%c", &temp, &c);
        if ( vmarks[j] == 'm' ) { ++y; mPorts[0][y] += temp; } // s->m
        else if ( vmarks[j] == 't' ) { mPorts[0][m - 1] += temp; } // s->t
      }
    } else if ( vmarks[i] == 'm' ) {
      ++x;
      for ( j = 0; j < n; j++ ){
        scanf("%d%c", &temp, &c);
        if ( vmarks[j] == 'm' ) { ++y; mPorts[x][y] = temp; } // m->m
        else if ( vmarks[j] == 't' ) { mPorts[x][m - 1] += temp; } // m->t        
      }
    } else { for ( j = 0; j < n; j++ ){ scanf("%d%c", &temp, &c); } }
  }
  free(vmarks); return mPorts;
}

char BFS ( int **G, short m, short *prev ) {
  short u, v;
  char *visited = safeMalloc( m * sizeof(char)); visited[0] = 'y';
  for ( u = 1; u < m; u++) { visited[u] = 'n'; }
  Queue nb = newQueue(m); enqueue(0, &nb);
  while ( nb.back != nb.front ) {
    u = dequeue(&nb);
    for ( v = 0; v < m; v++) {
      if ( G[u][v] && visited[v] == 'n' ) {
        if ( v == m - 1 ) { prev[v] = u; free(visited); free(nb.array); return 'y'; }
        visited[v] = 'y'; prev[v] = u; enqueue(v, &nb);
      }
    }
  }
  free(visited); free(nb.array); return 'n';
}

void FordFulkerson ( int **G, short m ) {
  lint sum = G[0][m - 1], single; G[0][m - 1] = 0;
  short u, v, *prev = safeMalloc( m * sizeof(short));
  for (int i = 0; i < m; i++) { prev[i] = -1; }
  while ( BFS(G, m, prev) == 'y' ) {
    single = MAXLOAD; v = m - 1;
    while ( v > 0 ) { u = prev[v]; single = (single <= G[u][v]) ? single : G[u][v]; v = u; }
    v = m - 1;
    while ( v > 0 ) { u = prev[v]; G[v][u] += single; G[u][v] -= single; v = u; }
    sum += single;
  }
  for ( u = 0; u < m; u++ ) { free(G[u]); } free(G); free(prev);
  printf("%lld\n", sum);
}

void *safeMalloc(int n) {    
  void *a = malloc(n);
  if (a == NULL) {
    fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
    exit(EXIT_FAILURE);
  }
  return a;
}

/* based on queueTypeAndFunctions.c by Gerard Renardel, 31 January 2018 */

Queue newQueue (short s) {
  Queue q;
  q.array = safeMalloc(s*sizeof(short));
  q.back = 0; q.front = 0; q.size = s;
  return q;
}

void enqueue (short item, Queue *qp) {
  qp->array[qp->back] = item;
  qp->back = (qp->back + 1) % qp->size;
}

short dequeue (Queue *qp) {
  short item = qp->array[qp->front];
  qp->front = (qp->front + 1) % qp->size;
  return item;
}
