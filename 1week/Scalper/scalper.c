#include <stdio.h>
#include <stdlib.h>
#include "sort.h"


int main() {

    lint websiteNum = readNumber();
    if (websiteNum <= 0) { printf("0 0\n"); return 0; }
    lint dateArray[websiteNum * 2];
    char sellArray[websiteNum * 2];
    sortDate(websiteNum, dateArray, sellArray);
    findMax(websiteNum, dateArray, sellArray);

    return 0;
}