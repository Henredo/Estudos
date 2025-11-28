#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISTRIB 4
#define MAX_CORES 4
#define MAX_TIPOS 3
#define MAX_PEDIDOS 100

typedef struct {//formatação adicional comparado ao entregue na parte1
    float valor_unitario;
    int q_entregue;
    int q_a_fabricar;
    int q_deposito;
} BrindeInfo;

typedef struct {
    float frete;
    int pedidos[MAX_PEDIDOS][MAX_CORES][MAX_TIPOS]; // pedidos[index][cor][tipo]
    int pedidos_feitos;                             // quantos pedidos já criados/ultimo pedido feito
    int pedido_engravado[MAX_PEDIDOS];              // 0/1 por pedido
    int pedido_espera[MAX_PEDIDOS];                 // 0 = não em espera, 1 = em espera
} Distribuidora;

/* protótipos */
int fabricar(BrindeInfo Dados[][MAX_TIPOS], int cor, int tipo, int quantidade);
void mostrar_ser_fabricado(Distribuidora distribuidoras[], BrindeInfo Dados[][MAX_TIPOS]);
void relatorio_pbrinde(int brinde, BrindeInfo Dados[][MAX_TIPOS]);
void relatorio_pcor(int cor, BrindeInfo Dados[][MAX_TIPOS]);
void relatorio_entregas(BrindeInfo Dados[][MAX_TIPOS]);
int solicitar_entrega(int local, Distribuidora distribuidoras[], BrindeInfo Dados[][MAX_TIPOS]);
void tentar_realizar_entregas(int local, Distribuidora distribuidoras[], BrindeInfo Dados[][MAX_TIPOS]);
void status_distribuidora(int local, Distribuidora distribuidoras[]);
void inserir_dados();
void inserir_frete(int local);

int main() {
    BrindeInfo Dados[MAX_CORES][MAX_TIPOS] = {0}; // [cor][tipo]
    Distribuidora distribuidoras[MAX_DISTRIB];
    FILE *arq_distribuidoras = NULL, *arq_dados = NULL;

    memset(distribuidoras, 0, sizeof(distribuidoras));//bruxaria que zera arrays

    arq_distribuidoras = fopen("distribuidoras.dat", "rb");
    if (arq_distribuidoras == NULL) {
        printf("\nArquivo [distribuidoras.dat] não encontrado.\n Insira os valores iniciais para prosseguir.\n");
        inserir_frete(-1); // cria o arquivo com fretes iniciais
        arq_distribuidoras = fopen("distribuidoras.dat", "rb");
    }
    if (arq_distribuidoras != NULL) {
        fread(distribuidoras, sizeof(Distribuidora), MAX_DISTRIB, arq_distribuidoras);
        fclose(arq_distribuidoras);
    }
    arq_dados = fopen("dados.dat", "rb");
    if (arq_dados == NULL) {
        printf("\nArquivo [dados.dat] não encontrado. Insira os valores iniciais para prosseguir.\n");
        inserir_dados();
        arq_dados = fopen("dados.dat", "rb");
    }
    if (arq_dados != NULL) {
        fread(Dados, sizeof(BrindeInfo), MAX_CORES * MAX_TIPOS, arq_dados);
        fclose(arq_dados);
    }

    int escolha;
    while (1) {
        printf("\nAbrir menu de:\n[1]Fabricante.\n[2]Distribuidor.\n[0]Sair\n$ ");
        if (scanf(" %d", &escolha) != 1) break;
        switch (escolha) {
            case 1: {
                printf("\nSelecione a operação desejada\n[1]Fabricar.\n[2]Mostrar o que deve ser fabricado.\n[3]Relatório por brinde.\n[4]Relatório por cor.\n[5]Relatório de entregas.\n$ ");
                if (scanf(" %d", &escolha) != 1) { escolha = 0; }
                switch (escolha) {
                    case 1: {
                        int escolha1, escolha2, quant;
                        printf("\nSelecione qual brinde deseja fabricar :\n[1]Caneta\n[2]Chaveiro\n[3]Régua\n$ ");
                        scanf(" %d", &escolha1);
                        printf("\nSelecione a cor do brinde :\n[1]Branca\n[2]Azul\n[3]Preta\n[4]Vermelho\n$ ");
                        scanf(" %d", &escolha2);
                        printf("\nInforme a quantidade a ser fabricada :\n$ ");
                        scanf(" %d", &quant);
                        if (escolha1 >= 1 && escolha1 <= MAX_TIPOS && escolha2 >= 1 && escolha2 <= MAX_CORES && quant > 0) {
                            fabricar(Dados, escolha2-1, escolha1-1, quant);
                            for (int i = 0; i < MAX_DISTRIB; i++) {
                                tentar_realizar_entregas(i, distribuidoras, Dados);
                            }
                        } else {
                            printf("Entrada inválida.\n");
                        }
                    } break;

                    case 2:
                        mostrar_ser_fabricado(distribuidoras, Dados);
                        break;

                    case 3: {
                        printf("\nInsira o brinde que deseja conferir :\n[1]Caneta\n[2]Chaveiro\n[3]Régua\n$ ");
                        scanf(" %d", &escolha);
                        if (escolha >= 1 && escolha <= MAX_TIPOS) relatorio_pbrinde(escolha-1, Dados);
                        else printf("Opção inválida.\n");
                    } break;

                    case 4: {
                        printf("\nInsira a cor que deseja conferir :\n[1]Branca\n[2]Azul\n[3]Preta\n[4]Vermelho\n$ ");
                        scanf(" %d", &escolha);
                        if (escolha >= 1 && escolha <= MAX_CORES) relatorio_pcor(escolha-1, Dados);
                        else printf("Opção inválida.\n");
                    } break;

                    case 5:
                        relatorio_entregas(Dados);
                        break;

                    default:
                        break;
                }
            } break;

            case 2: {
                int local = 0;
                printf("\nSelecione a distribuidora para fazer login :\n[1]Palmas\n[2]Gurupi\n[3]Goiania\n[4]Brasilia\n$ ");
                scanf(" %d", &local);
                if (local < 1 || local > MAX_DISTRIB) {
                    printf("Distribuidora inválida.\n");
                    break;
                }
                local--;
                printf("\nSelecione a operação desejada\n[1]Solicitar entrega.\n[2]Status da distribuidora.\n[3]Editar frete.\n$ ");
                scanf(" %d", &escolha);
                switch (escolha) {
                    case 1:
                        solicitar_entrega(local, distribuidoras, Dados);
                        tentar_realizar_entregas(local, distribuidoras, Dados);
                        break;

                    case 2:
                        status_distribuidora(local, distribuidoras);
                        break;

                    case 3:
                        inserir_frete(local);
                        /* recarrega arquivo de distribuidoras */
                        arq_distribuidoras = fopen("distribuidoras.dat", "rb");
                        if (arq_distribuidoras != NULL) {
                            fread(distribuidoras, sizeof(Distribuidora), MAX_DISTRIB, arq_distribuidoras);
                            fclose(arq_distribuidoras);
                        }
                        break;

                    default:
                        break;
                }
            } break;

            case 0:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida.\n");
                break;
        }
    }

    return 0;
}

int fabricar(BrindeInfo Dados[][MAX_TIPOS], int cor, int tipo, int quantidade) {
    Dados[cor][tipo].q_deposito += quantidade;
    if (Dados[cor][tipo].q_a_fabricar > 0) {
        Dados[cor][tipo].q_a_fabricar -= quantidade;
        if (Dados[cor][tipo].q_a_fabricar < 0) Dados[cor][tipo].q_a_fabricar = 0;
    }
    return Dados[cor][tipo].q_deposito;
}

void mostrar_ser_fabricado(Distribuidora distribuidoras[], BrindeInfo Dados[][MAX_TIPOS]) {
    int fabricar[MAX_CORES][MAX_TIPOS] = {0};
    int any = 0;//tem pedidos em espera? 0=N

    for (int i = 0; i < MAX_DISTRIB; i++) {
        for (int n = 0; n < distribuidoras[i].pedidos_feitos; n++) {
            if (distribuidoras[i].pedido_espera[n] == 1) {
                any = 1;
                for (int x = 0; x < MAX_CORES; x++) {
                    for (int y = 0; y < MAX_TIPOS; y++) {
                        fabricar[x][y] += distribuidoras[i].pedidos[n][x][y];
                    }
                }
            }
        }
    }

    if (!any) {
        printf("\nNão há pedidos em espera.\n");
        return;
    }

    for (int x = 0; x < MAX_CORES; x++) {
        for (int y = 0; y < MAX_TIPOS; y++) {
            if (fabricar[x][y] > 0) {
                printf("\nDevem ser fabricadas %d unidades do brinde tipo %d na cor %d.", fabricar[x][y], y + 1, x + 1);
                if (Dados[x][y].q_deposito < 50) {
                    printf(" (Atenção: estoque atual = %d < 50!)", Dados[x][y].q_deposito);
                }
            }
        }
    }
}

void relatorio_pbrinde(int brinde, BrindeInfo Dados[][MAX_TIPOS]) {
    if (brinde < 0 || brinde >= MAX_TIPOS) {
        printf("Brinde inválido.\n");
        return;
    }
    for (int i = 0; i < MAX_CORES; i++) {
        printf("\nExistem %d brindes do tipo %d na cor %d no depósito neste momento.", Dados[i][brinde].q_deposito, brinde + 1, i + 1);
    }
}

void relatorio_pcor(int cor, BrindeInfo Dados[][MAX_TIPOS]) {
    if (cor < 0 || cor >= MAX_CORES) {
        printf("Cor inválida.\n");
        return;
    }
    for (int i = 0; i < MAX_TIPOS; i++) {
        printf("\nSerão necessarios fabricar %d unidades do tipo %d para a cor %d (q_a_fabricar).", Dados[cor][i].q_a_fabricar, i + 1, cor + 1);
    }
}

void relatorio_entregas(BrindeInfo Dados[][MAX_TIPOS]) {
    for (int i = 0; i < MAX_CORES; i++) {
        for (int i = 0; i < MAX_TIPOS; i++) {
            printf("\nJá foram entregues %d unidades do tipo %d na cor %d.", Dados[i][i].q_entregue, i + 1, i + 1);
        }
    }
}

int solicitar_entrega(int local, Distribuidora distribuidoras[], BrindeInfo Dados[][MAX_TIPOS]) {
    if (local < 0 || local >= MAX_DISTRIB) return -1;
    int pedidos_feitos = distribuidoras[local].pedidos_feitos;
    if (pedidos_feitos >= MAX_PEDIDOS) {
        printf("Limite de pedidos atingido.\n");
        return -1;
    }
    for (int x = 0; x < MAX_CORES; x++)//zera o novo pedido que vai ser feito
        for (int y = 0; y < MAX_TIPOS; y++)
            distribuidoras[local].pedidos[pedidos_feitos][x][y] = 0;
    distribuidoras[local].pedido_engravado[pedidos_feitos] = 0;
    distribuidoras[local].pedido_espera[pedidos_feitos] = 0;
    printf("\nCriando novo pedido (Distribuidora %d). Para encerrar, selecione realizar pedido.\n", local + 1);
    while (1) {
        int tipo, cor, quantidade;
        char escolhaChar;
        printf("\nSelecione o brinde que quer pedir :\n[1]Caneta\n[2]Chaveiro\n[3]Régua\n$ ");
        if (scanf(" %d", &tipo) != 1) { printf("Entrada inválida.\n"); return -1; }
        printf("\nSelecione a cor do brinde :\n[1]Branca\n[2]Azul\n[3]Preta\n[4]Vermelha\n$ ");
        scanf(" %d", &cor);
        printf("\nSelecione a quantidade a se pedir :\n$ ");
        scanf(" %d", &quantidade);
        distribuidoras[local].pedidos[pedidos_feitos][cor - 1][tipo - 1] += quantidade;
        printf("\nEsse pedido terá arte no(s) brinde(s) [S/N]\n$ ");
        scanf(" %c", &escolhaChar);
        if (escolhaChar == 's' || escolhaChar == 'S') {
            distribuidoras[local].pedido_engravado[pedidos_feitos] = 1;
        }
        printf("\nSelecione :\n[1]Realizar pedido.\n[2]Adicionar outro item ao pedido\n$ ");
        int opt;
        scanf(" %d", &opt);
        if (opt == 1) {
            distribuidoras[local].pedido_espera[pedidos_feitos] = 1;
            distribuidoras[local].pedidos_feitos++;
            printf("Pedido criado (índice %d) e colocado em espera.\n", pedidos_feitos);//temporario, vai ver se continua em tentar)realizar_entrega()
            break;
        } else {
            printf("Item adicionado. Continue adicionando.\n");
        }
    }
    //atualiza o distribuidoras.dat reescrevendo tudo com as novas infos
    FILE *arquivo = fopen("distribuidoras.dat", "wb");
    fwrite(distribuidoras, sizeof(Distribuidora), MAX_DISTRIB, arquivo);
    fclose(arquivo);
    return 1;
}

void tentar_realizar_entregas(int local, Distribuidora distribuidoras[], BrindeInfo Dados[][MAX_TIPOS]) {
    if (local < 0 || local >= MAX_DISTRIB) return;
    for (int i = 0; i < distribuidoras[local].pedidos_feitos; i++) {
        if (distribuidoras[local].pedido_espera[i] == 0) continue;
        int faltou = 0;
        for (int x = 0; x < MAX_CORES; x++) {
            for (int y = 0; y < MAX_TIPOS; y++) {
                if (distribuidoras[local].pedidos[i][x][y] > Dados[x][y].q_deposito) {
                    faltou = 1;
                }
            }
        }
        if (!faltou) {
            float preco_total = 0.0;
            for (int x = 0; x < MAX_CORES; x++) {
                for (int y = 0; y < MAX_TIPOS; y++) {
                    if (distribuidoras[local].pedidos[i][x][y] > 0) {
                        Dados[x][y].q_deposito -= distribuidoras[local].pedidos[i][x][y];
                        Dados[x][y].q_entregue += distribuidoras[local].pedidos[i][x][y];
                        preco_total += distribuidoras[local].pedidos[i][x][y] * Dados[x][y].valor_unitario;
                    }
                }
            }
            if (distribuidoras[local].pedido_engravado[i]) preco_total += 100.0;
            preco_total += distribuidoras[local].frete;
            distribuidoras[local].pedido_espera[i] = 0;
            printf("\nPedido %d da distribuidora %d realizado com sucesso. Total = R$ %.2f\n", i, local + 1, preco_total);//.2f é 2 digitos depois da,
        } else {
            for (int x = 0; x < MAX_CORES; x++) {
                for (int y = 0; y < MAX_TIPOS; y++) {
                    int falta = distribuidoras[local].pedidos[i][x][y] - Dados[x][y].q_deposito;
                    if (falta > 0) Dados[x][y].q_a_fabricar += falta;
                }
            }
            printf("\nPedido %d da distribuidora %d permanece em espera (estoque insuficiente).\n", i, local + 1);
        }
    }

    FILE *f = fopen("distribuidoras.dat", "wb");
    if (f) {
        fwrite(distribuidoras, sizeof(Distribuidora), MAX_DISTRIB, f);
        fclose(f);
    }
    FILE *g = fopen("dados.dat", "wb");
    if (g) {
        fwrite(Dados, sizeof(BrindeInfo), MAX_CORES * MAX_TIPOS, g);
        fclose(g);
    }
}

void status_distribuidora(int local, Distribuidora distribuidoras[]) {
    if (local < 0 || local >= MAX_DISTRIB) {
        printf("Distribuidora inválida.\n");
        return;
    }
    int espera = 0;
    for (int i = 0; i < distribuidoras[local].pedidos_feitos; i++) {
        if (distribuidoras[local].pedido_espera[i] > 0) {
            espera++;
            printf("\nPedido [%d] em espera :", i);
            for (int x = 0; x < MAX_CORES; x++) {
                for (int y = 0; y < MAX_TIPOS; y++) {
                    if (distribuidoras[local].pedidos[i][x][y] > 0)
                        printf("\n  Brinde tipo %d de cor %d : %d unidades", y + 1, x + 1, distribuidoras[local].pedidos[i][x][y]);
                }
            }
            if (distribuidoras[local].pedido_engravado[i]) printf("\n  (Com gravação)");
        }
    }
    if (espera == 0) {
        printf("\nEssa distribuidora não possui pedidos em espera\n");
    }
}

void inserir_frete(int local) {
    FILE *arquivo = fopen("distribuidoras.dat", "rb");
    Distribuidora distribuidoras[MAX_DISTRIB] = {0};

    if (arquivo != NULL) {
        fread(distribuidoras, sizeof(Distribuidora), MAX_DISTRIB, arquivo);
        fclose(arquivo);
    }

    if (local >= 0 && local < MAX_DISTRIB) {
        int input;
        char inputchar;
        printf("O frete atual é : %iR$\nDeseja edita-lo? [S/N]\n$ ");
        scanf(" %c",&inputchar);
        if(inputchar=='N'||inputchar=='n')return;
        printf("\nInsira o novo frete para a distribuidora %d :\n$ ", local + 1);
        if (scanf(" %d", &input) == 1) distribuidoras[local].frete = (float)input;
    } else {
        int input;
        for (int i = 0; i < MAX_DISTRIB; i++) {
            distribuidoras[i].pedidos_feitos = 0;
            printf("\nInsira o Frete para a distribuidora %i :\n$ ", i + 1);
            if (scanf(" %d", &input) == 1) distribuidoras[i].frete = (float)input;
        }
    }

    arquivo = fopen("distribuidoras.dat", "wb");
    if (arquivo != NULL) {
        fwrite(distribuidoras, sizeof(Distribuidora), MAX_DISTRIB, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao gravar distribuidoras.dat\n");
    }
}

void inserir_dados() {
    FILE *arquivo = fopen("dados.dat", "rb");
    BrindeInfo Dados[MAX_CORES][MAX_TIPOS];
    memset(Dados, 0, sizeof(Dados));

    if (arquivo != NULL) {
        fread(Dados, sizeof(BrindeInfo), MAX_CORES * MAX_TIPOS, arquivo);
        fclose(arquivo);
    }

    arquivo = fopen("dados.dat", "wb");
    if (arquivo == NULL) {
        printf("Não foi possível abrir/crear dados.dat para escrita.\n");
        return;
    }

    int inputInt;
    float inputFloat;
    for (int x = 0; x < MAX_CORES; x++) {
        for (int y = 0; y < MAX_TIPOS; y++) {
            Dados[x][y].q_a_fabricar = 0;
            Dados[x][y].q_entregue = 0;
            Dados[x][y].q_deposito = 0;
            printf("\nInsira o VALOR UNITARIO para o brinde cor %d * tipo %d (ex: 2.50):\n$ ", x + 1, y + 1);
            if (scanf(" %f", &inputFloat) == 1) Dados[x][y].valor_unitario = inputFloat;
            else Dados[x][y].valor_unitario = 0.0f;

            printf("\nInsira a QUANTIDADE em deposito para o brinde cor %d * tipo %d:\n$ ", x + 1, y + 1);
            if (scanf(" %d", &inputInt) == 1) Dados[x][y].q_deposito = inputInt;
            else Dados[x][y].q_deposito = 0;
        }
    }

    fwrite(Dados, sizeof(BrindeInfo), MAX_CORES * MAX_TIPOS, arquivo);
    fclose(arquivo);
    printf("Dados dos brindes gravados em dados.dat\n");
}
