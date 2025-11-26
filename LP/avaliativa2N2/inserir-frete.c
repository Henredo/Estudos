#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float frete;
    int pedidos[100][4][3],pedidos_feitos,pedido_engravado[100];
}Distribuidora;

void main(int argc,char* argv[]){
    FILE *arquivo;
    Distribuidora distribuidoras[4];
    int input;
    arquivo = fopen("distribuidoras.dat","rb");
    if(arquivo != NULL){
        fread(distribuidoras, sizeof(Distribuidora), 4, arquivo);
    }
    fclose(arquivo);
    arquivo = fopen("distribuidoras.dat","wb");
    if (argc > 1){
        printf("Insira o novo frete :\n$ ");
        scanf(" %i",&input);
        distribuidoras[atoi(argv[1])].frete=input;
    }
    else{//para para inserir-frete seja executado sozinho, no qual vamos resetar distribuidoras.dat
        for(int i=0;i<4;i++){
            distribuidoras[i].pedidos_feitos=0;
            printf("Insira o Frete para a distribuidora %i :\n$ ",i+1);
            scanf(" %i",&input);
            distribuidoras[i].frete=input;
        }
        fwrite(distribuidoras, sizeof(Distribuidora), 4, arquivo);
    }
    fclose(arquivo);
}