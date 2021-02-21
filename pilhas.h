#include <string.h>
#include <conio.h>
#include <iostream>

struct No {
	Ficha ficha;
	No *prox;
}; 

void criarPilha(No *&topo) { //Cria uma pilha vazia, apontando o topo da pilha para nulo
	topo = NULL;
}

int pilhaVazia(No *topo) { //Verifica se a pilha est� vazia ou n�o atrav�s da vari�vel topo
	return (topo == NULL); //retorna o valor da compara��o (0 ou 1)
}

void imprimirPilha(No *topo) {
	system("cls");
	if (!pilhaVazia(topo)) {
		No *aux = topo;
		while (aux != NULL) {
			printf("%s,%ld \n|\n", aux->ficha.Nome,aux->ficha.cpf);
			aux = aux->prox;
		}
		printf("\n\n");
	}
	else printf("Pilha vazia!\n\n");
	system("pause");
}

void empilhar(No *&topo, Ficha f) {
	No *novo = new No(); //aloca uma Nova area
	novo->ficha = f;
	novo->prox = topo; //faz o pr�ximo do novo n� apontar para onde era o topo
	topo = novo; //faz o topo apontar para o novo n�, que agora aponta para o Novo topo
}

Ficha desempilhar(No *&topo) {
	No *remover = topo;
	Ficha x = topo->ficha;
	topo = topo->prox;
	delete(remover);
	return x; //retorna o caracter que est� sendo desempilhado
}


