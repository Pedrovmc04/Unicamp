#define PAI(i) ((i-1) /2)
#define F_ESQ(i) (2*i+1)
#define F_DIR(i) (2*i+2)
#define INF 999999

typedef struct{
    char sobrenome[100];
    int p;
}item;

typedef item *p_item;

typedef struct{
    p_item cliente;
    int n,tam,minH;
}heap;

typedef heap *p_heap;

void trocar(item *a,item *b);

int comparar_string(char *str1,char *str2);

p_heap criar_Heap(int tam);

void destruir_Heap(p_heap heap);

void inserir_Heap(p_heap heap,item cliente);

void remover_Heap(p_heap heap,int pos);

void sobe_Heap(p_heap heap, int k);

void desce_heap(p_heap heap,int k);

void trocar_prioridade(p_heap heap,item cliente);

int procurar_min(p_heap heap);

void printar_Heap(p_heap heap);