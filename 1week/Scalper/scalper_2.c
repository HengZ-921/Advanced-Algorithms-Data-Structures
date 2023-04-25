#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int nreadNumber() {
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
  int num = atoi(line);
  free(line);
  return num;
}

int notmain() {

    int websiteNum = readNumber(), maxDate = 0, maxNum = 0, maxDay = 0;
    if (websiteNum <= 0) { printf("0 0\n"); return 0; }
    int dateArray[websiteNum * 2];
    
    for (int i = 0; i < websiteNum; i++) {
        dateArray[i * 2] = readNumber();
        dateArray[i * 2 + 1] = readNumber();
        if ( maxDate < dateArray[i * 2 + 1] ) { maxDate = dateArray[i * 2 + 1]; }
    }
    int sellArray[maxDate+1];
    for (int i = 0; i < maxDate+1; i++) { sellArray[i] = 0; }
    // for (int i = 0; i < maxDate+1; i++) { printf("%d ", sellArray[i] ); }
    // printf("\n\n");
    //for (int i = 0; i < websiteNum; i++) { printf("%d %d \n", dateArray[i * 2], dateArray[i * 2 + 1] ); }
    printf("%d Size: %ld\n\n",maxDate, sizeof(sellArray));
    for (int i = 0; i < websiteNum; i++) {
        for (int j = dateArray[i * 2]; j < dateArray[i * 2 + 1] + 1; j++) { sellArray[j] += 1; }
    }

    for (int i = 0; i < maxDate+1; i++) {
      // printf("%d ", sellArray[i] );
      if (maxNum < sellArray[i]) { maxNum = sellArray[i]; maxDay = i; }
    }
    printf("\n\n");
    printf("%d %d\n", maxDay, maxNum);

    return 0;
}