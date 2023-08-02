#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int max(int a, int b){
    return a > b ? a : b;
}

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

void read_pos_ondem(p_no raiz){
    if(raiz!=NULL){
        read_pos_ondem(raiz->esq);
        read_pos_ondem(raiz->dir);
        printf("%d ",raiz->data);
    }
}

int max_graos(p_no raiz,int *maxSum){
    if(raiz == NULL)return 0;
    
    int esq = max_graos(raiz->esq,maxSum);
    int dir = max_graos(raiz->dir,maxSum);
    
    int soma = max(max(raiz->data,raiz->data+esq+dir),max(raiz->data+esq,raiz->data+dir));

    *maxSum = max(*maxSum,soma);
    
    return max(raiz->data,max(raiz->data+esq,raiz->data+dir));
}

void destruir_arvore(p_no raiz){
    if(raiz == NULL)return;

    destruir_arvore(raiz->dir);
    destruir_arvore(raiz->esq);

    free(raiz);
}