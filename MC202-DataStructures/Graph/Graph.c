#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

p_queue criar_queue(){
    p_queue new = malloc(sizeof(struct queue));
    new->ini = NULL;
    new->fim = NULL;
    return new;
}

void inserir_queue(p_queue queue,int x){
    p_no new = malloc(sizeof(struct no));
    new->data = x;
    new->next = NULL;
    if(queue->ini == NULL){
        queue->ini = new;
    }else{
        queue->fim->next = new;
    }
    queue->fim = new;
}

int extrair_queue(p_queue queue){
    if(queue->ini == NULL)return -1;

    p_no temp = queue->ini;
    int extraido = queue->ini->data;
    queue->ini = queue->ini->next;
    free(temp);
    
    return extraido;
}

p_graph criar_grafo(int tam){
    p_graph new = calloc(1, sizeof(struct graph));
    new->n = tam;
    new->dists = calloc(tam,sizeof(struct dist));
    new->adj = calloc(tam,sizeof(int*));
    for(int i = 0 ; i < tam; i++){
        new->dists[i].distancia = INF;
        new->adj[i] = calloc(tam,sizeof(int));
    }

    return new;
}

void destruir_grafo(p_graph grafo){
    for(int i = 0 ; i < grafo->n ; i++){
        free(grafo->adj[i]);
    }
    free(grafo->adj);
    free(grafo);
}

void printa_listAdj(p_graph grafo){
    for(int i = 0 ; i < grafo->n ; i++){
        for(int j = 0 ; j < grafo->n ; j++){
            printf("%d ",grafo->adj[i][j]);
        }
        printf("\n");
    }
}

void BFS(p_graph grafo,int no,int component){
    p_queue fila = criar_queue();
    int *dist = calloc(grafo->n,sizeof(int));

    for(int i = 0 ; i < grafo->n ; i++)
        dist[i] = (i != no) ? INF : 0;

    inserir_queue(fila,no);

    while(fila->ini != NULL){
        int u = extrair_queue(fila);

        for(int i = 0 ; i < grafo->n ; i++){
            if(grafo->adj[u][i] == 0)continue;
            if(dist[i] > dist[u]+1){
                dist[i] = dist[u]+1;
                inserir_queue(fila,i);
            }
        }
    }

    for(int i = 0 ; i < grafo->n ; i++){
        if(dist[i] == INF)continue;
        grafo->dists[i].distancia = dist[i];
        grafo->dists[i].componente = component;
    }
    
    free(dist);
    free(fila);
}

void DFS(p_graph grafo,int no,int *visitados,int is_inverted){
    if(visitados[no] == 1)return;

    visitados[no] = 1;

    if(is_inverted == 0){
        for(int i = 0 ; i < grafo->n ; i++){
            if(grafo->adj[no][i] == 0)continue;
            DFS(grafo,i,visitados,is_inverted);
        }
    }else{
        for(int i = (grafo->n - 1) ; i >= 0 ; i--){
            if(grafo->adj[no][i] == 0)continue;
            DFS(grafo,i,visitados,is_inverted);
        }
    }

    char v = 'A' + no;

    printf("%c ",v);
    return;
}