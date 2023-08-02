#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no *p_no;

struct no{
    double coeficiente,expoente;
    p_no next;
};

void destruir_lista(p_no list){
    while(list != NULL){
        p_no next = list->next;
        free(list);
        list = next;
    }
}

p_no adicionar_elemento(p_no list,double coeficiente,double expoente){
    p_no new = malloc(sizeof(struct no));
    new->coeficiente = coeficiente;
    new->expoente = expoente;
    new->next = list;
    return new;
}

void print_lista(p_no list){
    for(p_no i = list; i != NULL; i = i->next){
        printf("%0.2lf %0.2lf\n",i->coeficiente,i->expoente);
    }
}

p_no ler_arquivo(char *path){
    p_no new = NULL;
    int n;
    FILE *f = fopen(path,"r");
    fscanf(f,"%d",&n);
    for(int i = 0 ; i < n ; ++i){
        double coef,expo;
        fscanf(f,"%lf %lf",&coef,&expo);
        new = adicionar_elemento(new,coef,expo);
    }
    fclose(f);

    return new;
}

int main(int argc, char **argv){
    char *path = (argc > 1) ? argv[1] : NULL;
    double x = (argc > 2) ? atof(argv[2]) : 0;

    double ans = 0.0;
    p_no polinomio = NULL;

    polinomio = ler_arquivo(path);

    for(p_no i = polinomio; i != NULL; i = i->next){
        double potencia = pow(x,i->expoente);
        ans += potencia * i->coeficiente;
    }

    printf("%lf\n",ans);

    destruir_lista(polinomio);

    return 0;
}