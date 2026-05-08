#include <stdio.h>
#include "ex1.h"

typedef struct no {
    int valor;
    struct no *prox;
} No;
typedef struct pilha {
    No topo;
} Pilha;

void push(Pilha stack,int valor){
    
}