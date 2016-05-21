#ifndef ARVORE_H
#define ARVORE_H


/* ------------------------------------------------------ */

typedef struct tipoNodo {
   char nome[40];
   int pagina;
   tipoNodo *esquerda, *direita;
} TNodo;

/* ------------------------------------------------------ */


#include <lista.h>

TNodo* inicializaArvore();
int alturaNo(TNodo *r);
int buscarPagina(TNodo *r, char nome[40]);
void insereArvore(TNodo **r, char nome[50], int pagina);
void insereRecursivo(TNodo *atual, TNodo *novo);
void preOrdem(TNodo *r);
void emOrdem(TNodo *r);
void posOrdem(TNodo *r);
void imprimeArvore(TNodo *r);

/* ------------------------------------------------------ */

#endif // ARVORE_H
