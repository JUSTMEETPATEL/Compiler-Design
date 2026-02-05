#include <stdio.h>
#include <string.h>

int main() {
    char lhs, rhs[50];
    char alpha[20], beta[20];

    printf("Enter the production: ");
    scanf(" %c->%s", &lhs, rhs);

    // Split production at '|'
    char *part1 = strtok(rhs, "|");
    char *part2 = strtok(NULL, "|");

    // Check for left recursion
    if (part1[0] == lhs) {
        // alpha is remaining part after lhs
        strcpy(alpha, part1 + 1);
        strcpy(beta, part2);

        printf("\nThe productions after eliminating Left Recursion are:\n");
        printf("%c->%s%c'\n", lhs, beta, lhs);
        printf("%c'->%s%c'|ε\n", lhs, alpha, lhs);
    } else {
        printf("\nThe given grammar has no Left Recursion.\n");
    }

    return 0;
}
