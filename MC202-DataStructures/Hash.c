#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 271
#define MAX_LINE 50

typedef struct no *p_no;
typedef struct hash *p_hash;

struct no{
    char chave[MAX_LINE];
    p_no next;
};

struct hash{
    p_no vetor[MAXN];
};

////////////////////////////////////////////////////////////

p_no adicionar_elemento(p_no list,char *chave){
    p_no new = malloc(sizeof(struct no));
    strcpy(new->chave,chave);
    new->next = list;
    return new;
}

void destruir_lista(p_no list){
    while(list != NULL){
        p_no next = list->next;
        free(list);
        list = next;
    }
}

///////////////////////////////////////////////////////////

int hash(char *chave){
    int n = 0;
    for(int i = 0 ; i < strlen(chave) ; i++)
        n = (256 * n + chave[i])%MAXN;
    
    return n;
}

p_hash novo_hash_table(){
    p_hash new = malloc(sizeof(struct hash));
    for(int i = 0 ; i < MAXN ; i++)new->vetor[i] = NULL;
    return new;
}

void inserir_hash_table(p_hash t,char *chave) {
    int n = hash(chave);
    t->vetor[n] = adicionar_elemento(t->vetor[n],chave);
}

void destruir_hash_table(p_hash t) {
    for(int i = 0 ; i < MAXN ; i++){
        if(t->vetor[i] == NULL)continue;
        destruir_lista(t->vetor[i]);
    }
    free(t);
}

p_hash criar_hash_table(char *path){
    p_hash new = novo_hash_table();
    int n;

    FILE *f = fopen(path,"r");
    fscanf(f, "%d\n",&n);

    for(int i = 0 ; i < n ; ++i){
        char name[50];
        fgets(name,MAX_LINE, f);
        name[strcspn(name, "\n")] = '\0';
        inserir_hash_table(new,name);
    }

    fclose(f);

    return new;
}

int comparar_string(char *str1,char *str2){
    if(strlen(str1) != strlen(str2))return 0;

    for(int i = 0 ; i < strlen(str1) ; ++i){
        if(str1[i] != str2[i])return 0;
    }

    return 1;
}

int search_hash_table(p_hash t,char *name){
    int n = hash(name);
    for(p_no i = t->vetor[n] ; i != NULL ; i = i->next){
        if(comparar_string(i->chave,name) == 1)return 1;
    }
    return 0;
}

void print_hash_table(p_hash t){
    for(int i = 0 ; i < MAXN ; i++){
        if(t->vetor[i] == NULL)continue;
        printf("%d :",i);
        for(p_no j = t->vetor[i] ; j != NULL ; j = j->next){
            printf("%s %ld ",j->chave,strlen(j->chave));
        }
        printf("\n");
    }
}


//////////////////////////////////////////////////////////

int main(int argc, char **argv){
    char *path = (argc > 1) ? argv[1] : NULL;
    char *name = (argc > 2) ? argv[2] : NULL;

    p_hash table = criar_hash_table(path);

    printf("%d\n",search_hash_table(table,name));

    destruir_hash_table(table);

    return 0;
}