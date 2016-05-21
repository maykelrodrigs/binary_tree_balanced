#include <lista.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

/* ------------------------------------------------------ */

TLista* inicializaLista(){
    TLista *l = (TLista *) malloc(sizeof(TLista));
    l->inicio = NULL;
    return l;
}

/* ------------------------------------------------------ */

void insereLista(TLista *l, TFunc *novo){

    if(l->inicio == NULL){
        l->inicio = novo;
    }else{
        novo->prox = l->inicio;
        l->inicio = novo;
    }

    l->quantidade++;
}

/* ------------------------------------------------------ */

void ordenaLista(TLista *l){

    TFunc *i, *aux, *j;
    aux = (TFunc *) malloc(sizeof(TFunc));

    i = l->inicio;
    while(i != NULL){
        j = i->prox;
        while(j != NULL){
            if(strcmp(i->nome, j->nome) > 0){
                strcpy(aux->nome, i->nome);
                aux->matricula = i->matricula;
                aux->salario = i->salario;
                strcpy(aux->genero, i->genero);

                strcpy(i->nome, j->nome);
                i->matricula = j->matricula;
                i->salario = j->salario;
                strcpy(i->genero, j->genero);

                strcpy(j->nome, aux->nome);
                j->matricula = aux->matricula;
                j->salario = aux->salario;
                strcpy(j->genero, aux->genero);
            }
            j = j->prox;
        }
        i = i->prox;
    }
    free(aux);
}

/* ------------------------------------------------------ */

void imprimeLista(TFunc *f){
    if(f != NULL){
        cout<<f->nome<<endl;
        imprimeLista(f->prox);
    }
}

/* ------------------------------------------------------ */

void imprimeFuncionario(TFunc *f, char nome[]){

    if(f != NULL){
        if(strcmp(f->nome, nome) == 0){
            cout<<endl<<"|> Matricula: "<<f->matricula<<endl;
            cout<<"|> Salario: "<<f->salario<<endl;
            cout<<"|> Genero: "<<f->genero<<endl<<endl;
        }
        imprimeFuncionario(f->prox, nome);
    }
}

/* ------------------------------------------------------ */

int retornaPagina(TFunc *f){

    if(f->nome[0] < 70)
        return 1;
    else if(f->nome[0] < 75)
        return 2;
    else if(f->nome[0] < 80)
        return 3;
    else if(f->nome[0] < 85)
        return 4;
    else
        return 5;

}

/* ------------------------------------------------------ */

void inserePagina(TFunc *pag, TLista *p1, TLista *p2, TLista *p3, TLista *p4, TLista *p5){

    if(pag != NULL){
        if(retornaPagina(pag) == 1){
            if(p1->inicio == NULL)
                p1->inicio = pag;
        }else if(retornaPagina(pag) == 2){
            if(p2->inicio == NULL)
                p2->inicio = pag;
        }else if(retornaPagina(pag) == 3){
            if(p3->inicio == NULL)
                p3->inicio = pag;
        }else if(retornaPagina(pag) == 4){
            if(p4->inicio == NULL)
                p4->inicio = pag;
        }else{
            if(p5->inicio == NULL)
                p5->inicio = pag;
        }

        inserePagina(pag->prox, p1, p2, p3, p4, p5);
    }

}

/* ------------------------------------------------------ */

void buscaFuncionario(TNodo *r, TLista *p1, TLista *p2, TLista *p3, TLista *p4, TLista *p5, char nome[]){

    if(buscarPagina(r, nome) == 1)
        imprimeFuncionario(p1->inicio, nome);
    else if(buscarPagina(r, nome) == 2)
        imprimeFuncionario(p2->inicio, nome);
    else if(buscarPagina(r, nome) == 3)
        imprimeFuncionario(p3->inicio, nome);
    else if(buscarPagina(r, nome) == 4)
        imprimeFuncionario(p4->inicio, nome);
    else if(buscarPagina(r, nome) == 5)
        imprimeFuncionario(p5->inicio, nome);
    else
        cout<<"\n**Funcionario não encontrado!"<<endl;

}

/* ------------------------------------------------------ */

void lerArquivo(TLista *l){

    char frase[100];
    char *tok;
    int aux = 1;

    FILE *arquivo;
    arquivo = fopen("tabela.txt", "r");

    if(!arquivo){
        cout<<"Erro ao abrir o arquivo!"<<endl;
    }else{
        while((fgets(frase, sizeof(frase), arquivo))!=NULL){

            TFunc *novo = (TFunc *) malloc(sizeof(TFunc));
            tok = strtok(frase, ";");
            while(tok!=NULL){

                if(aux == 1)
                    novo->matricula = atoi(tok);
                else if(aux == 2)
                    strcpy(novo->nome, tok);
                else if(aux == 3)
                    novo->salario = atof(tok);
                else if(aux == 4)
                    strcpy(novo->genero,  tok);
                else
                    aux = 0;

                aux++;
                tok = strtok(NULL, ";");
            }

            insereLista(l, novo);
        }
    }
    fclose(arquivo);
}

