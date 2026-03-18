#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct pilha{
    int stack[MAX], quantidade;

} pilha;

int read_stack(pilha *stack){
    for (int i = 0; i < MAX; i++){
        printf("\n%d",stack->stack[i]);
    }
    return 0;
}

int push(pilha *stack,int input){
    
}

void main(){
    pilha teste;
    push(&teste,1);
    push(&teste,10);
    push(&teste,100);
    read_stack(&teste);
    pop(&teste);
    read_stack(&teste);
}