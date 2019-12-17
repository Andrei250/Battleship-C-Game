#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


int randomize()
{
	return rand() % 10;
}

int checks(int cornerLefti, int cornerLeftj, int cornerRighti, int cornerRightj, int **Matrix) {
	int index, jindex;

	for (index = cornerLefti; index <= cornerRighti; ++index) {
		for (jindex = cornerLeftj; jindex <= cornerRightj; ++jindex) {
			if (Matrix[index][jindex] != 0 && Matrix[index][jindex] != -1) {
				return 0;
			}
		}
	}

	return 1;

}

void genereaza(int **Matrix, int Nave[]) {
	int i, index, jindex;

	for (i = 0; i < 10; ++i) {
		int checker = 1;

		while (checker) {
			index = randomize();
			jindex = randomize();

			if(Matrix[index][jindex] == 0){
			if (index + Nave[i] < 10) {
				int i1, j1, i2, j2; 
				i1 = fmax(0, index - 1);
				j1 = fmax(0, jindex - 1);
				i2 = fmin(9, index + Nave[i]);
				j2 = fmin(9, jindex + 1);

				if ( checks(i1, j1, i2, j2, Matrix)) {
					int j, w, k;

					for (w = i1; w <= i2; ++w) {
						for (k = j1; k <= j2; ++k) {
							Matrix[w][k] = -1;
						}
					}

					for (j = 0; j < Nave[i]; ++j) {
						Matrix[index + j][jindex] = Nave[i];
					}

					checker = 0;

				}
			} 

			if( checker && jindex + Nave[i] < 10) {
				int i1, j1, i2, j2; 
				i1 = fmax(0, index - 1);
				j1 = fmax(0, jindex - 1);
				i2 = fmin(9, index + 1);
				j2 = fmin(9, jindex + Nave[i]);

				if ( checks(i1, j1, i2, j2, Matrix)) {
					int j, w, k;

					for (w = i1; w <= i2; ++w) {
						for (k = j1; k <= j2; ++k) {
							Matrix[w][k] = -1;
						}
					}

					for (j = 0; j < Nave[i]; ++j) {
						Matrix[index][jindex + j] = Nave[i];
					}

					checker = 0;				
				}
			}

		}
	 }
	}
}

int main(int arc, char *argv[]) {

	clock_t begin, end;

	int **Matrix;
	time_t t;
	srand((unsigned) time(&t));

	Matrix = malloc( 10 * sizeof(int *));

	for(int i = 0; i < 10; ++i)
		Matrix[i] = malloc(10 * sizeof(int));

	int Nave[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

	for (int i = 0; i < 10; ++i)
		for(int j = 0; j < 10; ++j)
			Matrix[i][j] = 0;

	begin = clock();

	genereaza(Matrix, Nave);

	end = clock();

	printf("%lf\n",(double)(end - begin ) / CLOCKS_PER_SEC );


	return 0;
}