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