#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


char player1 ;
char player2 ;
char escolha;
bool escolha_player = false;
int i = 0,j = 0;
int p_player1 = 0,p_player2 = 0 , p_empate = 0;
int ganhou = 0;
int fim = false;
int jogada = 0 , vez = 1;
int correto = false;
int contador = 0;
char matriz[3][3];
// assinatura das func
void preencher_matriz();
void player();
void print_matriz();
void jogadas();
void placar(int &p_player1,int &p_player2,int &p_empate);
void jogo();
void verif_ganhador();


int main() {
	char resp;
	setlocale(LC_ALL,"PORTUGUESE");
	jogo();
	while(resp !=toupper('N')){
	printf("Deseja jogar novamente?: ");
	scanf(" %c",&resp);
	if (resp == toupper('S')){
		ganhou = false;
		fim =  false;
		correto = false;
		jogo();
	}
}
	return 0;		
				
}




void player(){
	printf("Escolha (X) ou (O) para iniciar o jogo: ");
	scanf("%c",&escolha);
	while(escolha_player ==  false){
		
	if(escolha == 'X' || escolha == 'x'){
		player1 = 'X';
		player2 = 'O';
		escolha_player = true;
	}else if(escolha == 'O' || escolha == 'o'){
		player1 = 'O';
		player2 = 'X';
		escolha_player = true;
	}else{
		printf("\nEscolha Inválida ! Digite novamente: ");
		scanf(" %c",&escolha);
		
	}	
}
system("cls");
printf(" PLAYER 1 = %c       PLAYER 2 = %c",player1,player2);
}
void  placar(int &p_player1, int &p_player2, int &p_empate){
	printf("\n\n                               PLACAR                                   \n\n\n\n");
	printf("\tJOGADOR1              JOGADOR2              EMPATE\n\n");
	printf("          [%i]                   [%i]                  [%i]",p_player1,p_player2,p_empate);
	
}

void preencher_matriz(){
	
	for(int i = 0 ; i <3 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			matriz[i][j]=' ';
		}
	}
}
void print_matriz(){
	
	printf("\n\n\t\t[0]   [1]   [2]\n\n");
	printf("    [0]\t\t");
	printf(" %c  |  %c  |  %c  \n",matriz[0][0],matriz[0][1],matriz[0][2]);
	printf("\t\t----|-----|----\n");
	printf("    [1]\t\t");
	printf(" %c  |  %c  |  %c  \n",matriz[1][0],matriz[1][1],matriz[1][2]);
	printf("\t\t----|-----|----\n");
	printf("    [2]\t\t");
	printf(" %c  |  %c  |  %c  \n",matriz[2][0],matriz[2][1],matriz[2][2]);
	printf("\t\t----|-----|----\n");

}

void jogadas(){
	correto = false;
	if (fim == false){
			if (vez == 1){
				while(correto == false){
					printf("PLAYER 1 digite  a linha e coluna que deseja: ");
					cin >> i >> j;
					if(matriz[i-1][j-1] ==' '){
						matriz[i-1][j-1] = player1;
						correto = true;
						vez = 2;
						system("cls");
						print_matriz();
						placar(p_player1,p_player2,p_empate);
						printf("\n\n");

					}else
						printf("Jogada Inválida\n");

				}
			}else if (vez == 2){
				correto = false;
				while(correto == false){
					printf("PLAYER 2 digite  a linha e coluna que deseja: ");
					cin >> i >> j;
					
						if(matriz[i-1][j-1] ==' '){
						matriz[i-1][j-1] = player2;
						correto = true;
						vez = 1;
						system("cls");
						print_matriz();
						placar(p_player1,p_player2,p_empate);
						printf("\n\n");

					}else
						printf("Jogada Inválida\n");

					
				}
			}

		}
	}
	
	
	
	


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void jogo(){
	system("cls");
	player();
	preencher_matriz();
	print_matriz();
	placar(p_player1,p_player2,p_empate);
	printf("\n");
	contador = 0;
	ganhou = 0;
	while((contador <=9) && (ganhou == 0)){
		jogadas();
		contador++;
		verif_ganhador();
	}
}

void verif_ganhador(){

	if(matriz[0][0] == 'X' && matriz[0][1]  == 'X' && matriz[0][2] == 'X' ){
		ganhou = 1;
	}else if (matriz[1][0] == 'X' && matriz[1][1]  == 'X' && matriz[1][2] == 'X' ){
		ganhou = 1;	
	}else if (matriz[2][0] == 'X' && matriz[2][1]  == 'X' && matriz[2][2] == 'X' ){
		ganhou = 1;	
	}else if (matriz[0][0] == 'X' && matriz[1][0]  == 'X' && matriz[2][0] == 'X' ){
		ganhou = 1;	
	}else if (matriz[0][1] == 'X' && matriz[1][1]  == 'X' && matriz[2][1] == 'X' ){
		ganhou = 1;	
	}else if (matriz[0][2] == 'X' && matriz[1][2]  == 'X' && matriz[2][2] == 'X' ){
		ganhou = 1;	
	}else if (matriz[0][0] == 'X' && matriz[1][1]  == 'X' && matriz[2][2] == 'X' ){
		ganhou = 1;	
	}else if (matriz[0][2] == 'X' && matriz[1][1]  == 'X' && matriz[2][0] == 'X' ){
		ganhou = 1;	
	}else if(matriz[0][0] == 'O' && matriz[0][1]  == 'O' && matriz[0][2] == 'O' ){
		ganhou = 2;
	}else if (matriz[1][0] == 'O' && matriz[1][1]  == 'O' && matriz[1][2] == 'O' ){
		ganhou = 2;	
	}else if (matriz[2][0] == 'O' && matriz[2][1]  == 'O' && matriz[2][2] == 'O' ){
		ganhou = 2;	
	}else if (matriz[0][0] == 'O' && matriz[1][0]  == 'O' && matriz[2][0] == 'O' ){
		ganhou = 2;	
	}else if (matriz[0][1] == 'O' && matriz[1][1]  == 'O' && matriz[2][1] == 'O' ){
		ganhou = 2;	
	}else if (matriz[0][2] == 'O' && matriz[1][2]  == 'O' && matriz[2][2] == 'O' ){
		ganhou = 2;	
	}else if (matriz[0][0] == 'O' && matriz[1][1]  == 'O' && matriz[2][2] == 'O' ){
		ganhou = 2;	
	}else if (matriz[0][2] == 'O' && matriz[1][1]  == 'O' && matriz[2][0] == 'O' ){
		ganhou = 2;	
	}else{
		if(contador == 9 && ganhou == false){
			printf("EMPATE\n");
			p_empate++;
			fim = true;
		} 
	}if(ganhou == 1){
		
			printf("PLAYER 1 VENCEDOR!\n");
			p_player1++;	
		}else if(ganhou == 2 ){
		printf("PLAYER 2 VENCEDOR!\n");
		p_player2++;
	}
}

	
	

	
	
	

