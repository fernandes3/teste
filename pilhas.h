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

int pilhaVazia(No *topo) { //Verifica se a pilha está vazia ou não através da variável topo
	return (topo == NULL); //retorna o valor da comparação (0 ou 1)
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
	novo->prox = topo; //faz o próximo do novo nó apontar para onde era o topo
	topo = novo; //faz o topo apontar para o novo nó, que agora aponta para o Novo topo
}

Ficha desempilhar(No *&topo) {
	No *remover = topo;
	Ficha x = topo->ficha;
	topo = topo->prox;
	delete(remover);
	return x; //retorna o caracter que está sendo desempilhado
}


