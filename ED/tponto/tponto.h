#ifndef PONTOH
#define PONTOH

typedef struct ponto ponto;

#include <stdio.h>
ponto* criar_ponto(float x, float y);
void deletar_ponto(ponto* old);
void print_ponto(ponto* p);
void editar_pontox(ponto* p, float novo_x);
void adquirir_xponto(ponto* alvo, float* ponteiro);
void adquirir_yponto(ponto* alvo, float* ponteiro);
float distancia_pontos(ponto* p1, ponto* p2);

#endif