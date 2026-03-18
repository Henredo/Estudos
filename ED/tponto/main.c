#include "tponto.h"
#include <stdio.h>
int main(){
    ponto *ponto1 = criar_ponto(0.2, 2.5);
    print_ponto(ponto1);
    editar_pontox(ponto1, 2.0);
    print_ponto(ponto1);
    float local_x;
    adquirir_xponto(ponto1, &local_x);
    printf("Valor recuperado de x: %f\n", local_x);

    ponto* p2 = criar_ponto(3, 5);
    printf("A distancia eh: %f\n", distancia_pontos(ponto1, p2));
    deletar_ponto(ponto1);
    return 0;
}