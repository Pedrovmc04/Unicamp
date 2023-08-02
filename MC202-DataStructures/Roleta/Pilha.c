#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"


p_pilha criar_pilha(){
    p_pilha p = malloc(sizeof(struct pilha));
    p->topo = NULL;
    return p;
}

int destruir_pilha(p_pilha p){
    int soma = 0;
    while(p->topo != NULL){
        p_no topo= p->topo;
        soma += p->topo->data;
        p->topo = p->topo->next;
        free(topo);
    }

    free(p);

    return soma;	
}

void inserir_pilha(p_pilha p,int x){
    p_no new = malloc(sizeof(struct no));
    new->data = x;
    new->next = p->topo;
    p->topo = new;
}

void remover_pilha(p_pilha p){
    p_no topo = p->topo;
    p->topo = p->topo->next;
    free(topo);
}