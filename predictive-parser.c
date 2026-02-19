#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define MAXSTACK 50
#define MAXIN    100

/* Nonterminals (5) and Terminals (6) */
char NT[5] = { 'E', 'R', 'T', 'S', 'F' };
char Tm[6] = { 'x', '+', '*', '(', ')', '$' };

/* Parsing Table: [NonTerminal][Terminal] -> production RHS string */
char *table[5][6] = {
    /* E */ { "TR",  NULL,  NULL,  "TR",  NULL,  NULL },
    /* R */ {  NULL, "+TR", NULL,  NULL,  "@",   "@"  },
    /* T */ { "FS",  NULL,  NULL,  "FS",  NULL,  NULL },
    /* S */ {  NULL, "@",   "*FS", NULL,  "@",   "@"  },
    /* F */ { "x",   NULL,  NULL,  "(E)", NULL,  NULL }
};

struct Stack {
    char data[MAXSTACK];
    int top;
};

void push(struct Stack *s, char ch) {
    if (s->top >= MAXSTACK - 2) return;
    s->data[++s->top] = ch;
    s->data[s->top + 1] = '\0';
}

char pop(struct Stack *s) {
    char ch;
    if (s->top < 0) return '\0';
    ch = s->data[s->top];
    s->data[s->top--] = '\0';
    return ch;
}

char peek(struct Stack *s) {
    if (s->top < 0) return '\0';
    return s->data[s->top];
}

int is_terminal(char ch) {
    int i;
    for (i = 0; i < 6; i++) if (Tm[i] == ch) return 1;
    return 0;
}

int nt_index(char ch) {
    int i;
    for (i = 0; i < 5; i++) if (NT[i] == ch) return i;
    return -1;
}

/* Map raw input char to terminal column:
   letters/digits => x, else use the symbol itself (+,*,(,),$) */
int term_col(char ch) {
    int i;
    if (isalnum((unsigned char)ch)) ch = 'x';
    for (i = 0; i < 6; i++) if (Tm[i] == ch) return i;
    return -1;
}

/* Push RHS to stack in reverse order, ignoring epsilon '@' */
void push_rhs_reverse(struct Stack *s, const char *rhs) {
    int len, i;
    if (rhs == NULL) return;
    if (rhs[0] == '@' && rhs[1] == '\0') return;

    len = strlen(rhs);
    for (i = len - 1; i >= 0; i--) {
        push(s, rhs[i]);
    }
}

void print_table(void) {
    int i, j;
    clrscr();
    printf("PARSING TABLE (LL(1))\n\n");
    printf("      ");
    for (j = 0; j < 6; j++) printf("%c     ", Tm[j]);
    printf("\n");

    for (i = 0; i < 5; i++) {
        printf(" %c :  ", NT[i]);
        for (j = 0; j < 6; j++) {
            if (table[i][j] == NULL) printf("err   ");
            else printf("%-5s", table[i][j]);
        }
        printf("\n");
    }
    printf("\nGrammar uses @ as epsilon.\n\n");
}

void main(void) {
    struct Stack st;
    char input[MAXIN];
    char mapped;          /* current input symbol mapped to terminal */
    int ip = 0;           /* input pointer */
    int err = 0;

    st.top = -1;
    st.data[0] = '\0';

    print_table();

    printf("Enter input string (use letters/digits for id, e.g. a+a*a): ");
    scanf("%s", input);

    /* Append $ to input */
    strcat(input, "$");

    /* Initialize stack with $E */
    push(&st, '$');
    push(&st, 'E');

    printf("\nBehavior of parser:\n");
    printf("\n%-20s %-20s %-20s\n", "STACK", "INPUT", "OUTPUT");

    while (!err) {
        char top = peek(&st);
        char in  = input[ip];

        /* map in to terminal set (alnum => x) for table lookup / matching */
        mapped = in;
        if (isalnum((unsigned char)mapped)) mapped = 'x';

        /* print current state */
        printf("%-20s %-20s ", st.data, &input[ip]);

        if (top == '$' && mapped == '$') {
            printf("%-20s\n", "accept");
            break;
        }

        if (is_terminal(top) || top == '$') {
            /* terminal match */
            if (top == mapped) {
                pop(&st);
                ip++; /* consume one input char */
                printf("%-20s\n", "match");
            } else {
                printf("%-20s\n", "error");
                err = 1;
            }
        } else {
            /* nonterminal: use table */
            int r = nt_index(top);
            int c = term_col(in); /* use raw input, term_col will map alnum to x */

            if (r < 0 || c < 0 || table[r][c] == NULL) {
                printf("%-20s\n", "error");
                err = 1;
            } else {
                char *rhs = table[r][c];
                pop(&st);
                push_rhs_reverse(&st, rhs);

                /* show production applied */
                {
                    char outbuf[30];
                    strcpy(outbuf, "");
                    sprintf(outbuf, "%c->%s", NT[r], rhs);
                    printf("%-20s\n", outbuf);
                }
            }
        }
    }

    if (err) {
        printf("\nThe string is NOT accepted.\n");
    } else {
        printf("\nThe string IS accepted.\n");
    }

    getch();
}