#define INF 999999999

typedef struct no *p_no;
typedef struct queue *p_queue;
typedef struct graph *p_graph;
typedef struct dist *p_dist;

struct dist{
    int componente,distancia;
};

struct no{
    p_no next;
    int data;
};

struct queue{
    p_no ini,fim;
};

struct graph{
    int **adj;
    p_dist dists;
    int n;
};

p_queue criar_queue();

void inserir_queue(p_queue queue,int x);

int extrair_queue(p_queue queue);

p_graph criar_grafo(int tam);

void destruir_grafo(p_graph grafo);

void printa_listAdj(p_graph grafo);

void BFS(p_graph grafo,int no,int component);

void DFS(p_graph grafo,int no,int *visitados,int is_inverted);