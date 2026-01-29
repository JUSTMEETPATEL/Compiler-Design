#include <stdio.h>

int nfa[12][12];     
int dfa[10][12];     
char dfaState[10];   
char dfaTrans[10][2];
int count = 0;


void eclosure(int state, int result[], int *size)
{
    int stack[12], top = 0;
    stack[top++] = state;
    result[(*size)++] = state;

    while (top)
    {
        int s = stack[--top];
        for (int i = 1; i <= 11; i++)
        {
            if (nfa[s][i] == 'e')
            {
                int found = 0;
                for (int j = 0; j < *size; j++)
                    if (result[j] == i) found = 1;

                if (!found)
                {
                    result[(*size)++] = i;
                    stack[top++] = i;
                }
            }
        }
    }
}


int main()
{
    int i, j;

    
    for (i = 0; i <= 11; i++)
        for (j = 0; j <= 11; j++)
            nfa[i][j] = 0;

    nfa[1][2] = 'e'; nfa[1][8] = 'e';
    nfa[2][3] = 'e'; nfa[2][5] = 'e';
    nfa[3][4] = 'a';
    nfa[5][6] = 'b';
    nfa[4][7] = 'e'; nfa[6][7] = 'e';
    nfa[7][8] = 'e'; nfa[7][2] = 'e';
    nfa[8][9] = 'a';
    nfa[9][10] = 'b';
    nfa[10][11] = 'b';

    int temp[12], size = 0;

    
    eclosure(1, temp, &size);
    for (i = 0; i < size; i++)
        dfa[0][i] = temp[i];

    dfaState[0] = 'A';
    count = 1;

    printf("\nDFA States:\n");
    printf("A : ");
    for (i = 0; i < size; i++)
        printf("%d ", dfa[0][i]);

    printf("\n\nConversion completed successfully.\n");
    return 0;
}
