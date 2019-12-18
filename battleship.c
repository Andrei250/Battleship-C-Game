#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#define BACKGROUND_PAIR 1
#define MATRIX_PAIR_1 2
#define MATRIX_PAIR_2 3
#define WHITE_SPACE 4
#define SHIP 5
#define EVIDENTA 6

typedef struct {
	int **Mat;
	int *StartI, *StartJ, *Directie, *Ships, *Vap;
	//directie 2 in jos si 1 la dreapta
} configuratie;

typedef struct{
	int valoare;
	char **elemente;
} textinitial;


void alocare(configuratie *PC) {
	int i;
	(*PC).Mat = malloc(10 * sizeof(int *));
	(*PC).Directie = malloc(10 * sizeof(int));
	(*PC).StartI = malloc(10 * sizeof(int));
	(*PC).StartJ = malloc(10 * sizeof(int));
	(*PC).Ships = malloc(10 * sizeof(int));
	(*PC).Vap = malloc(10 * sizeof(int));
	(*PC).Vap[0] = (*PC).Ships[0] = 4;
	(*PC).Vap[1] = (*PC).Ships[1] = 3;
	(*PC).Vap[2] = (*PC).Ships[2] = 3;
	(*PC).Vap[3] = (*PC).Ships[3] = 2;
	(*PC).Vap[4] = (*PC).Ships[4] = 2;
	(*PC).Vap[5] = (*PC).Ships[5] = 2;
	(*PC).Vap[6] = (*PC).Ships[6] = 1;
	(*PC).Vap[7] = (*PC).Ships[7] = 1;
	(*PC).Vap[8] = (*PC).Ships[8] = 1;
	(*PC).Vap[9] = (*PC).Ships[9] = 1;
	
	for (i = 0; i < 10; ++i)
	{
		(*PC).Mat[i] = malloc(10 * sizeof(int));
	}
}

//returneaza o valoare random intre 0 si 10
int randomize()
{
	return rand() % 10;
}

//initializez interfata jocului
void initWindows(int nrows, int ncols)
{
	int r, c;
	r = c = 0;

	start_color();
	init_pair(BACKGROUND_PAIR, COLOR_WHITE, COLOR_CYAN);
	attron(COLOR_PAIR(BACKGROUND_PAIR));

	while ( r < nrows)
	{

		while (c < ncols)
		{
			move(r,c);
			delch();
			insch(' ');
			c++;
		}

		c = 0;
		r++;

	}
	refresh();
	attroff(COLOR_PAIR(BACKGROUND_PAIR));
	move(0, 0);

}

//initializez meniul de inceput cu new game, resume game si quit
void initText(char **elements, int linieText, int coloanaText, int poz, int number)
{
	char *item;
	int i;
	// int i, linieText, coloanaText;
	// linieText = nrows / 3;
	// coloanaText = ncols / 2 - 10;
	char Pointer = (char) 62; 
	for (i = 0; i < number; ++i)
	{
		item = strdup(elements[i]);

		if ( i == poz)
			{
				attron(A_STANDOUT);
			}
		else
			{
				attroff(A_STANDOUT);
				start_color();
				init_pair(BACKGROUND_PAIR,COLOR_WHITE, COLOR_CYAN);
				attron(COLOR_PAIR(BACKGROUND_PAIR));

			}

		if ( i == poz)
		{
			move(linieText, coloanaText - 2);
			addch(Pointer);
			move(linieText, coloanaText - 1);
			addch(' ');
			mvaddstr(linieText, coloanaText, item);
			move(linieText, coloanaText + strlen(item));
			addch(' ');
		} else
		{
			move(linieText, coloanaText - 2);
			addch(' ');
			move(linieText, coloanaText - 1);
			addch(' ');
			mvaddstr(linieText, coloanaText, item);
			move(linieText, coloanaText + strlen(item));
			addch(' ');
		}

		linieText += 3;
		attroff(COLOR_PAIR(BACKGROUND_PAIR));
		attroff(A_STANDOUT);
	}

	free(item);
	move(0, 0);
}

//verific daca aria unui dreptunghi contine doar 0 si -1
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

//generez mapa random a calcualtorului si a jucatorului cand apasa R
void genereaza(configuratie PC) {
	int i, index, jindex;
	for (index = 0; index < 10; ++ index) {
		for (jindex = 0; jindex < 10; ++ jindex) {
			PC.Mat[index][jindex] = 0;
		}
	}

	for (i = 0; i < 10; ++i) {
		PC.Vap[i] = PC.Ships[i];
		if (PC.Ships[i]) {
			int checker = 1;

			while (checker) {
				index = randomize();
				jindex = randomize();

				if(PC.Mat[index][jindex] == 0){

				if (index + PC.Ships[i] - 1 < 10) { // jos
					int i1, j1, i2, j2; 
					i1 = fmax(0, index - 1);
					j1 = fmax(0, jindex - 1);
					i2 = fmin(9, index + PC.Ships[i]);
					j2 = fmin(9, jindex + 1);

					if ( checks(i1, j1, i2, j2, PC.Mat)) {
						int j, w, k;

						for (w = i1; w <= i2; ++w) {
							for (k = j1; k <= j2; ++k) {
								PC.Mat[w][k] = -1;
							}
						}

						for (j = 0; j < PC.Ships[i]; ++j) {
							PC.Mat[index + j][jindex] = i + 1;
						}

						PC.Directie[i] = 2;
						PC.StartI[i] = index;
						PC.StartJ[i] = jindex;
						checker = 0;

						if (PC.Ships[i] == 1) {
							PC.Directie[i] = 0;
						}

					}
				} 

				if( checker && jindex + PC.Ships[i] - 1 < 10) { // dreapta
					int i1, j1, i2, j2; 
					i1 = fmax(0, index - 1);
					j1 = fmax(0, jindex - 1);
					i2 = fmin(9, index + 1);
					j2 = fmin(9, jindex + PC.Ships[i]);

					if ( checks(i1, j1, i2, j2, PC.Mat)) {
						int j, w, k;

						for (w = i1; w <= i2; ++w) {
							for (k = j1; k <= j2; ++k) {
								PC.Mat[w][k] = -1;
							}
						}

						for (j = 0; j < PC.Ships[i]; ++j) {
							PC.Mat[index][jindex + j] = i + 1;
						}

						PC.Directie[i] = 1;
						PC.StartI[i] = index;
						PC.StartJ[i] = jindex;
						checker = 0;	

						if (PC.Ships[i] == 1) {
							PC.Directie[i] = 0;
						}			
					}
				}


			}
		 }
		}
	}

	int j;

	for (i = 0; i < 10; ++i) {
    	for (j = 0; j < 10; ++j) {
    		PC.Mat[i][j] = fmax(PC.Mat[i][j] , 0);
    	}
    }
}

//afisez configuratia in format mic
void showConfig(int **Mat, int linieText, int coloanaText) {
	int i, j;
	start_color();
	init_pair(MATRIX_PAIR_1, COLOR_BLACK, COLOR_BLACK);
	init_pair(MATRIX_PAIR_2, COLOR_WHITE, COLOR_WHITE);
	init_pair(SHIP, COLOR_RED, COLOR_RED);
	init_pair(WHITE_SPACE, COLOR_MAGENTA, COLOR_MAGENTA);

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			move(linieText + i, coloanaText + 2 * j);
			if (Mat[i][j] > 0) {
				attron(COLOR_PAIR(MATRIX_PAIR_1));
				addch(' ');
				move(linieText + i, coloanaText + 2 * j + 1);
				addch(' ');
				attroff(COLOR_PAIR(MATRIX_PAIR_1));
			} else if (Mat[i][j] == 0) {
				attron(COLOR_PAIR(MATRIX_PAIR_2));
				addch(' ');
				move(linieText + i, coloanaText + 2 * j + 1);
				addch(' ');
				attroff(COLOR_PAIR(MATRIX_PAIR_2));
			} else if (Mat[i][j] == -1) { // nava ratata
				attron(COLOR_PAIR(WHITE_SPACE));
				addch(' ');
				move(linieText + i, coloanaText + 2 * j + 1);
				addch(' ');
				attroff(COLOR_PAIR(WHITE_SPACE));
			} else if (Mat[i][j] == -2) { // nava nimerita
				attron(COLOR_PAIR(SHIP));
				addch(' ');
				move(linieText + i, coloanaText + 2 * j + 1);
				addch(' ');
				attroff(COLOR_PAIR(SHIP));
			}
			refresh();
		}

	}

	move(0, 0);
}

//afisez configuratia in format mare
void showConfigBig(int **Mat, int linieText, int coloanaText) {
	int i, j;
	start_color();
	init_pair(MATRIX_PAIR_1, COLOR_BLACK, COLOR_BLACK);
	init_pair(MATRIX_PAIR_2, COLOR_WHITE, COLOR_WHITE);
	init_pair(SHIP, COLOR_RED, COLOR_RED);
	init_pair(WHITE_SPACE, COLOR_MAGENTA, COLOR_MAGENTA);

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			move(linieText + 2 * i, coloanaText + 4 * j);
			if (Mat[i][j] > 0) {
				attron(COLOR_PAIR(MATRIX_PAIR_1));
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 3);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 3);
				addch(' ');
				attroff(COLOR_PAIR(MATRIX_PAIR_1));
			} else if (Mat[i][j] == 0) {
				attron(COLOR_PAIR(MATRIX_PAIR_2));
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 3);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 3);
				addch(' ');
				attroff(COLOR_PAIR(MATRIX_PAIR_2));
			} else if (Mat[i][j] == -1) { // nava ratata
				attron(COLOR_PAIR(WHITE_SPACE));
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 3);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 3);
				addch(' ');
				attroff(COLOR_PAIR(WHITE_SPACE));
			} else if (Mat[i][j] == -2) { // nava nimerita
				attron(COLOR_PAIR(SHIP));
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 3);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 3);
				addch(' ');
				attroff(COLOR_PAIR(SHIP));
			}
			refresh();
		}

	}

	move(0, 0);
}

// afisez matricea PCului
void showConfigPC(int **Mat, int linieText, int coloanaText) {
	int i, j;
	start_color();
	init_pair(MATRIX_PAIR_1, COLOR_BLACK, COLOR_BLACK);
	init_pair(MATRIX_PAIR_2, COLOR_WHITE, COLOR_WHITE);
	init_pair(SHIP, COLOR_RED, COLOR_RED);
	init_pair(WHITE_SPACE, COLOR_MAGENTA, COLOR_MAGENTA);

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			move(linieText + 2 * i, coloanaText + 4 * j);
			if (Mat[i][j] >= 0) {
				attron(COLOR_PAIR(MATRIX_PAIR_2));
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 3);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 3);
				addch(' ');
				attroff(COLOR_PAIR(MATRIX_PAIR_2));
			} else if (Mat[i][j] == -1) { // nava ratata
				attron(COLOR_PAIR(WHITE_SPACE));
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 3);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 3);
				addch(' ');
				attroff(COLOR_PAIR(WHITE_SPACE));
			} else if (Mat[i][j] == -2) { // nava nimerita
				attron(COLOR_PAIR(SHIP));
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i, coloanaText + 4 * j + 3);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 1);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 2);
				addch(' ');
				move(linieText + 2 * i + 1, coloanaText + 4 * j + 3);
				addch(' ');
				attroff(COLOR_PAIR(SHIP));
			}
			refresh();
		}

	}

	move(0, 0);
}

//functie care verifica cand un joc e gata
int Over(int Nave[]) {
	int i;

	for (i = 0; i < 10; ++i) {
		if (Nave[i]) {
			return 0;
		}
	}

	return 1;
}

//functie care ocupa spatiile de langa o nava cand a fost distrusa in totalitate
void acopera(configuratie Con, int ind) {
	int k, w, i1, j1, i2, j2;

	if (Con.Directie[ind] == 0) {
		i1 = fmax(Con.StartI[ind] - 1, 0);
		j1 = fmax(Con.StartJ[ind] - 1, 0);
		i2 = fmin(Con.StartI[ind] + 1, 9);
		j2 = fmin(Con.StartJ[ind] + 1, 9);

		for (k = i1; k <= i2; ++ k) {
			for (w = j1; w <= j2; ++ w) {
				if (Con.Mat[k][w] != -2) {
					Con.Mat[k][w] = -1;
				}
			}
		}

	} else if (Con.Directie[ind] == 1) { // dreapta
		i1 = fmax(Con.StartI[ind] - 1, 0);
		j1 = fmax(Con.StartJ[ind] - 1, 0);
		i2 = fmin(Con.StartI[ind] + 1, 9);
		j2 = fmin(Con.StartJ[ind] + Con.Vap[ind], 9);

		for (k = i1; k <= i2; ++ k) {
			for (w = j1; w <= j2; ++ w) {
				if (Con.Mat[k][w] != -2) {
					Con.Mat[k][w] = -1;
				}
			}
		}
	} else if (Con.Directie[ind] == 2) { // jos
		i1 = fmax(Con.StartI[ind] - 1, 0);
		j1 = fmax(Con.StartJ[ind] - 1, 0);
		i2 = fmin(Con.StartI[ind] + Con.Vap[ind], 9);
		j2 = fmin(Con.StartJ[ind] + 1, 9);

		for (k = i1; k <= i2; ++ k) {
			for (w = j1; w <= j2; ++ w) {
				if (Con.Mat[k][w] != -2) {
					Con.Mat[k][w] = -1;
				}
			}
		}
	}

}

//randul PCului
void PCTurn(configuratie Jucator, int Linie, int ColoanaJuc) {
	int lin, col;
	int checker = 1;

	while (checker) {
		lin = randomize();
		col = randomize();

		while (Jucator.Mat[lin][col] == -1 || Jucator.Mat[lin][col] == -2) {
			lin = randomize();
			col = randomize();
		}

		if (Jucator.Mat[lin][col] > 0) {
			Jucator.Ships[ Jucator.Mat[lin][col] - 1 ] --;

			if (Jucator.Ships[ Jucator.Mat[lin][col] - 1 ] == 0) {
				acopera(Jucator, Jucator.Mat[lin][col] - 1);
			}

			Jucator.Mat[lin][col] = -2;
		} else {
			Jucator.Mat[lin][col] = -1;
			checker = 0;
		}

		showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
		sleep(3);

	}

}

//colorez o celula
void coloreazaCelula(int i, int j, int linieText, int coloanaText) {
	init_pair(EVIDENTA, COLOR_YELLOW, COLOR_YELLOW);
	attron(COLOR_PAIR(EVIDENTA));
	move(linieText + 2 * i, coloanaText + 4 * j);
	addch(' ');
	move(linieText + 2 * i, coloanaText + 4 * j + 1);
	addch(' ');
	move(linieText + 2 * i, coloanaText + 4 * j + 2);
	addch(' ');
	move(linieText + 2 * i, coloanaText + 4 * j + 3);
	addch(' ');
	move(linieText + 2 * i + 1, coloanaText + 4 * j);
	addch(' ');
	move(linieText + 2 * i + 1, coloanaText + 4 * j + 1);
	addch(' ');
	move(linieText + 2 * i + 1, coloanaText + 4 * j + 2);
	addch(' ');
	move(linieText + 2 * i + 1, coloanaText + 4 * j + 3);
	addch(' ');
	attroff(COLOR_PAIR(EVIDENTA));
}

//distruge 10 spatii aleatorii
int distruge(configuratie PC, configuratie Jucator, int ColoanaPC) {
	int i1, j1, i2, j2, counter = 0;

	while (counter < 10) {
		counter ++; 

		i1 = randomize();
		j1 = randomize();

		while (PC.Mat[i1][j1] < 0) {
			i1 = randomize();
			j1 = randomize();
		}

		i2 = randomize();
		j2 = randomize();

		while (Jucator.Mat[i2][j2] < 0) {
			i2 = randomize();
			j2 = randomize();
		}

		if (PC.Mat[i1][j1] > 0) {
			PC.Ships[ PC.Mat[i1][j1] - 1 ] --;

			if (PC.Ships[ PC.Mat[i1][j1] - 1 ]) {
				acopera(PC, PC.Mat[i1][j1] - 1);
			}

			PC.Mat[i1][j1] = -2;
		} else {
			PC.Mat[i1][j1] = -1;
		}

		if (Jucator.Mat[i2][j2] > 0) {
			Jucator.Ships[ Jucator.Mat[i2][j2] - 1 ] --;

			if (Jucator.Ships[ Jucator.Mat[i2][j2] - 1 ] == 0) {
				acopera(Jucator, Jucator.Mat[i2][j2] - 1);
			}

			Jucator.Mat[i2][j2] = -2;
		} else {
			Jucator.Mat[i2][j2] = -1;
		}

		showConfigBig(Jucator.Mat, 15, 25);
		showConfigPC(PC.Mat, 15, ColoanaPC);
		sleep(1);

		if (Over(PC.Ships) && Over(Jucator.Ships)) {
			return 3;
		} else if (Over(PC.Ships)) {
			return 2;
		} else if (Over(Jucator.Ships)) {
			return 1;
		}


	}

	return 0;

}

void retine(configuratie PC, configuratie Jucator) {
	FILE *fila;
	fila = fopen("existaJoc.txt" , "w");

	if (fila != NULL) {
		int i, j;
		char *string;
		char number[3];
		string = malloc(30 * sizeof(char));
		fputc('1',fila);
		fputc('\n',fila);

		//salvez configuratia pcului
		for (i = 0; i < 10; ++ i) {
			string[0] = '\0';

			for (j = 0; j < 10; ++ j) {
				sprintf(number, "%d ", PC.Mat[i][j]);
				strcat(string, number);
			}

			fputs(string, fila);
			fputc('\n',fila);
		}

		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.StartI[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.StartJ[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.Directie[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.Ships[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.Vap[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);


		//salvez configuratia jucatorului
		for (i = 0; i < 10; ++ i) {
			string[0] = '\0';

			for (j = 0; j < 10; ++ j) {
				sprintf(number, "%d ", Jucator.Mat[i][j]);
				strcat(string, number);
			}

			fputs(string, fila);
			fputc('\n',fila);
		}

		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.StartI[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.StartJ[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.Directie[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.Ships[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.Vap[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n',fila);
	}

}

//incep un nou joc
void startGame(configuratie PC, configuratie Jucator, WINDOW *terminal) {
	int i, j, nrows, ncols, d;
	getmaxyx(terminal, nrows, ncols);
	initWindows(nrows, ncols);
	int caracter, raspuns;

	int Linie = 15, ColoanaJuc = 25, ColoanaPC = ncols - 65;
	showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
	showConfigPC(PC.Mat, Linie, ColoanaPC);
	int checker = 1, turn = 1;
	i = j = 0;
	coloreazaCelula(i, j, Linie, ColoanaPC);

	while(checker) {
		if (turn == 1) { // jucator
			coloreazaCelula(i, j, Linie, ColoanaPC);
			if ((d = getch())) {
				switch(d){
					case KEY_DOWN:
								i++;
								i = ( i > 9) ? 0 : i;
								break;
					case KEY_UP:
								i--;
								i = ( i < 0) ? 9 : i;
								break;
					case KEY_RIGHT:
								j++;
								j = ( j > 9) ? 0 : j;
								break;
					case KEY_LEFT:
								j--;
								j = ( j < 0) ? 9 : j;
								break;  
					case 10:
								if (PC.Mat[i][j] != -1 && PC.Mat[i][j] != -2) {
									if (PC.Mat[i][j] > 0) {
										PC.Ships[ PC.Mat[i][j] - 1 ] --;

										if (PC.Ships[ PC.Mat[i][j] - 1 ]) {
											acopera(PC, PC.Mat[i][j] - 1);
										}

										PC.Mat[i][j] = -2;
									} else {
										PC.Mat[i][j] = -1;
										turn = 2;
									}
								}
								break;
					case 'q':
								//design
								caracter = getch();
								while (caracter != 'Y' && caracter != 'N' && caracter != 'y' && caracter != 'n') {
									caracter = getch();
								}
								if (caracter == 'Y' || caracter == 'y') {
									retine(PC, Jucator);
									checker = 0;
								}
								break;
					case 'Q':
								//design
								caracter = getch();
								while (caracter != 'Y' && caracter != 'N' && caracter != 'y' && caracter != 'n') {
									caracter = getch();
								}
								if (caracter == 'Y' || caracter == 'y') {
									retine(PC, Jucator);
									checker = 0;
								}
								break;
					case 'D':
								raspuns = distruge(PC, Jucator, ColoanaPC);
								if (raspuns > 0) {
									//verificam in functie de care
									checker = 0;
								}
								break;
					case 'd':
								raspuns = distruge(PC, Jucator, ColoanaPC);
								if (raspuns > 0) {
									//verificam in functie de care
									checker = 0;
								}
								break;
					case 'R':
								genereaza(Jucator);
								break;
					case 'r':
								genereaza(Jucator);
								break;
				}
			}	
			showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
			showConfigPC(PC.Mat, Linie, ColoanaPC);
			if (turn == 1) {
				coloreazaCelula(i, j, Linie, ColoanaPC);	
			}
			
		} else { // calculator
			PCTurn(Jucator, Linie, ColoanaJuc);
			showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
			showConfigPC(PC.Mat, Linie, ColoanaPC);
			turn = 1;
		}
		
		
	}

}

// copiez o configuratie
void Copiere(configuratie Unu, configuratie Doi) {
	int i, j;

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			Unu.Mat[i][j] = Doi.Mat[i][j];
		}
	}

	for (i = 0; i < 10; ++ i) {
		Unu.Directie[i] = Doi.Directie[i];
		Unu.StartI[i] = Doi.StartI[i];
		Unu.StartJ[i] = Doi.StartJ[i];
		Unu.Ships[i] = Doi.Ships[i];
		Unu.Vap[i] = Doi.Vap[i];
	}

}

// generez meniul cu configuratii vechi
void OldConfig(configuratie PC, configuratie *Configuratii, int marime, WINDOW *terminal) {
	int i, nrows, ncols;
	char **meniulVechi;
	configuratie Salvare;
    alocare(&Salvare);

	meniulVechi = malloc((marime + 1) * sizeof(char *));

	getmaxyx(terminal, nrows, ncols);
	initWindows(nrows, ncols);

	int linieText, coloanaText;
	linieText = nrows / 3;
	coloanaText = ncols / 2 - 10;

	for (i = 0; i < marime; ++i) {
		char buffer[30];
		sprintf(buffer, "Configuration number %d", i + 1);
		meniulVechi[i] = strdup(buffer);
	}

	meniulVechi[marime] = strdup("Go back to main menu");

	int checker = 1, d;
    i = 0;
    initText(meniulVechi, linieText, coloanaText, 0, marime + 1);

    if (marime > 0) {
    	showConfig(Configuratii[0].Mat, 3, 3);
    }

    while (checker)
	{
		if ((d = getch())) {
			switch( d ){
				case KEY_DOWN:
							i++;
							i = ( i > marime) ? 0 : i;
							break;
				case KEY_UP:
							i--;
							i = ( i < 0) ? marime : i;
							break; 
				case 10:
							if (i == marime) {
								checker = 0;
							} else if (i < marime) {
								Copiere(Salvare, Configuratii[i]);
								startGame(PC, Salvare, terminal);
							}
							break;
				case 'q':
							checker = 0;
							break;
				case 'Q':
							checker = 0;
			}
		}	
		getmaxyx(terminal, nrows, ncols);
		initWindows(nrows, ncols);
	  	initText(meniulVechi, linieText, coloanaText, i, marime + 1);

	  	if (i < marime) {
	  		showConfig(Configuratii[i].Mat, 3, 3);
	  	}

	}

}

//generez meniul cu configuratii
void NewGame(configuratie PC, configuratie *Configuratii, int marime, configuratie *Nou, int dimensiune, WINDOW *terminal) {
    genereaza(PC);
    int i, nrows, ncols;
    configuratie Salvare;
    alocare(&Salvare);

	getmaxyx(terminal, nrows, ncols);
	initWindows(nrows, ncols);

	int linieText, coloanaText;
	linieText = nrows / 3;
	coloanaText = ncols / 2 - 10;

	char **meniulNou;

	meniulNou = malloc((dimensiune + 2) * sizeof(char *));

	for (i = 0; i < dimensiune; ++i) {
		char buffer[30];
		sprintf(buffer, "Configuration number %d", i + 1);
		meniulNou[i] = strdup(buffer);
	}

	meniulNou[dimensiune] = strdup("Choose an old configuration");
    meniulNou[dimensiune + 1] = strdup("Go back to main menu");

    int checker = 1, d;
    i = 0;
    initText(meniulNou, linieText, coloanaText, 0, dimensiune + 2);

    if (dimensiune > 0) {
	  	showConfig(Nou[0].Mat, 3, 3);
	}

    while (checker)
	{
		if ((d = getch())) {
			switch( d ){
				case KEY_DOWN:
							i++;
							i = ( i > dimensiune + 1) ? 0 : i;
							break;
				case KEY_UP:
							i--;
							i = ( i < 0) ? (dimensiune + 1) : i;
							break; 
				case 10:
							if (i == dimensiune + 1) {
								checker = 0;
							} else if (i == dimensiune) {
								OldConfig(PC, Configuratii, marime, terminal);
							} else if (i < dimensiune) {
								Copiere(Salvare, Nou[i]);
								startGame(PC, Salvare, terminal);
							}
							break;
				case 'q':
							checker = 0;
							break;
				case 'Q':
							checker = 0;
			}
		}	
		getmaxyx(terminal, nrows, ncols);
		initWindows(nrows, ncols);
	  	initText(meniulNou, linieText, coloanaText, i, dimensiune + 2);

	  	if (i < dimensiune) {
	  		showConfig(Nou[i].Mat, 3, 3);
	  	}

	}

}

//citesc configuratiile vechi si noi ale jucatorului din fisiere
void readData(int *hasGame, configuratie **Configuratii, int *marime, int argc, char *argv[], configuratie **Nou, int *dimensiune) {
	FILE *fila;
	fila = fopen("existaJoc.txt" , "r");

	if (fila == NULL) {
		*hasGame = 0;	
	} else {
		char *sr;
		sr = malloc(4 * sizeof(char));
		fgets(sr, 4, fila);
		*hasGame = sr[0] - '0';
		fclose(fila);
	}

	fila = fopen("configuratii.txt", "r");

	if (fila != NULL) {
		char *sr;
		sr = malloc(40 * sizeof(char));
		fgets(sr, 40, fila);
		*marime = sr[0] - '0';
		int i, j, k;
		*Configuratii = malloc(*marime * sizeof(configuratie));

		for (i = 0; i < *marime; ++i) {
			alocare(&(*Configuratii)[i]);
		}

		for (i = 0; i < *marime; ++i) {
			char *p;

			for (j = 0; j < 10; ++j) {
				fgets(sr, 40, fila);
				p = strtok(sr, " ");
				k = 0;

				while (p) {
					(*Configuratii)[i].Mat[j][k ++] = atoi(p);
					p = strtok(NULL, " ");
				}
			}

			fgets(sr, 40, fila);
			p = strtok(sr, " ");
			k = 0;

			while (p) {
				(*Configuratii)[i].Directie[k ++] = atoi(p);
				p = strtok(NULL, " ");
			}

			fgets(sr, 40, fila);
			p = strtok(sr, " ");
			k = 0;

			while (p) {
				(*Configuratii)[i].StartI[k ++] = atoi(p);
				p = strtok(NULL, " ");
			}

			fgets(sr, 40, fila);
			p = strtok(sr, " ");
			k = 0;

			while (p) {
				(*Configuratii)[i].StartJ[k ++] = atoi(p);
				p = strtok(NULL, " ");
			}
		}

		free(sr);
		fclose(fila);
	} else {
		*marime = 0;
	}

	int i, j;
	*dimensiune = argc - 1;
	if (*dimensiune) {
		*Nou = malloc(*dimensiune * sizeof(configuratie));

		for (i = 0; i < *dimensiune; ++i) {
			alocare(&(*Nou)[i]);
		}
	}

	for (i = 1; i < argc; ++i) {
		fila = fopen(argv[i], "r");

		if (fila != NULL) {
			for (j = 0; j < 10; ++j) {
				char *sr, *p;
				sr = malloc(35 * sizeof(char));
				char separator[] = "|\n";
				fgets(sr, 35, fila);
				p = strtok(sr, separator);
				int counter = 0;

				while (p) {
					if (strcmp(p," ") == 0) {
						(*Nou)[i - 1].Mat[j][counter++] =  0;
					} else if (strcmp(p, "X") == 0) {
						(*Nou)[i - 1].Mat[j][counter++] =  -1;
					}

					p = strtok(NULL, separator);
				}

				free(sr);
			}

			int k = 0, unu = 0, doi = 0, trei = 0;

			for (j = 0; j < 10; ++j) {
				for (k = 0; k < 10; ++k) {
					if ((*Nou)[i - 1].Mat[j][k] == -1) {
						int counter = 1;
						int directie = 0;
						int pozitie = k;

						while (pozitie < 9 && (*Nou)[i - 1].Mat[j][pozitie + 1] == -1) {
							counter ++;
							pozitie ++;
							directie = 1;
						}

						pozitie = j;

						while(pozitie < 9 && (*Nou)[i - 1].Mat[pozitie + 1][k] == -1) {
							counter ++;
							pozitie ++;
							directie = 2;
						}

						if (directie == 1) {
							pozitie = k;

							if (counter == 4) {
								while (pozitie < 10 && (*Nou)[i - 1].Mat[j][pozitie] == -1) {
									(*Nou)[i - 1].Mat[j][pozitie] = 1;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[0] = 1;
								(*Nou)[i - 1].StartI[0] = j;							
								(*Nou)[i - 1].StartJ[0] = k;
							} else if (counter == 3) {

								while (pozitie < 10 && (*Nou)[i - 1].Mat[j][pozitie] == -1) {
									(*Nou)[i - 1].Mat[j][pozitie] = 2 + trei;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[2 + trei - 1] = 1;
								(*Nou)[i - 1].StartI[2 + trei - 1] = j;							
								(*Nou)[i - 1].StartJ[2 + trei - 1] = k;
								trei ++;

							} else if (counter == 2) {

								while (pozitie < 10 && (*Nou)[i - 1].Mat[j][pozitie] == -1) {
									(*Nou)[i - 1].Mat[j][pozitie] = 4 + doi;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[4 + doi - 1] = 1;
								(*Nou)[i - 1].StartI[4 + doi - 1] = j;							
								(*Nou)[i - 1].StartJ[4 + doi - 1] = k;
								doi ++;
							}


						} else if (directie == 2) {
							pozitie = j;

							if (counter == 4) {
								while (pozitie < 10 && (*Nou)[i - 1].Mat[j][pozitie] == -1) {
									(*Nou)[i - 1].Mat[j][pozitie] = 1;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[0] = 2;
								(*Nou)[i - 1].StartI[0] = j;							
								(*Nou)[i - 1].StartJ[0] = k;
							} else if (counter == 3) {

								while (pozitie < 10 && (*Nou)[i - 1].Mat[pozitie][k] == -1) {
									(*Nou)[i - 1].Mat[pozitie][k] = 2 + trei;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[2 + trei - 1] = 2;
								(*Nou)[i - 1].StartI[2 + trei - 1] = j;							
								(*Nou)[i - 1].StartJ[2 + trei - 1] = k;
								trei ++;

							} else if (counter == 2) {

								while (pozitie < 10 && (*Nou)[i - 1].Mat[pozitie][k] == -1) {
									(*Nou)[i - 1].Mat[pozitie][k] = 4 + doi;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[4 + doi - 1] = 2;
								(*Nou)[i - 1].StartI[4 + doi - 1] = j;							
								(*Nou)[i - 1].StartJ[4 + doi - 1] = k;
								doi ++;
							} 


						} else {
							(*Nou)[i - 1].Mat[j][k] = 7 + unu;
							(*Nou)[i - 1].Directie[7 + unu - 1] = 0;
							(*Nou)[i - 1].StartI[7 + unu - 1] = j;							
							(*Nou)[i - 1].StartJ[7 + unu - 1] = k;
							unu ++;
						}

					}
				}
			}

		}

		fclose(fila);

	}
}


//main function
int main(int argc, char *argv[])
{
	time_t t;
	srand((unsigned) time(&t));
	int nrows, ncols, d;
	WINDOW *terminal;
	nrows = ncols = 0;
	textinitial meniu[2];
	meniu[0].valoare = 2;
	meniu[1].valoare = 3;
	meniu[0].elemente = malloc(2 * sizeof(char *));
	meniu[0].elemente[0] = strdup("New Game");
	meniu[0].elemente[1] = strdup("Quit(Q)");
	meniu[1].elemente = malloc(3 * sizeof(char *));
	meniu[1].elemente[0] = strdup("New Game");
	meniu[1].elemente[1] = strdup("Resume Game");
	meniu[1].elemente[2] = strdup("Quit(Q)");
	configuratie *Configuratii, *Nou, PC;
	int hasGame = 0, marime = 0, dimensiune = 0;
	readData(&hasGame, &Configuratii, &marime, argc, argv, &Nou, &dimensiune);

	terminal = initscr();
    cbreak();
	noecho();
	getmaxyx(terminal, nrows, ncols);
	curs_set(0);
	clear();
	refresh();
	keypad(terminal, TRUE);

	int linieText, coloanaText;
	linieText = nrows / 3;
	coloanaText = ncols / 2 - 10;

	int i = 0;
	int checker = 1;
	alocare(&PC);

	i = 0;

	initWindows(nrows, ncols);
	initText(meniu[hasGame].elemente, linieText, coloanaText, 0, meniu[hasGame].valoare);

	while (checker)
	{	
		if ((d = getch()) != 'Q' && d != 'q') {
			switch( d ){
				case KEY_DOWN:
							i++;
							i = ( i > meniu[hasGame].valoare - 1) ? 0 : i;
							break;
				case KEY_UP:
							i--;
							i = ( i < 0) ? meniu[hasGame].valoare - 1 : i;
							break; 
				case 10:
							if (hasGame == 1) {
								if (i == 0) {
									NewGame(PC, Configuratii, marime, Nou, dimensiune, terminal);
									initWindows(nrows, ncols);
								} else if (i == 1)
								{
									printf("DA\n");
								} else if (i == 2) {
									checker = 0;
								}
							} else {
								if (i == 0) {
									NewGame(PC, Configuratii, marime, Nou, dimensiune, terminal);
									initWindows(nrows, ncols);
								} else if (i == 1) {
									checker = 0;
								}
							}
							break;
			}
		} else if( d == 'Q' || d == 'q') {
			break;
		}

		getmaxyx(terminal, nrows, ncols);
		initWindows(nrows, ncols);
		initText(meniu[hasGame].elemente, linieText, coloanaText, i, meniu[hasGame].valoare);

	}

	endwin();

	for(int i = 0; i < 10; ++i)
	{
		printf("[");
		for ( int j = 0; j < 10; ++j){
				printf("%d ", PC.Mat[i][j] );
		}
		printf("]\n");
	}

	for(int i = 0; i < 10; ++i)
		printf("%d ",PC.Directie[i] );
	printf("\n");

	for(int i = 0; i < 10; ++i)
		printf("%d ",PC.StartI[i] );
	printf("\n");

	for(int i = 0; i < 10; ++i)
		printf("%d ",PC.StartJ[i] );
	printf("\n");

	printf("\n");


	for (int k = 0; k < dimensiune; ++k)
	{
		for(int i = 0; i < 10; ++i)
		{
			printf("[");
			for ( int j = 0; j < 10; ++j){
					printf("%d ", Nou[k].Mat[i][j] );
			}
			printf("]\n");
		}

		for(int i = 0; i < 10; ++i)
			printf("%d ",Nou[k].Directie[i] );
		printf("\n");

		for(int i = 0; i < 10; ++i)
			printf("%d ",Nou[k].StartI[i] );
		printf("\n");

		for(int i = 0; i < 10; ++i)
			printf("%d ",Nou[k].StartJ[i] );
		printf("\n");

		for(int i = 0; i < 10; ++i)
			printf("%d ",Nou[k].Vap[i] );
		printf("\n");

		for(int i = 0; i < 10; ++i)
			printf("%d ",Nou[k].Ships[i] );
		printf("\n");
	}
	

	return 0;
}