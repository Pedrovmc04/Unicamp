#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

p_no montar_arvore(int *simetrica,int *pos_ordem,int l,int r,int *topo){
    int pos = -1;
    for(int i = l; i <= r ; i++){
        if(simetrica[i] == pos_ordem[*topo])pos = i;
    }

    if(pos == -1)return NULL;

    p_no new = malloc(sizeof(struct no));

    new->data = pos_ordem[*topo];

    *topo = *topo-1;

    new->dir = montar_arvore(simetrica,pos_ordem,pos+1,r,topo);
    new->esq = montar_arvore(simetrica,pos_ordem,l,pos-1,topo);

    return new;
}

void destruir_arvore(p_no raiz){
    if(raiz == NULL)return;

    destruir_arvore(raiz->dir);
    destruir_arvore(raiz->esq);

    free(raiz);
}

void read_pre_ordem(p_no raiz){
    if(raiz!=NULL){
        printf("%d ",raiz->data);
        read_pre_ordem(raiz->esq);
        read_pre_ordem(raiz->dir);
    }
}

void read_pos_ordem(p_no raiz){
    if(raiz!=NULL){
        read_pos_ordem(raiz->esq);
        read_pos_ordem(raiz->dir);
        printf("%d ",raiz->data);
    }
}

void read_inordem(p_no raiz){
    if(raiz!=NULL){
        read_inordem(raiz->esq);
        printf("%d ",raiz->data);
        read_inordem(raiz->dir);
    }
}