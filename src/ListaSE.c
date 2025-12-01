#include "ListaSE.h" 
#include <stdio.h>
#include <stdlib.h>

tp_lista_encadeada* inicializa_listase()
{
	return NULL;
}
	
int listase_vazia(tp_lista_encadeada* lista)
{
	if(lista==NULL) return 1;
	return 0;
}

tp_lista_encadeada* aloca_listase()
{ 
	tp_lista_encadeada* novo_no;
	novo_no=(tp_lista_encadeada*) malloc(sizeof(tp_lista_encadeada));
	return novo_no;
}

int insere_listase_no_fim(tp_lista_encadeada** l, tp_item_listase e)
{ 
	tp_lista_encadeada* novo_no, *atu;
	novo_no=aloca_listase(); 
	if(novo_no==NULL) return 0;

	novo_no->info= e;
	novo_no->prox=NULL;

	if(listase_vazia(*l)){
		*l=novo_no;
	} else{
		atu = *l;
		while(atu->prox!=NULL){ 
		atu=atu->prox;
		}
		atu->prox=novo_no;	
	}
	return 1;
}

void imprime_listase(tp_lista_encadeada* lista)
{
	tp_lista_encadeada* atu;
	atu=lista;
	while (atu!=NULL){
		printf("%d ", atu->info);
		atu=atu->prox;
	}
}

int remove_listase(tp_lista_encadeada** lista, tp_item_listase e)
{
	tp_lista_encadeada* ant, *atu;
	atu=*lista;
	ant=NULL;
	while ((atu!=NULL)&&(atu->info!=e)){
		ant=atu;
		atu=atu->prox;	
		}
	if (atu==NULL) return 0; 
	if (ant==NULL){
		*lista=atu->prox; 
	}
	else{
		ant->prox=atu->prox; 
	}
	free(atu);
	atu=NULL;
	return 1;
}

tp_lista_encadeada* busca_listase(tp_lista_encadeada* lista, tp_item_listase e)
{
	tp_lista_encadeada* atu;
	atu=lista;
	while((atu!=NULL)&&(atu->info!=e)){
		atu=atu->prox;
	}
	if (atu==NULL) return NULL;
	return atu;
}

int tamanho_listase(tp_lista_encadeada* lista)
{
    int cont=0;        
    tp_lista_encadeada* atu;
    atu=lista;
    while(atu!=NULL){
        cont++;
        atu=atu->prox;
    }
    return cont;
}

void destroi_listase(tp_lista_encadeada** l)
{
	tp_lista_encadeada* atu;
	atu=*l;
	while (atu!=NULL){
		*l=atu->prox;
		free(atu);
		atu=*l;
	}
	*l=NULL;
}