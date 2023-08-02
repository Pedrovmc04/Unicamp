#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int IPL(p_no raiz,int dist){
    if(raiz == NULL)return 0;
    int soma = 0;

    soma += IPL(raiz->esq,dist+1);
    soma += IPL(raiz->dir,dist+1);

    return soma+dist;
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

    printf("%d\n",IPL(tree,0));
    
    destruir_arvore(tree);
    free(simetrica);
    free(pos_ordem);

    return 0;
}