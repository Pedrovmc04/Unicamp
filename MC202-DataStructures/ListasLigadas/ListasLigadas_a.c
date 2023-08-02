#include <stdio.h>
#include <stdlib.h>

typedef struct no *p_no;

struct no{
    float coeficiente;
    int expoente;
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
    if(list == NULL || list->expoente < expoente){
        p_no new = malloc(sizeof(struct no));
        new->coeficiente = coeficiente;
        new->expoente = expoente;
        new->next = list;
        return new;
    }

    list->next = adicionar_elemento(list->next,coeficiente,expoente);
    return list;
}

void derivar_polinomio(p_no list){
    if(list == NULL)return;
    list->coeficiente = list->coeficiente*list->expoente;
    list->expoente--;
    derivar_polinomio(list->next);
}

void print_lista(p_no list){
    for(p_no i = list; i != NULL ; i = i->next){
        if(i->coeficiente == 0)continue;
        if(i->expoente == 0){
            if(i->coeficiente > 0){
                printf("%0.2f ",i->coeficiente);
            }else{
                printf("- %0.2f ",-1 * i->coeficiente);
            }
        }else{
            if(i->coeficiente > 0){
                printf("+ %0.2fx^%d ",i->coeficiente,i->expoente);
            }else{
                printf("- %0.2fx^%d ",-1 * i->coeficiente,i->expoente);
            }
        }
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

int main(int argc, char **argv){
    char *path = (argc > 1) ? argv[1] : NULL;

    p_no polinomio = NULL;

    polinomio = ler_arquivo(path);

    derivar_polinomio(polinomio);

    print_lista(polinomio);

    destruir_lista(polinomio);

    return 0;
}