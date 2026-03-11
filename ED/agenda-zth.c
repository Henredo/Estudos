#include <stdio.h>
#include <stdlib.h>

typedef struct telefone {
    int ddd;
    int numero;
} telefone;

typedef struct contato {
    char nome[128];
    telefone numero;
} contato;

void escrever_agenda(contato agenda[100], int n_contatos);
void ler_agenda(contato agenda[100], int *n_contatos);

int main(){

    contato *agenda = malloc(100 * sizeof(contato));
    int n_contatos = 0;

    int on = 1;

    while (on)
    {
        int input = 0;

        printf("\n-----------------------------\n");
        printf("\nSelecione uma opcao :\n");
        printf("1) adicionar contato\n");
        printf("2) exibir contatos\n");
        printf("3) salvar para arquivo\n");
        printf("4) abrir um arquivo\n");
        printf("\nInput : ");

        scanf("%i", &input);

        printf("\n-----------------------------\n");

        switch (input)
        {

        case 1:

            printf("Digite o Nome do novo contato : ");
            scanf("%s", agenda[n_contatos].nome);

            printf("Digite o DDD do novo contato : ");
            scanf("%i", &agenda[n_contatos].numero.ddd);

            printf("Digite o numero do novo contato : ");
            scanf("%i", &agenda[n_contatos].numero.numero);

            n_contatos++;

            break;

        case 2:

            printf("\nLista de contatos:\n");

            for (int i = 0; i < n_contatos; i++)
            {
                printf("\nContato %i:\n", i + 1);
                printf("Nome : %s\n", agenda[i].nome);
                printf("Telefone : (%i) %i\n",
                       agenda[i].numero.ddd,
                       agenda[i].numero.numero);
            }

            printf("\nFim da lista\n");

            break;

        case 3:

            escrever_agenda(agenda, n_contatos);
            break;

        case 4:

            ler_agenda(agenda, &n_contatos);
            break;

        default:

            on = 0;
        }
    }
    printf("\nEncerrando...\n");
    free(agenda);
    return 0;
}

void escrever_agenda(contato agenda[100], int n_contatos){
    FILE *arquivo = fopen("agenda.dat", "wb");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    fwrite(&n_contatos, sizeof(int), 1, arquivo);
    fwrite(agenda, sizeof(contato), n_contatos, arquivo);
    fclose(arquivo);
    printf("Agenda salva com %i contatos.\n", n_contatos);
}

void ler_agenda(contato agenda[100], int *n_contatos){
    FILE *arquivo = fopen("agenda.dat", "rb");
    if (arquivo == NULL){
        printf("\nArquivo [agenda.dat] nao encontrado.\n");
        return;
    }
    fread(n_contatos, sizeof(int), 1, arquivo);
    fread(agenda, sizeof(contato), *n_contatos, arquivo);
    fclose(arquivo);
    printf("Agenda carregada com %i contatos.\n", *n_contatos);
}