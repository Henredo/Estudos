#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float valor_unitario;
    int q_entregue,q_a_fabricar,q_deposito;
}BrindeInfo;

typedef struct{
    float frete;
    int pedidos[100][4][3],pedidos_feitos,pedido_engravado[100],pedido_espera[100]; //pedidos = n_pedido / cor / tipo
}Distribuidora;

int fabricar(BrindeInfo Dados[][3], int cor, int tipo, int quantidade);
void mostrar_ser_fabricado(Distribuidora distribuidoras[],BrindeInfo Dados[][3]);
void relatorio_pbrinde(int brinde,BrindeInfo Dados[][3]);
void relatorio_pcor(int cor,BrindeInfo Dados[][3]);
void relatorio_entregas(BrindeInfo Dados[][3]);
int solicitar_entrega(int local,Distribuidora distribuidoras[4],BrindeInfo Dados[][3]);
int tentar_realizar_entrega(int local,Distribuidora distribuidoras[4],BrindeInfo Dados[][3]);
void status_distribuidora(int local,Distribuidora distribuidoras[]);
void inserir_dados();
void inserir_frete(int local);

int main(){
    BrindeInfo Dados[4][3]; //cor/tipo
    Distribuidora distribuidoras[4]={0};
    FILE *arq_distribuidoras,*arq_dados;
    arq_distribuidoras = fopen("distribuidoras.dat","rb");
    if(arq_distribuidoras == NULL){
        printf("\nArquivo [distribuidoras.dat] não encontrado\n");
        inserir_frete(-1);
    }
    fread(distribuidoras, sizeof(Distribuidora), 4, arq_distribuidoras);
    fclose(arq_distribuidoras);
    arq_dados = fopen("dados.dat","rb");
    if(arq_dados == NULL){
        printf("\nArquivo [dados.dat] não encontrado\n");
        inserir_dados();
    }
    int escolha;
    
    while(1==1){
       //print menu choice
       printf("\nAbrir menu de:\n[1]Fabricante.\n[2]Distribuidor.\n$ ");
       scanf(" %i",&escolha);
       //print menu da escolha
       switch (escolha)
       {
           case 1:
           printf("\nSelecione a operação desejada\n[1]Fabricar.\n[2]Mostrar o que deve ser fabricado.\n[3]Relatório por brinde.\n[4]Relatório por cor.\n[5]Relatório de entregas.\n$ ");
           scanf(" %i",&escolha);
           switch (escolha)
           {
               case 1:
               int escolha1,escolha2;
               printf("\nSelecione qual brinde deseja fabricar :\n[1]Caneta\n[2]Chaveiro\n[3]Régua\n$ ");
               scanf(" %i",&escolha1);
               printf("\nSelecione a cor do brinde :\n[1]Branca\n[2]Azul\n[3]Preta\n[4]Vermelho\n$ ");
               scanf(" %i",&escolha2);
               printf("\nInforme aquantidade a ser fabricada :\n$ ");
               scanf(" %i",&escolha);
               fabricar(Dados,escolha2,escolha1,escolha);
               for(int i=0;i<4;i++){
                    printf("\n%i\n",i);
                   tentar_realizar_entrega(i,distribuidoras,Dados);
                }
                break;
               
               case 2:
                mostrar_ser_fabricado(distribuidoras,Dados);
                break;

                case 3:
                printf("\nInsira o brinde que deseja conferir :\n[1]Caneta\n[2]Chaveiro\n[3]Régua\n$ ");
                scanf(" %i",&escolha);
                relatorio_pbrinde(escolha-1,Dados);
                break;
                
                case 4:
                printf("\nInsira a cor que deseja conferir :\n[1]Branca\n[2]Azul\n[3]Preta\n[4]Vermelho\n$ ");
                scanf(" %i",&escolha);
                relatorio_pbrinde(escolha-1,Dados);
                break;
                
                case 5:
                relatorio_entregas(Dados);
                break;
                
                default:
                break;
            }
            break;
            
            case 2:
            int local=0;
            printf("\nSelecione a distribuidora para fazer login :\n[1]Palmas\n[2]Gurupi\n[3]Goiania\n[4]Brasilia\n$ ");
            scanf(" %i",&local);
            local--;
            printf("\nSelecione a operação desejada\n[1]Solicitar entrega.\n[2]Status da distribuidora.\n[3]Editar frete.\n$ ");
            scanf(" %i",&escolha);
            switch (escolha)
            {
            case 1:
                solicitar_entrega(local,distribuidoras,Dados);
                tentar_realizar_entrega(local,distribuidoras,Dados);
                break;
            
            case 2:
                status_distribuidora(local,distribuidoras);
                break;
                
            case 3:
                inserir_frete(local);
                arq_distribuidoras = fopen("distribuidoras.dat","rb");
                if(arq_distribuidoras != NULL){
                    fread(distribuidoras, sizeof(Distribuidora), 4, arq_distribuidoras);
                    fclose(arq_distribuidoras);
                }
                break;
        break;
            default:
                break;
            }
            break;
            
            default:
            break;
        }
        
    }
    return 0;
}

int fabricar(BrindeInfo Dados[][3], int cor, int tipo, int quantidade){    
    Dados[cor][tipo].q_deposito = Dados[cor][tipo].q_deposito + quantidade;
    return Dados[cor][tipo].q_deposito;
}

void mostrar_ser_fabricado(Distribuidora distribuidoras[],BrindeInfo Dados[][3]){
    for(int i=0;i<4;i++){
        if(distribuidoras[i].pedido_espera==0){
            continue;
        }
        else{
            int fabricar[4][3];
            for(int x=0;x<4;x++){
                for(int y=0;y<3;y++){
                    fabricar[x][y]+=distribuidoras[i].pedidos[distribuidoras[i].pedidos_feitos][x][y];
                }
            }
            for(int x=0;x<4;x++){
                for(int y=0;y<3;y++){
                    printf("\nDevem ser fabricadas %i do brinde %i * %i",y+1,x+1);
                    if(Dados[x][y].q_deposito<50){
                        printf("\nEsse brinde tem menos de 50 unidades no estoque!");
                    }
                }
            }
        }
    }
}

void relatorio_pbrinde(int brinde,BrindeInfo Dados[][3]){
    for(int i=0;i<4;i++){
        printf("\nExistem %i brindes da cor %i no deposito nesse momento.",Dados[i][brinde].q_deposito,i+1);
    }
}

void relatorio_pcor(int cor,BrindeInfo Dados[][3]){
    for(int i=0;i<3;i++){
        printf("\nSerão nessessarios %i no deposito nesse momento.",Dados[cor][i].q_a_fabricar,i+1);
    }
}

void relatorio_entregas(BrindeInfo Dados[][3]){
    for(int i=0;i<4;i++){
        for(int n=0;n<3;n++){
            printf("\nJa foram entregues %i brindes %i de cor %i !",Dados[i][n].q_entregue,n,i);
        }
    }
}

int solicitar_entrega(int local,Distribuidora distribuidoras[4],BrindeInfo Dados[][3]){
    distribuidoras[local].pedido_espera[distribuidoras[local].pedidos_feitos]++;
    int Realizar=0;
    do
    {
        int tipo,cor,quantidade,arte=0;
        char escolha;
        printf("\nSelecione o brinde que quer pedir :\n[1]Caneta\n[2]Chaveiro\n[3]Régua\n$ ");
        scanf(" %i",&tipo);
        printf("\nSelecione a cor do brinde :\n[1]Branca\n[2]Azul\n[3]Preta\n[4]Vermelha\n$ ");
        scanf(" %i",&cor);
        printf("\nSelecione a quantidade a se pedir :\n$ ");
        scanf(" %i",&quantidade);
        printf("\nEsse pedido terá arte no(s) brinde(s) [S/N]\n$ ");
        scanf(" %c",&escolha);
        if(escolha == 's' || escolha == 'S'){
            arte++;
        }
        distribuidoras[local].pedidos[distribuidoras[local].pedidos_feitos][cor][tipo] = quantidade;
        printf("\nSelecione :\n[1]Realizar pedido.\n[2]Adicionar item ao pedido");
        scanf(" %i",&cor);
        if(cor == 1){
            Realizar++;
        }
        else{
            printf("\nDeve-se notar que tentar adicionar do mesmo tipo com cor ja no pedido irá sobrescrever o pedido original");
            Realizar = solicitar_entrega(local,distribuidoras,Dados);
        }
    } while (Realizar==0);
    distribuidoras[local].pedidos_feitos++;
    return Realizar;
}

int tentar_realizar_entrega(int local,Distribuidora distribuidoras[4],BrindeInfo Dados[][3]){
    if(distribuidoras[local].pedido_espera[distribuidoras[local].pedidos_feitos]==0){
        return 1;
    }
    int sucesso=0;
    for(int i=0;i<4;i++){
        for(int n=0;n<3;n++){
            if(distribuidoras[local].pedidos[distribuidoras[local].pedidos_feitos][i][n]>Dados[i][n].q_deposito){
                sucesso++;
            }
        }
    }
    if(sucesso<1){
        for(int i=0;i<4;i++){
            for(int n=0;n<3;n++){
                Dados[i][n].q_deposito-=distribuidoras[local].pedidos[distribuidoras[local].pedidos_feitos][i][n];
                Dados[i][n].q_entregue+=distribuidoras[local].pedidos[distribuidoras[local].pedidos_feitos][i][n];
            }
        }
        distribuidoras[local].pedido_espera[distribuidoras[local].pedidos_feitos]=0;
    }
    else{
        for(int i=0;i<4;i++){
            for(int n=0;n<3;n++){
                Dados[i][n].q_a_fabricar = distribuidoras[local].pedidos[distribuidoras[local].pedidos_feitos][i][n];
            }
        }
    }
    return 0;
}

void status_distribuidora(int local,Distribuidora distribuidoras[]){
    int espera=0;
    for(int i=0;i<distribuidoras[local].pedidos_feitos;i++){
        if(distribuidoras[local].pedido_espera[i]>0){
            espera++;
            printf("\nPedido [%i] em espera :",i);
            for(int x=0;x<4;x++){
                for(int y=0;y<3;y++){
                    printf("\nBrinde %i de cor %i : %i unidades",x,y,distribuidoras[local].pedidos[i][x][y]);
                }
            }
        }
    }
    if(espera==0){
        printf("\nEssa distribuidora não possui pedidos em espera");
    }
}

void inserir_frete(int local){
    FILE *arquivo;
    Distribuidora distribuidoras[4]={0};
    int input;
    arquivo = fopen("distribuidoras.dat","rb");
    if(arquivo != NULL){
        fread(distribuidoras, sizeof(Distribuidora), 4, arquivo);
    }
    fclose(arquivo);
    arquivo = fopen("distribuidoras.dat","wb");
    if (local >= 0){
        printf("\nInsira o novo frete :\n$ ");
        scanf(" %i",&input);
        distribuidoras[local].frete=input;
    }
    else{//para para inserir-frete seja executado sozinho, no qual vamos resetar distribuidoras.dat
        for(int i=0;i<4;i++){
            distribuidoras[i].pedidos_feitos=0;
            printf("\nInsira o Frete para a distribuidora %i :\n$ ",i+1);
            scanf(" %i",&input);
            distribuidoras[i].frete=input;
        }
        fwrite(distribuidoras, sizeof(Distribuidora), 4, arquivo);
    }
    fclose(arquivo);
}

void inserir_dados(){
    FILE *arquivo;
    BrindeInfo Dados[4][3]={0};
    int input;
    arquivo = fopen("dados.dat","rb");
    if(arquivo != NULL){
        fread(Dados, sizeof(BrindeInfo), 4 * 3, arquivo);
    }
    fclose(arquivo);
    arquivo = fopen("dados.dat","wb");
    
    for(int i=0;i<4;i++){
        for(int n=0;n<3;n++){
            Dados[i][n].q_a_fabricar=0;
            printf("\nInsira o valor para o brinde %i * %i:\n$ ",i+1,n+1);
            scanf(" %i",&input);
            Dados[i][n].valor_unitario=input;
            printf("\nInsira a quantidade em deposito para o brinde %i * %i:\n$ ",i+1,n+1);
            scanf(" %i",&input);
            Dados[i][n].q_deposito=input;
        }
    }
    fwrite(Dados, sizeof(BrindeInfo), 4 * 3, arquivo);
    fclose(arquivo);
}
