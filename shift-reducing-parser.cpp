#include<iostream.h>
#include<string.h>
#include<conio.h>

struct grammar {
    char lhs;
    char rhs[10];
} g[10];

char stack[20], input[20];
int top = -1, n;

void push(char c) {
    stack[++top] = c;
    stack[top+1] = '\0';
}

char pop() {
    return stack[top--];
}

void main() {
    int i, j, k, len;
    char temp[20], start;

    clrscr();

    cout<<"Enter number of productions: ";
    cin>>n;

    for(i=0;i<n;i++) {
        cout<<"LHS of production "<<i+1<<": ";
        cin>>g[i].lhs;
        cout<<"RHS: ";
        cin>>g[i].rhs;
    }

    cout<<"Enter input string: ";
    cin>>input;

    start = g[0].lhs;
    len = strlen(input);
    input[len] = '$';
    input[len+1] = '\0';

    push('$');

    cout<<"\nStack\tInput\tAction\n";

    for(i=0;i<=len;i++) {
        push(input[i]);
        cout<<stack<<"\t"<<&input[i+1]<<"\tShift\n";

        // Check for reduce
        for(j=0;j<n;j++) {
            if(strstr(stack, g[j].rhs) != NULL) {
                int rlen = strlen(g[j].rhs);
                top -= rlen;
                push(g[j].lhs);
                cout<<stack<<"\t"<<&input[i+1]<<"\tReduce\n";
            }
        }
    }

    if(stack[1] == start && stack[2] == '\0')
        cout<<"\nString Accepted";
    else
        cout<<"\nString Rejected";

    getch();
}
