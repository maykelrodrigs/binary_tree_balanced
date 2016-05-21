#ifndef LISTA_H
#define LISTA_H

#include <arvore.h>

/* ------------------------------------------------------ */

typedef struct tipoFunc {
    int matricula;
    char nome[40];
    float salario;
    char genero[1];
    tipoFunc *prox;
} TFunc;

typedef struct TipoLista {
    TFunc *inicio;
    int quantidade;
} TLista;

/* ------------------------------------------------------ */

TLista* inicializaLista();
int retornaPagina(TFunc *f);
void ordenaLista(TLista *l);
void imprimeLista(TFunc *f);
void imprimeFuncionario(TFunc *f, char nome[]);
void insereLista(TLista *l, TFunc *novo);
void inserePagina(TFunc *pag, TLista *p1, TLista *p2, TLista *p3, TLista *p4, TLista *p5);
void buscaFuncionario(TNodo *r, TLista *p1, TLista *p2, TLista *p3, TLista *p4, TLista *p5, char nome[]);
void lerArquivo(TLista *l);

/* ------------------------------------------------------ */

#endif // LISTA_H
