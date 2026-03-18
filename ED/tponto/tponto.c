#include "tponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ponto{
    float x,y;
} ponto;

ponto* criar_ponto(float x, float y){
    ponto* novo = malloc(sizeof(ponto));
    if(novo){
        novo->x = x;
        novo->y = y;
    }
    return novo;
}

void deletar_ponto(ponto* old){
    free(old);
}

void print_ponto(ponto* p){
    printf("As coordenadas do ponto sao :\nx) %f\ny) %f\n", p->x, p->y);
}

void editar_pontox(ponto* p, float novo_x){
    p->x = novo_x;
}

void adquirir_xponto(ponto* alvo, float* ponteiro){
    *ponteiro = alvo->x;
}

void adquirir_yponto(ponto* alvo, float* ponteiro){
    *ponteiro = alvo->y;
}

float distancia_pontos(ponto* p1, ponto* p2){
    float difx = p1->x - p2->x;
    float dify = p1->y - p2->y;
    float diftotal = sqrt((difx * difx) + (dify * dify));
    return diftotal;
}