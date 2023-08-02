#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main(int argc, char *argv[]){
    char *path = argv[1];

    int n,topo;
    int *simetrica;
    int *pos_ordem;

    FILE *f = fopen(path,"r");
    fscanf(f,"%d",&n);
    topo = n-1;
    simetrica = calloc(n,sizeof(int));
    pos_ordem = calloc(n,sizeof(int));

    for(int i=0;i<n;i++)
        fscanf(f,"%d",&simetrica[i]);
    for(int i=0;i<n;i++)
        fscanf(f,"%d",&pos_ordem[i]);

    fclose(f);

    int maxSum = -1000000000;

    p_no tree;

    tree = montar_arvore(simetrica,pos_ordem,0,n-1,&topo);

    int soma = max_graos(tree,&maxSum);
    maxSum = (maxSum > soma) ? maxSum : soma;

    printf("%d\n",maxSum);

    free(simetrica);
    free(pos_ordem);

    destruir_arvore(tree);

    return 0;
}