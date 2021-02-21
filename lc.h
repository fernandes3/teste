#include <string.h>
#include <conio.h>
#include <iostream>


struct NoLC
{
	FuncionarioEnfermaria funcionarioEnf;
	NoLC *prox;
};

void criarLC (NoLC *&LC)
{
	LC = NULL;	
}

int LCVazia (NoLC *LC)
{
	return (LC == NULL);
}

void inserirNaLC (NoLC *&LC, FuncionarioEnfermaria f, int inicio)
{
	NoLC *novo = new (NoLC);
	novo->funcionarioEnf = f;
	if (LCVazia(LC))
	{
		novo->prox = novo;  //inserir na LC vazia
		LC = novo;
	}
	else
	{
		NoLC *aux = LC;
		while (aux->prox != LC)
		{
			aux = aux->prox;		//inserir na ultima posição
		}
		aux->prox = novo;
		novo->prox = LC;
		if (inicio == 1)
		{
			LC = novo;		//inserir na primeira posição
		}
	}
}

FuncionarioEnfermaria removerDaLC (NoLC *&LC, int inicio)
{
	NoLC *remover = LC;
	if (inicio == 1)
	{
		LC = LC->prox;
	}
	while (remover->prox->prox != LC)
	{
		remover = remover->prox;
	}
	FuncionarioEnfermaria x = remover->prox->funcionarioEnf;
	delete (remover->prox);
	remover->prox = LC;
	return x;
}

void imprimirLC (NoLC *LC)
{
	system("cls");
	if (!LCVazia(LC))
	{
		NoLC *aux = LC;
		do 
		{
			printf("%s, %ld -> ", aux->funcionarioEnf, aux->funcionarioEnf.RegistoConselho);
			aux = aux->prox;
		} while (aux != LC);
	}
	else
		printf("Fila vazia!");	
	printf("\n\n");
	system("pause");
}
