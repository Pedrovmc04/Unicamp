typedef struct no *p_no;
typedef struct pilha *p_pilha;

struct no{
    int data;
    p_no next;
};

struct pilha{
    p_no topo;
};


p_pilha criar_pilha();

int destruir_pilha(p_pilha p);

void inserir_pilha(p_pilha p,int x);

void remover_pilha(p_pilha p);