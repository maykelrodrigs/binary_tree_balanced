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
    l->fim = NULL;
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

void imprimeFuncionario(TLista *f, char nome[], int pag){

    TFunc *ini = f->inicio;
    TFunc *fim = f->fim;

    while(ini!=fim && ini!=NULL){
        if(strcmp(ini->nome, nome) == 0){
            cout<<endl<<"|> Matricula: "<<ini->matricula<<endl;
            cout<<"|> Nome: "<<ini->nome<<endl;
            cout<<"|> Salario: "<<ini->salario<<endl;
            cout<<"|> Genero: "<<ini->genero<<endl<<endl;
        }else{
            cout<<ini->nome<<endl;
        }
        ini = ini->prox;
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
                p1->fim = p2->inicio;
        }else if(retornaPagina(pag) == 3){
            if(p3->inicio == NULL)
                p3->inicio = pag;
                p2->fim = p3->inicio;
        }else if(retornaPagina(pag) == 4){
            if(p4->inicio == NULL)
                p4->inicio = pag;
                p3->fim = p4->inicio;
        }else{
            if(p5->inicio == NULL)
                p5->inicio = pag;
                p4->fim = p5->inicio;
                p5->fim = NULL;
        }

        inserePagina(pag->prox, p1, p2, p3, p4, p5);
    }

}

/* ------------------------------------------------------ */

void buscaFuncionario(TNodo *r, TLista *p1, TLista *p2, TLista *p3, TLista *p4, TLista *p5, char nome[]){

    int ver = buscarPagina(r, nome);

    if(ver == 1)
        imprimeFuncionario(p1, nome, 1);
    else if(ver == 2)
        imprimeFuncionario(p2, nome, 2);
    else if(ver == 3)
        imprimeFuncionario(p3, nome, 3);
    else if(ver == 4){
        imprimeFuncionario(p4, nome, 4);
    }
    else if(ver == 5){
        imprimeFuncionario(p5, nome, 5);
    }
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

