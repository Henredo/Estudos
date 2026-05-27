#include "TLList.h"
#include<stdio.h>
#include <stdlib.h>

typedef struct _no{
    int info;
    struct _no *prox;
}TNo;

struct _list{
    TNo* inicio;
};
TNo* TNo_createNFill(int info){
    return NULL;
}

TLList* TLList_create(){
    TLList* nova = malloc(sizeof(TLList));
    if(nova != NULL){
        nova->inicio = NULL;
    }
    return nova;
}
/**
 * @return true|false caso não possa inserir na lista
 */
bool TLList_insert_begin(TLList* lista, int info){
    TNo* novo = malloc(sizeof(TNo));
    if(novo == NULL) 
        return false; 
    novo->info = info;
    novo->prox = lista->inicio;	
    lista->inicio = novo;
    return true;
}
bool TLList_insert_end(TLList* lista, int info){
       TNo* novo = malloc(sizeof(TNo));
    if(novo == NULL) 
        return false; 
    novo->info = info;
    novo->prox = NULL;
    if(lista->inicio == NULL)
        lista->inicio = novo;
    else{//a lista nao estah vazia
        TNo* aux = lista->inicio;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return true;
}
/**
 * Imprime a lista do início para o fim.
 */
void TLList_print(TLList* lista){
    TNo* aux = lista->inicio;
    while(aux!=NULL){
        printf("%d->", aux->info);
        aux = aux->prox;
    }
    putchar('\n');
}