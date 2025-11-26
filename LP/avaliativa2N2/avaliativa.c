#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float valor_unitario;
    int q_entregue,q_a_fabricar,q_deposito;
}BrindeInfo;

typedef struct{
    float frete;
    int pedidos[100][4][3],pedidos_feitos,pedido_engravado[100]; //pedidos = n_pedido / cor / tipo
}Distribuidora;
//prototipos
int fabricar(BrindeInfo Dados[][3], int cor, int tipo, int quantidade);

int main(){
   BrindeInfo Dados[4][3]; //cor/tipo
   Distribuidora distribuidoras[4];
   FILE *arq_distribuidoras;
   arq_distribuidoras = fopen("distribuidoras.dat","rb");
   if(arq_distribuidoras == NULL){
    printf("Arquivo [distribuidoras.dat] não encontrado\n");
    return 1;
   }
   fread(distribuidoras, sizeof(Distribuidora), 4, arq_distribuidoras);
   fclose(arq_distribuidoras);
   int escolha;
   /*pegar o valor do frete de cada ponto de distrubuicao e dados 
   da matriz dados (tentar usar arquivos/mas nao eh obrigatorio)*/
   
   //menu
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
               
               case 2:
                /* code */
                
                case 3:
                /* code */
                
                case 4:
                /* code */
                
                case 5:
                /* code */
                
                default:
                break;
            }
            
            case 2:
            printf("\nSelecione a operação desejada\n[1]Solicitar entrega.\n[2]Status da distribuidora.\n[3]Editar frete.\n$ ");
            break;
            
            default:
            break;
        }
        
    }
    return 0;
}

int fabricar(BrindeInfo Dados[][3], int cor, int tipo, int quantidade){    
    Dados[cor][tipo].q_deposito = Dados[cor][tipo].q_deposito + quantidade;
    //verificar se algum pedido pode ser atendido com outra funçao
    
    return Dados[cor][tipo].q_deposito;
}

void mostrar_ser_fabricado(){
    
}

void relatorio_pbrinde(){
    //
}

void relatorio_pcor(){
    //
}

void relatorio_entregas(){
    //
}

void solicitar_entrega(){
    //
}

void status_distribuidora(){
    //
}

void editar_frete(){
    //
}



//system("./frete.h %i",escolha);