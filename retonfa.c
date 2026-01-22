#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char re[20], t[10][10];
    int i, j, n, r = 0;

    printf("\nSIMULATION OF NFA\n*****************\n");

    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            t[i][j] = ' ';

    printf("\nEnter a regular expression: ");
    scanf("%s", re);
    n = strlen(re);

    for (i = 0; i < n; i++) {
        switch (re[i]) {

        case '|':
            t[r][r+1] = 'E';
            t[r+1][r+2] = re[i-1];
            t[r+2][r+5] = 'E';
            t[r][r+3] = 'E';
            t[r+3][r+4] = re[i+1];
            t[r+4][r+5] = 'E';
            r += 5;
            break;

        case '*':
            t[r-1][r] = 'E';
            t[r][r+1] = 'E';
            t[r][r+3] = 'E';
            t[r+1][r+2] = re[i-1];
            t[r+2][r+1] = 'E';
            t[r+2][r+3] = 'E';
            r += 3;
            break;

        case '+':
            t[r][r+1] = re[i-1];
            t[r+1][r] = 'E';
            r++;
            break;

        default:
            if (isalpha(re[i])) {
                t[r][r+1] = re[i];
                r++;
            }
        }
    }

    printf("\n ");
    for (i = 0; i <= r; i++)
        printf("%d ", i);

    printf("\n--------------------------------\n");

    for (i = 0; i <= r; i++) {
        for (j = 0; j <= r; j++)
            printf("%c ", t[i][j]);
        printf("| %d\n", i);
    }

    printf("\nStart state: 0");
    printf("\nFinal state: %d\n", r);

    return 0;
}
