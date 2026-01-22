#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[])
{
    char keywords[32][10] = {
        "auto","break","case","char","const","continue","default",
        "do","double","else","enum","extern","float","for","goto",
        "if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union",
        "unsigned","void","volatile","while"
    };

    for (int i = 0; i < 32; i++)
    {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}

int main(void)
{
    char ch, buffer[20];
    char operators[] = "+-*/%=";
    FILE *fp;
    int i, j = 0;

    fp = fopen("program.txt", "r");
    if (fp == NULL)
    {
        printf("Error while opening the file\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF)
    {

        for (i = 0; i < 6; i++)
        {
            if (ch == operators[i])
                printf("%c is operator\n", ch);
        }


        if (isalnum(ch))
        {
            if (j < 19)   
                buffer[j++] = ch;
        }
        else if ((ch == ' ' || ch == '\n' || ch == '\t') && j != 0)
        {
            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer))
                printf("%s is keyword\n", buffer);
            else
                printf("%s is identifier\n", buffer);
        }
    }

    
    if (j != 0)
    {
        buffer[j] = '\0';
        if (isKeyword(buffer))
            printf("%s is keyword\n", buffer);
        else
            printf("%s is identifier\n", buffer);
    }

    fclose(fp);
    return 0;
}
