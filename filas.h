#include <string.h>
#include <conio.h>
#include <iostream>


struct NodoFila 
{
	Ficha ficha;
	NodoFila *prox;
}; 

struct Fila 
{
	NodoFila *prim; //ponteiro para a primeira posição da fila
	NodoFila *ult; //ponteiro para a última posição da fila
}; 

void criarFila (Fila &F) {
	F.prim = F.ult = NULL;
}

int filaVazia (Fila F) {
	return ((F.prim == NULL) && (F.ult == NULL));
}

void imprimirFila(Fila F) {
	system("cls");
	if (!filaVazia(F)) {
		NodoFila *aux = F.prim;
		while (aux != NULL) {
			printf("%s, %ld -> ", aux->ficha.Nome, aux->ficha.cpf);
			aux = aux->prox;
		}
	}
	else
		printf("Fila vazia!");
	
	printf("\n\n");
	system("pause");
}

void enfileirar(Fila &F, Ficha x) {
	NodoFila *aux = new (NodoFila);
	aux->ficha = x;
	aux->prox = NULL;
	if (filaVazia(F)) F.prim = aux;
	else F.ult->prox = aux;
	F.ult = aux;
}

Ficha desenfileirar(Fila &F) {
	NodoFila *aux = F.prim;
	Ficha y = aux->ficha;
	if (F.prim == F.ult) F.ult = NULL;
	F.prim = aux->prox;
	delete(aux);
	return y;
}
