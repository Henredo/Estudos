//todo
#include <stdio.h>
#include <string.h>
typedef struct stack
{
    char* string;
    int huggers[20], huggers_n;
} stack;

void iniciar_pilha(stack *input){
    stack* novo = malloc(sizeof(stack));
    input = novo;
}
int push(stack *stack,int input){
    if (stack->huggers_n >= 20){
        printf("\nError : overflow");
        return 1;
    }
    else{
        stack->huggers[stack->huggers_n] = input;
        stack->huggers_n++;
        return 0;
    }
       
}
int pop(stack *stack){
    if (stack->huggers_n <= 0){
        printf("\nError : underflow");
        return 1;
    }
    else{
        stack->huggers_n--;
        stack->huggers[stack->huggers_n] = 0;
    }
       
}

void add_huggers(stack *input){
    for (int i = 0; i < strlen(input->string); i++){
        switch (input->string[i])
        {
        case '(':
            push(input,1);
        break;
        
        case ')':
            pop(input);
            break;
        case '[':
            push(input,2);
            break;
        
        case ']':
            pop(input);
            break;
        
        
        case '{':
            push(input,3);
            break;
        
        case '}':
            pop(input);
            break;
        
        default:
            break;
        }
    }
    
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