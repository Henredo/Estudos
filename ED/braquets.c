#include <stdio.h>

typedef struct stack
{
    char* string;
    int huggers[20], huggers_n;
} stack;

void iniciar_pilha(stack *input){
    stack* novo = malloc(sizeof(stack));
    input = novo;
}

void add_huggers(stack *input){
    
}

void main(){
    //variaveis
    stack input;
    iniciar_pilha(&input);
    //input
    printf("Digite aqui : ");
    scanf(" %s",input.string);
    //whats
}