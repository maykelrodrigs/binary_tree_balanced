#include <iostream>
#include <lista.h>
#include <arvore.h>
#include <string.h>
#include <math.h>

using namespace std;

int contarNivel(int numero, int cont);
int *inicializaVetor(int n);
int *divisaoNivel(int n, int raiz);
void preencheArvore(int *vetor, int tam, TNodo *r, TLista *l);
void insereNodo(int pos, TLista *l, TNodo **r);

/* ------------------------------------------------------ */

int contaNivel(int numero, int cont){

    int div = numero / 2;

    if(div < 1)
        return cont;

    contaNivel(div, ++cont);
}

/* ------------------------------------------------------ */

int *inicializaVetor(int n){

    int *v = (int *)calloc(n, sizeof(int));
    return v;
}

/* ------------------------------------------------------ */

int *divisaoNivel(int n, int raiz){

    int *v = inicializaVetor(n);
    for(int i=0; i<n; i++){
        raiz = raiz / 2;
        v[i] = raiz;
    }
    return v;
}

/* ------------------------------------------------------ */

int *trocarVetor(int *vetor, int tam){

    int *v = inicializaVetor(tam);
    for(int j=0; j<tam; j++){
        v[j] = vetor[j];
    }
    return v;
}

/* ------------------------------------------------------ */

void preencheArvore(int *vetor, int tam, TNodo *r, TLista *l){

    for(int i=0; i<tam; i++){
        if(vetor[i] == 0){
            insereNodo(i, l, &r);
        }
    }
}

/* ------------------------------------------------------ */

void insereNodo(int pos, TLista *l, TNodo **r){

    int cont = 0;
    TFunc *func = l->inicio;
    while(func != NULL){
        if(cont == pos){
            insereArvore(r, func->nome, retornaPagina(func));
        }
        cont++;
        func = func->prox;
    }
}

/* ------------------------------------------------------ */

int menu(){

    system("cls || clear");

    cout<<"|============| ARVORE BINARIA |"<<endl;
    cout<<"1 - Imprime funcionarios"<<endl;
    cout<<"2 - Buscar funcionario"<<endl;
    cout<<"3 - Imprime arvore"<<endl;
    cout<<"4 - Pre ordem"<<endl;
    cout<<"5 - Em ordem"<<endl;
    cout<<"6 - Pos ordem"<<endl;
    cout<<"7 - Altura da arvore"<<endl;
    cout<<"9 - Sair"<<endl;

    int op;
    cout<<"\n| Opção: ";
    cin>>op;
    getchar();

    return op;
}

/* ------------------------------------------------------ */

int main(){

    TLista *l = inicializaLista();
    lerArquivo(l);
    ordenaLista(l);

    TLista *p1 = inicializaLista(); // A - E
    TLista *p2 = inicializaLista(); // F - J
    TLista *p3 = inicializaLista(); // K - O
    TLista *p4 = inicializaLista(); // P - T
    TLista *p5 = inicializaLista(); // U - Z

    inserePagina(l->inicio, p1, p2, p3, p4, p5);

    TNodo *r = inicializaArvore();

    int cont = 0, esq, dir;
    int tamanho = l->quantidade;
    int raiz = tamanho / 2;

    int qtd_nivel = contaNivel(raiz, 0);
    int *vet_nivel = divisaoNivel(qtd_nivel, raiz);
    int *vet_nome = inicializaVetor(tamanho);

    int qtd_filho = pow(2, qtd_nivel);
    int *vet_filho = inicializaVetor(qtd_filho);
    int *aux = inicializaVetor(qtd_filho);

    vet_filho[0] = raiz; // Inserir a raiz no vetor
    vet_nome[raiz] = 1; // Marcar a raiz como inseriada
    insereNodo(raiz, l, &r); // Inserir a raiz na árvore

    for(int i=1; i<=qtd_nivel; i++){
        for(int j=0; j<pow(2,(i-1)); j++){

            esq = vet_filho[j] - vet_nivel[i-1];
            dir = vet_filho[j] + vet_nivel[i-1];

            insereNodo(esq, l, &r);
            insereNodo(dir, l, &r);

            vet_nome[esq] = 1;
            vet_nome[dir] = 1;

            aux[cont++] = esq;
            aux[cont++] = dir;
        }

        vet_filho = trocarVetor(aux, cont);
        cont = 0;
    }

    preencheArvore(vet_nome, tamanho, r, l);

    buscaFuncionario(r, p1, p2, p3, p4, p5, "Silvio Santos");
    excluiNodo(r, "Ze da Silva");

}
