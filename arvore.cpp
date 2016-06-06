#include <arvore.h>
#include <iostream>
#include <string.h>

using namespace std;

/* ------------------------------------------------------ */

TNodo* inicializaArvore(){
    TNodo *r = (TNodo *) malloc(sizeof(TNodo));
    r = NULL;
    return r;
}

/* ------------------------------------------------------ */

void insereArvore(TNodo **r, char nome[50], int pagina){

    TNodo *novo = (TNodo *)malloc(sizeof(TNodo));

    strcpy(novo->nome, nome);
    novo->pagina = pagina;
    novo->direita = NULL;
    novo->esquerda = NULL;

    if (*r == NULL)
        *r = novo;
    else
         insereRecursivo(*r, novo);
}

/* ------------------------------------------------------ */

void insereRecursivo(TNodo *atual, TNodo *novo){
    if(strcmp(novo->nome, atual->nome) < 0){
        if(atual->esquerda == NULL){
            atual->esquerda = novo;
        }else{
            insereRecursivo(atual->esquerda, novo);
        }
    }else{
        if(atual->direita == NULL){
            atual->direita = novo;
        } else {
            insereRecursivo(atual->direita, novo);
        }
    }
}

/* ------------------------------------------------------ */

void preOrdem(TNodo *r){
    if (r != NULL){
        cout<<r->nome<<endl;
        preOrdem(r->esquerda);
        preOrdem(r->direita);
    }
}

/* ------------------------------------------------------ */

void emOrdem(TNodo *r){
    if (r != NULL){
        preOrdem(r->esquerda);
        cout<<r->nome<<endl;
        preOrdem(r->direita);
    }
}

/* ------------------------------------------------------ */

void posOrdem(TNodo *r){
    if (r != NULL){
        preOrdem(r->esquerda);
        preOrdem(r->direita);
        cout<<r->nome<<endl;
    }
}

/* ------------------------------------------------------ */

void imprimeArvore(TNodo *r){
    if (r != NULL){
        cout<<r->nome<<endl;
        preOrdem(r->esquerda);
    }
}

/* ------------------------------------------------------ */

int alturaNo(TNodo *r){

    int u, v;
    if (r == NULL) return -1;
    u = alturaNo(r->esquerda);
    v = alturaNo(r->direita);
    if (u > v) return u+1;
    else return v+1;
}

/* ------------------------------------------------------ */

int buscarPagina(TNodo *r, char nome[]){

    if(r != NULL){
        if(strcmp(nome, r->nome) == 0){
            return r->pagina;
        }else{
            if(strcmp(r->nome, nome) < 0){
                buscarPagina(r->direita, nome);
            }else{
                buscarPagina(r->esquerda, nome);
            }
        }
    }
}

/* ------------------------------------------------------ */

TNodo *excluiNodo(TNodo *r, char nome[]){

    if (r == NULL)	{
            return NULL;
    } else if (strcmp(r->nome, nome) > 0){ // valor > argumento
            r->esquerda = excluiNodo(r->esquerda, nome);

    } else if (strcmp(r->nome, nome) < 0){ // valor < argumento
            r->direita = excluiNodo(r->direita, nome);

    } else {
        if((r->esquerda == NULL) && (r->direita == NULL)){
            free(r);
            r = NULL;
        } else if (r->esquerda == NULL){
            TNodo *temp = r;
            r = r->direita;
            free(temp);
        } else if (r->direita == NULL){
            TNodo *temp = r;
            r = r->esquerda;
            free(temp);
        } else {
            TNodo *filho = r->esquerda;
            while (filho->direita != NULL){
                filho = filho->direita;
            }

            // Verificar se precisa atualizar o numero da página
            strcpy(r->nome, filho->nome);
            strcpy(filho->nome, nome);

            r->esquerda = excluiNodo(r->esquerda, nome);
        }
    }
    return r;
}
