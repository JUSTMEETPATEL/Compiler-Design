#include <stdio.h>
#include <string.h>

int main() {
    char lhs;
    char rhs[50];
    char alpha[20], beta[20];
    char *part1;
    char *part2;

    printf("Enter the production: ");
    scanf(" %c->%s", &lhs, rhs);

    part1 = strtok(rhs, "|");
    part2 = strtok(NULL, "|");

    if (part1[0] == lhs) {
        strcpy(alpha, part1 + 1);
        strcpy(beta, part2);

        printf("\nThe productions after eliminating Left Recursion are:\n");
        printf("%c->%s%c'\n", lhs, beta, lhs);
        printf("%c'->%s%c'|e\n", lhs, alpha, lhs);
    } else {
        printf("\nThe given grammar has no Left Recursion.\n");
    }

    return 0;
}
