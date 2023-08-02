#include <stdio.h>
#include <stdlib.h>

#define PAI(i) ((i-1) /2)
#define F_ESQ(i) (2*i+1)
#define F_DIR(i) (2*i+2)
#define INF 999999
#define MAXN 16

typedef struct{
    int v,peso;
}vertice;

typedef struct{
    vertice *no;
    int n,tam;
}heap;

typedef struct{
    int dist[MAXN][MAXN];
    int n;
}graph;

typedef heap *p_heap;
typedef graph *p_graph;

void trocar(vertice *a,vertice *b);
p_heap criar_Heap(int tam);
void destruir_Heap(p_heap heap);
void inserir_Heap(p_heap heap,int v,int peso);
int remover_Heap(p_heap heap);
void sobe_Heap(p_heap heap, int k);
void desce_heap(p_heap heap,int k);


////////////////////////////////////////////////////////////////

void trocar(vertice *a,vertice *b){
    vertice t = *a;
    *a = *b;
    *b = t;
}

p_heap criar_Heap(int tam){
    p_heap new = malloc(sizeof(heap));
    new->no = malloc((tam)*sizeof(vertice));
    new->tam = tam;
    new->n = 0;

    return new;
}

void destruir_Heap(p_heap heap){
    free(heap->no);
    free(heap);
}

void inserir_Heap(p_heap heap,int v,int peso){
    if(heap->n == heap->tam)return;

    vertice no;
    no.v = v;
    no.peso = peso;

    heap->no[heap->n] = no;
    heap->n++;

    sobe_Heap(heap,heap->n - 1);
}

int remover_Heap(p_heap heap){
    int pos = heap->no[0].v;
    heap->n--;
    trocar(&heap->no[0],&heap->no[heap->n]);
    desce_heap(heap,0);
    return pos;
}

void sobe_Heap(p_heap heap,int k){
    if(k > 0 && heap->no[PAI(k)].peso > heap->no[k].peso){
        trocar(&heap->no[PAI(k)],&heap->no[k]);
        sobe_Heap(heap,PAI(k));
    }
}

void desce_heap(p_heap heap,int k){
    int menor_filho;
    if (F_ESQ(k) < heap->n){
        menor_filho = F_ESQ(k);
        if(F_DIR(k) < heap->n && heap->no[F_ESQ(k)].peso > heap->no[F_DIR(k)].peso)menor_filho = F_DIR(k);

        if(heap->no[k].peso > heap->no[menor_filho].peso){
            trocar(&heap->no[k],&heap->no[menor_filho]);
            desce_heap(heap,menor_filho);
        }

    }

}

////////////////////////////////////////////////////////////////

int prim(p_graph g){
    int dist[MAXN];
    int visitados[MAXN];

    for(int i = 0 ; i < g->n ; i++){
        dist[i] = INF;
        visitados[i] = 0;
    }
    dist[0] = 0;

    p_heap fila = criar_Heap(20);
    inserir_Heap(fila,0,0);

    while(1){
        int v = -1;

        while(fila->n != 0){
            int u = remover_Heap(fila);

            if(visitados[u] == 0){
                v = u;
                break;
            }
        }

        if(v == -1)break;

        visitados[v] = 1;

        for(int i = 0 ; i < g->n ; i++){
            if(g->dist[v][i] == 0)continue;

            if(dist[i] > g->dist[v][i] && visitados[i] == 0){
                dist[i] = g->dist[v][i];
                //printf("Atual: %d, inserindo : %d %d\n", v,i,dist[i]);
                inserir_Heap(fila,i,dist[i]);
            }
        }
    }

    destruir_Heap(fila);

    int ans = 0;

    for(int i = 0 ; i < g->n ; i++){
        if(dist[i] == INF)continue;
        printf("%d\n",dist[i]);
        ans += dist[i];
    }

    return ans;
}

////////////////////////////////////////////////////////////////

int main(){
    p_graph g = malloc(sizeof(graph));
    g->n = MAXN;
    int n;
    scanf("%d\n",&n);

    for(int i = 0 ; i < n ; i++){
        char aux1,aux2;
        int x,y,p;
        scanf("%c %c %d\n",&aux1,&aux2,&p);
        x = (int)(aux1-'A'),y = (int)(aux2-'A');
        g->dist[x][y] = p;
        g->dist[y][x] = p;
    }

    printf("%d\n",prim(g));

    free(g);

    return 0;
}