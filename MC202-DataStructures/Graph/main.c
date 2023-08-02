#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define INF 999999999

p_graph ler_arquivo(char *path){
    int n;
    FILE *f = fopen(path,"r");
    fscanf(f,"%d\n",&n);

    p_graph g = criar_grafo(n);

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            fscanf(f,"%d",&g->adj[i][j]);
        }
    }

    fclose(f);

    return g;
}

void printa_conponente(p_graph grafo,int components){
    for(int i = 0 ; i < grafo->n ; i++){
        if(grafo->dists[i].componente != components)continue;
        char x;
        x = i+'A';
        printf("P(%c) ",x);
    }
    printf("\n");
    for(int i = 0 ; i < grafo->n ; i++){
        if(grafo->dists[i].componente != components)continue;
        printf("D(%d) ",grafo->dists[i].distancia);
    }
    printf("\n");
}

int main(int argc,char **argv){
    char *path = (argc > 1) ? argv[1] : NULL;

    p_graph grafo = ler_arquivo(path);

    int components = 0;

    BFS(grafo,1,components);

    for(int i = 0 ; i < grafo->n ; i++){
        if(grafo->dists[i].distancia == INF){
            components++;
            BFS(grafo,i,components);
        }
    }

    int *visitados = calloc(grafo->n,sizeof(int));

    printa_conponente(grafo,0);

    DFS(grafo,1,visitados,0);

    for(int i = 0 ; i < grafo->n ; i++){
        if(visitados[i] == 0){
            printf("| ");
            DFS(grafo,i,visitados,0);
        }
    }
    printf("\n");

    for(int i = 0 ; i < grafo->n ; i++){
        visitados[i] = 0;
    }

    DFS(grafo,1,visitados,1);

    for(int i = 0 ; i < grafo->n ; i++){
        if(visitados[i] == 0){
            printf("| ");
            DFS(grafo,i,visitados,1);
        }
    }
    printf("\n");

    destruir_grafo(grafo);

    return 0;
}