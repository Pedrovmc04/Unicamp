typedef struct no *p_no;

struct no{
    int data;
    p_no esq,dir;
};

p_no montar_arvore(int *simetrica,int *pos_ordem,int l,int r,int *topo);

void destruir_arvore(p_no raiz);

void read_pre_ordem(p_no raiz);

void read_pos_ordem(p_no raiz);

void read_inordem(p_no raiz);