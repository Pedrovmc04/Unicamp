typedef struct no *p_no;

struct no{
    int data;
    p_no esq,dir;
};

int max(int a, int b);

p_no montar_arvore(int *simetrica,int *pos_ondem,int l,int r,int *topo);

void read_pos_ondem(p_no raiz);

int max_graos(p_no raiz,int *max);

void destruir_arvore(p_no raiz);