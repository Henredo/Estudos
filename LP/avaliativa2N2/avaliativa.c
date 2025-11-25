#include <stdio.h>

typedef struct{
    float valor_unitario;
    int q_entregue,q_a_fabricar,q_deposito;
}BrindeInfo;

typedef struct{
    float frete;
    int pedidos[100][4][3],pedidos_feitos,pedido_engravado[100]; //pedidos = n_pedido / cor / tipo
}Distribuidora;

int main(){
    /*
    existem 4 pontos de distribuicao
    */
    BrindeInfo Dados[4][3]; //cor/tipo
    int escolha;
    /*pegar o valor do frete de cada ponto de distrubuicao e dados 
    da matriz dados (tentar usar arquivos/mas nao eh obrigatorio)*/
    
    //menu
    while(1==1){
        //print menu choice
        printf("Abrir menu de:\n[1]Fabricante.\n[2]Distribuidor.\n");
        scanf(" %i",&escolha);
        //print menu da escolha
        switch (escolha)
        {
        case 1:
            printf("Selecione a operação desejada\n[1]Fabricar.\n[2]Mostrar o que deve ser fabricado.\n[3]Relatório por brinde.\n[4]Relatório por cor.\n[5]Relatório de entregas.\n$ ");
            scanf(" %i",&escolha);
            switch (escolha)
            {
            case 1:
                /* code */
                break;
            
                case 2:
                /* code */
                break;
            
                case 3:
                /* code */
                break;
            
                case 4:
                /* code */
                break;
            
                case 5:
                /* code */
                break;
            
                default:
                break;
            }
            break;

        case 2:
            printf("Selecione a operação desejada\n[1]Solicitar entrega.\n[2]Status da distribuidora.\n[3]Editar frete.\n$ ");
            break;
        
        default:
        printf("deu ruim");
            break;
        }
        //switch case pra cada escolha do menu da escolha
        break;
    }
    return 0;
}

int fabricar(BrindeInfo Dados[][3], int cor, int tipo, int quantidade){
    /*Adiciona um determinado brinde no depósito. Deve ser implementado usando
    uma função que recebe como parâmetros o brinde a ser fabricado, a cor,
    a quantidade e outros parâmetros que achar necessários.
    Esta função deve retornar a quantidade atual deste brinde no depósito*/
    
    Dados[cor][tipo].q_deposito = Dados[cor][tipo].q_deposito + quantidade;
    //verificar se algum pedido pode ser atendido com outra funçao
    
    return Dados[cor][tipo].q_deposito;
}