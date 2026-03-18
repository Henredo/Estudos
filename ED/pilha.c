#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct pilha{
    int stack[MAX], quantidade;

} pilha;

void iniciar_pilha(pilha *stack){
    pilha* novo = malloc(sizeof(pilha));
    stack = novo;
}

int read_stack(pilha *stack){
    for (int i = 0; i < stack->quantidade; i++){
        printf("\n%d",stack->stack[i]);
    }
    return 0;
}

int push(pilha *stack,int input){
    if (stack->quantidade >= MAX){
        printf("\nError : overflow");
        return 1;
    }
    else{
        stack->stack[stack->quantidade] = input;
        stack->quantidade++;
        return 0;
    }
       
}

int pop(pilha *stack){
    if (stack->quantidade <= 0){
        printf("\nError : underflow");
        return 1;
    }
    else{
        stack->quantidade--;
        stack->stack[stack->quantidade] = 0;
        //free(&stack->stack[stack->quantidade-1]);
    }
       
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