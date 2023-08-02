#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

int main(int argc, char **argv){
    char *path = (argc > 1) ? argv[1] : NULL;

    int n,soma = 0;
    p_pilha p = criar_pilha();

    FILE *f = fopen(path, "r");
    fscanf(f, "%d\n", &n);

    for(int i = 0 ; i < n ; ++i){
        char operator;
        fscanf(f, "%c\n", &operator);
        if(operator >= '0' && operator <= '9'){
            int num = operator - '0';
            inserir_pilha(p,num);
        }else if(operator == '+'){
            int a = p->topo->data;
            int b = p->topo->next->data;
            inserir_pilha(p,a+b);
        }else if(operator == 'D'){
            inserir_pilha(p,p->topo->data*2);
        }else if(operator == 'C'){
            remover_pilha(p);
        }else{
            p->topo->data = - p->topo->data;
        }
    }

    soma = destruir_pilha(p);

    printf("%d\n",soma);

    fclose(f);

    return 0;
}