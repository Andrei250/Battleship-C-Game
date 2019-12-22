#include <stdio.h>

int main() {
	FILE *fila;
	fila = fopen("existaJoc.txt" , "w");

	if (fila != NULL) {
		fputc('1',fila);
		fputc('\n',fila);
		fclose(fila);	
	}
}
// for(int i = 0; i < 10; ++i)
	// {
	// 	printf("[");
	// 	for ( int j = 0; j < 10; ++j){
	// 			printf("%d ", PC.Mat[i][j] );
	// 	}
	// 	printf("]\n");
	// }

	// for(int i = 0; i < 10; ++i)
	// 	printf("%d ",PC.Directie[i] );
	// printf("\n");

	// for(int i = 0; i < 10; ++i)
	// 	printf("%d ",PC.StartI[i] );
	// printf("\n");

	// for(int i = 0; i < 10; ++i)
	// 	printf("%d ",PC.StartJ[i] );
	// printf("\n");

	// printf("\n");


	// for (int k = 0; k < dimensiune; ++k)
	// {
	// 	for(int i = 0; i < 10; ++i)
	// 	{
	// 		printf("[");
	// 		for ( int j = 0; j < 10; ++j){
	// 				printf("%d ", Nou[k].Mat[i][j] );
	// 		}
	// 		printf("]\n");
	// 	}

	// 	for(int i = 0; i < 10; ++i)
	// 		printf("%d ",Nou[k].Directie[i] );
	// 	printf("\n");

	// 	for(int i = 0; i < 10; ++i)
	// 		printf("%d ",Nou[k].StartI[i] );
	// 	printf("\n");

	// 	for(int i = 0; i < 10; ++i)
	// 		printf("%d ",Nou[k].StartJ[i] );
	// 	printf("\n");

	// 	for(int i = 0; i < 10; ++i)
	// 		printf("%d ",Nou[k].Vap[i] );
	// 	printf("\n");

	// 	for(int i = 0; i < 10; ++i)
	// 		printf("%d ",Nou[k].Ships[i] );
	// 	printf("\n");
	// }
		
	// printf("\n");

	// for(int i = 0; i < 10; ++i)
	// {
	// 	printf("[");
	// 	for ( int j = 0; j < 10; ++j){
	// 			printf("%d ", Player.Mat[i][j] );
	// 	}
	// 	printf("]\n");
	// }