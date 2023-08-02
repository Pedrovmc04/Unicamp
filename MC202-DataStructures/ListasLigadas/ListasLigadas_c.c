#include <stdio.h>
#include <stdlib.h>

typedef struct no *p_no;

struct no{
    float coeficiente;
    int expoente,pos;
    p_no next;
};

void destruir_lista(p_no list){
    while(list != NULL){
        p_no next = list->next;
        free(list);
        list = next;
    }
}

p_no adicionar_elemento(p_no list,float coeficiente,int expoente){
    if(list == NULL){
        p_no new = malloc(sizeof(struct no));
        new->coeficiente = coeficiente;
        new->expoente = expoente;
        new->pos = 1;
        new->next = list;
        return new;
    }

    p_no new = malloc(sizeof(struct no));
    new->coeficiente = coeficiente;
    new->expoente = expoente;
    new->pos = list->pos+1;
    new->next = list;

    return new;
}

void print_lista(p_no list){
    for(p_no i = list; i != NULL; i = i->next){
        printf("%0.2f %d %d\n",i->coeficiente,i->expoente,i->pos);
    }
}

p_no ler_arquivo(char *path){
    p_no new = NULL;
    int n;
    FILE *f = fopen(path,"r");
    fscanf(f,"%d",&n);
    for(int i = 0 ; i < n ; ++i){
        float coef;
        int expo;
        fscanf(f,"%f %d",&coef,&expo);
        new = adicionar_elemento(new,coef,expo);
    }
    fclose(f);

    return new;
}

int tamanho(p_no list){
    return list->pos;
}

int main(int argc, char **argv){
    char *path = (argc > 1) ? argv[1] : NULL;
    
    p_no polinomio = NULL;

    polinomio = ler_arquivo(path);

    printf("%d\n",tamanho(polinomio));

    destruir_lista(polinomio);

    return 0;
}