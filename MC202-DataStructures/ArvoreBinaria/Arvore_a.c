#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

void arvore_simetrica(p_no raiz){
    if(raiz == NULL)return;
    arvore_simetrica(raiz->esq);
    arvore_simetrica(raiz->dir);

    p_no aux = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = aux;
}

int main(int argc, char **argv){
    char *path = argv[1];
    
    int n;
    int *simetrica,*pos_ordem;

    FILE *f = fopen(path,"r");
    fscanf(f, "%d\n",&n);
    simetrica = calloc(n,sizeof(int));
    pos_ordem = calloc(n,sizeof(int));

    for(int i=0;i<n;i++)
        fscanf(f,"%d",&simetrica[i]);
    for(int i=0;i<n;i++)
        fscanf(f,"%d",&pos_ordem[i]);

    fclose(f);

    n--;

    p_no tree = montar_arvore(simetrica,pos_ordem,0,n,&n);

    arvore_simetrica(tree);

    read_pre_ordem(tree);
    printf("\n");
    read_inordem(tree);
    printf("\n");
    read_pos_ordem(tree);
    
    destruir_arvore(tree);
    free(simetrica);
    free(pos_ordem);

    return 0;
}