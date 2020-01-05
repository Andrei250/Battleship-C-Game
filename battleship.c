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
#define BOX 7
#define BOX2 8

typedef struct {
	int **Mat;
	int *StartI, *StartJ, *Directie, *Ships, *Vap;
	//directie 2 in jos si 1 la dreapta
} configuratie;

typedef struct{
	int valoare;
	char **elemente;
} textinitial;

//dealoc memorie
void dealoca(configuratie C) {
	int i;

	for (i = 0; i < 10; ++i) {
		free(C.Mat[i]);
	}

	free(C.Mat);
	free(C.StartI);
	free(C.StartJ);
	free(C.Directie);
	free(C.Ships);
	free(C.Vap);
}

//initializez navele
void initializare(configuratie PC) {
	PC.Vap[0] = PC.Ships[0] = 4;
	PC.Vap[1] = PC.Ships[1] = 3;
	PC.Vap[2] = PC.Ships[2] = 3;
	PC.Vap[3] = PC.Ships[3] = 2;
	PC.Vap[4] = PC.Ships[4] = 2;
	PC.Vap[5] = PC.Ships[5] = 2;
	PC.Vap[6] = PC.Ships[6] = 1;
	PC.Vap[7] = PC.Ships[7] = 1;
	PC.Vap[8] = PC.Ships[8] = 1;
	PC.Vap[9] = PC.Ships[9] = 1;
}

//aloc memorie pentru o configuratie
void alocare(configuratie *PC) {
	int i;
	(*PC).Mat = malloc(11 * sizeof(int *));
	(*PC).Directie = malloc(11 * sizeof(int));
	(*PC).StartI = malloc(11 * sizeof(int));
	(*PC).StartJ = malloc(11 * sizeof(int));
	(*PC).Ships = malloc(11 * sizeof(int));
	(*PC).Vap = malloc(11 * sizeof(int));
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
	
	for (i = 0; i < 10; ++i) {
		(*PC).Mat[i] = malloc(11 * sizeof(int));
	}
}

//returneaza o valoare random intre 0 si 10
int randomize() {
	return rand() % 10;
}

//initializez interfata colorata jocului
void initWindows(int nrows, int ncols) {
	int r, c;
	r = c = 0;

	start_color();
	init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(BACKGROUND_PAIR));

	while (r < nrows) {

		while (c < ncols) {
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

//initializez meniul de inceput cu new game, resume game, quit,
//scoreboard si info
void initText(char **elements, int linieText,
 int coloanaText, int poz, int number) {
	char *item;
	int i;
	char Pointer = (char) 62; 
	for (i = 0; i < number; ++i) {
		item = strdup(elements[i]);

		if (i == poz) {
				attron(A_STANDOUT);
		} else {
			attroff(A_STANDOUT);
			start_color();
			init_pair(BACKGROUND_PAIR,COLOR_BLACK, COLOR_CYAN);
			attron(COLOR_PAIR(BACKGROUND_PAIR));
		}

		if (i == poz) {
			move(linieText, coloanaText - 2);
			addch(Pointer);
			move(linieText, coloanaText - 1);
			addch(' ');
			mvaddstr(linieText, coloanaText, item);
			move(linieText, coloanaText + strlen(item));
			addch(' ');
		} else {
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
		free(item);
	}
	refresh();
	move(0, 0);
}

//verific daca aria unui dreptunghi contine doar 0 si -1
int checks(int cornerLefti, int cornerLeftj, int cornerRighti,
 int cornerRightj, int **Matrix) {
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

//generez mapa random a calculatorului si a jucatorului cand apasa R
void genereaza(configuratie PC) {
	int i, index, jindex;
	for (index = 0; index < 10; ++index) {
		for (jindex = 0; jindex < 10; ++jindex) {
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

				if (PC.Mat[index][jindex] == 0){

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

				if (checker && jindex + PC.Ships[i] - 1 < 10) { // dreapta
					int i1, j1, i2, j2; 
					i1 = fmax(0, index - 1);
					j1 = fmax(0, jindex - 1);
					i2 = fmin(9, index + 1);
					j2 = fmin(9, jindex + PC.Ships[i]);

					if (checks(i1, j1, i2, j2, PC.Mat)) {
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
    		PC.Mat[i][j] = fmax(PC.Mat[i][j], 0);
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
	init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);

	attron(COLOR_PAIR(BACKGROUND_PAIR));

	for (j = 0; j < 10; ++j) {
		move(linieText - 1, coloanaText + 2 * j + 1);
		addch('0' + j);	
	}

	for (i = 0; i < 10; ++i) {
		move(linieText + i, coloanaText - 1);
		addch('0' + i);
	}

	attroff(COLOR_PAIR(BACKGROUND_PAIR));

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

//afisez configuratia PCului in format mic
void showPC(int **Mat, int linieText, int coloanaText) {
	int i, j;
	start_color();
	init_pair(MATRIX_PAIR_1, COLOR_BLACK, COLOR_BLACK);
	init_pair(MATRIX_PAIR_2, COLOR_WHITE, COLOR_WHITE);
	init_pair(SHIP, COLOR_RED, COLOR_RED);
	init_pair(WHITE_SPACE, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);

	attron(COLOR_PAIR(BACKGROUND_PAIR));

	for (j = 0; j < 10; ++j) {
		move(linieText - 1, coloanaText + 2 * j + 1);
		addch('0' + j);	
	}

	for (i = 0; i < 10; ++i) {
		move(linieText + i, coloanaText - 1);
		addch('0' + i);
	}

	attroff(COLOR_PAIR(BACKGROUND_PAIR));

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			move(linieText + i, coloanaText + 2 * j);
			if (Mat[i][j] >= 0) {
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
	init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(BACKGROUND_PAIR));

	for (j = 0; j < 10; ++j) {
		move(linieText - 1, coloanaText + 4 * j + 2);
		addch('0' + j);	
	}

	for (i = 0; i < 10; ++i) {
		move(linieText + 2 * i, coloanaText - 1);
		addch('0' + i);
	}

	attroff(COLOR_PAIR(BACKGROUND_PAIR));

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
	init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(BACKGROUND_PAIR));

	for (j = 0; j < 10; ++j) {
		move(linieText - 1, coloanaText + 4 * j + 2);
		addch('0' + j);	
	}

	for (i = 0; i < 10; ++i) {
		move(linieText + 2 * i, coloanaText - 1);
		addch('0' + i);
	}

	attroff(COLOR_PAIR(BACKGROUND_PAIR));

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

//functie care ocupa spatiile de langa o nava cand a fost distrusa in 
//totalitate
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

//sterga linia de jos
void stergeLinie(int r, int ncols) {
	int c;
	c = 0;

	start_color();
	init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(BACKGROUND_PAIR));
	while (c < ncols)
	{
		move(r,c);
		delch();
		insch(' ');
		c++;
	}

	refresh();
	attroff(COLOR_PAIR(BACKGROUND_PAIR));
	move(0, 0);
}

//randul PCului
void PCTurn(configuratie Jucator, int Linie, int ColoanaJuc, int nrows,
 int ncols, int *directie, int *numaratoare, int *in, int *jn) {
	int lin, col;
	int checker = 1;
	int peX[] = { -1, 0, 0, 1};
	int peY[] = { 0, -1, 1, 0};

	while (checker) {
		if (*numaratoare == 0) {
			lin = randomize();
			col = randomize();

			while (Jucator.Mat[lin][col] == -1 ||
			 Jucator.Mat[lin][col] == -2) {
				lin = randomize();
				col = randomize();
			}

			if (Jucator.Mat[lin][col] > 0) {
				Jucator.Ships[ Jucator.Mat[lin][col] - 1 ] --;

				if (Jucator.Ships[ Jucator.Mat[lin][col] - 1 ] == 0) {
					acopera(Jucator, Jucator.Mat[lin][col] - 1);
					*directie = 0;
					*numaratoare = 0;
				} else {
					*directie = 0;
					*numaratoare = 1;
					*in = lin;
					*jn = col;
				}

				Jucator.Mat[lin][col] = -2;

			} else {
				Jucator.Mat[lin][col] = -1;
				checker = 0;
			}
		} else {
			lin = *in + *numaratoare * peY[*directie];
			col = *jn + *numaratoare * peX[*directie];
			int verifica = 0;
			while (verifica == 0) {
				while (lin <= 9 && lin >= 0 && col <= 9 && col >= 0) {
					if (Jucator.Mat[lin][col] == -2) {
						*numaratoare = *numaratoare + 1;
						lin = *in + *numaratoare * peY[*directie];
						col = *jn + *numaratoare * peX[*directie];
					} else {
						break;
					}
				}

				while ((lin > 9 || lin < 0 || col > 9 || col < 0) || 
					Jucator.Mat[lin][col] == -1) {
					*directie = (*directie  + 3) % 4;
					*numaratoare = 1;
					lin = *in + *numaratoare * peY[*directie];
					col = *jn + *numaratoare * peX[*directie];	
				}

				if (Jucator.Mat[lin][col] >= 0) {
					verifica = 1;
				}
			}

			if (Jucator.Mat[lin][col] > 0) {
				Jucator.Ships[ Jucator.Mat[lin][col] - 1 ] --;

				if (Jucator.Ships[ Jucator.Mat[lin][col] - 1 ] == 0) {
					acopera(Jucator, Jucator.Mat[lin][col] - 1);
					*directie = 0;
					*numaratoare = 0;
				} else {
					*numaratoare = *numaratoare + 1;
				}

				Jucator.Mat[lin][col] = -2;

			} else {
				Jucator.Mat[lin][col] = -1;
				checker = 0;
				*directie = (*directie + 3) % 4;
				*numaratoare = 1;
			}
		}
		

		if (nrows > 38 && ncols > 132) {
			showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
		} else {
			showConfig(Jucator.Mat, Linie, ColoanaJuc);
		}
		
		if (checker == 1) {
			int numarare = 1;
			while (numarare) {
				stergeLinie(nrows - 3, ncols);
				init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
				attron(COLOR_PAIR(BACKGROUND_PAIR));
				char buffer[35];
				sprintf(buffer, "Urmatoarea mutare in %d secunda", numarare);
				buffer[strlen(buffer)] = '\0';
				mvaddstr(nrows - 3, (ncols - 25) / 2, buffer);
				attroff(COLOR_PAIR(BACKGROUND_PAIR));
				refresh();
				sleep(1);
				numarare --;
			}
		} else {
			int numarare = 3;
			while (numarare) {
				stergeLinie(nrows - 3, ncols);
				init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
				attron(COLOR_PAIR(BACKGROUND_PAIR));
				char buffer[35];
				sprintf(buffer, "Randul vostru urmeaza in %d...", numarare);
				buffer[strlen(buffer)] = '\0';
				mvaddstr(nrows - 3, (ncols - 30) / 2, buffer);
				attroff(COLOR_PAIR(BACKGROUND_PAIR));
				refresh();
				sleep(1);
				numarare --;
			}
		}
		if(Over(Jucator.Ships)) {
			return;
		}

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
	refresh();
}

//colorez celula mica
void coloreazaCelulaM(int i, int j, int linieText, int coloanaText) {
	init_pair(EVIDENTA, COLOR_YELLOW, COLOR_YELLOW);
	attron(COLOR_PAIR(EVIDENTA));
	move(linieText + i, coloanaText + 2 * j);
	addch(' ');
	move(linieText + i, coloanaText + 2 * j + 1);
	addch(' ');
	attroff(COLOR_PAIR(EVIDENTA));
	refresh();
}

//afiseaza scor
void printScore(int nrows, int ncols, int Linie, int Coloana, int score) {
	init_pair(BACKGROUND_PAIR,COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(BACKGROUND_PAIR));
	char buffer[30];
	sprintf(buffer, "Scor: %d", score);
	buffer[strlen(buffer)] = '\0';
	mvaddstr(Linie - 3, Coloana, buffer);
	attroff(COLOR_PAIR(BACKGROUND_PAIR));
	refresh();
}

//distruge 10 spatii aleatorii
int distruge(configuratie PC, configuratie Jucator, int ColoanaPC, int Linie,
 int ColoanaJuc, int nrows, int ncols, int *score) {
	int i1, j1, i2, j2, counter = 0, Bonus = 1;

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
			Bonus ++;

			if (PC.Ships[ PC.Mat[i1][j1] - 1 ] == 0) {
				acopera(PC, PC.Mat[i1][j1] - 1);
				Bonus *= 2;
			}

			PC.Mat[i1][j1] = -2;
		} else {
			PC.Mat[i1][j1] = -1;
			Bonus = 1;
		}

		*score += Bonus;

		if (Jucator.Mat[i2][j2] > 0) {
			Jucator.Ships[ Jucator.Mat[i2][j2] - 1 ] --;

			if (Jucator.Ships[ Jucator.Mat[i2][j2] - 1 ] == 0) {
				acopera(Jucator, Jucator.Mat[i2][j2] - 1);
			}

			Jucator.Mat[i2][j2] = -2;
		} else {
			Jucator.Mat[i2][j2] = -1;
		}

		if (nrows > 38 && ncols > 132) {
			showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
			showConfigPC(PC.Mat, Linie, ColoanaPC);
		} else {
			showConfig(Jucator.Mat, Linie, ColoanaJuc);
			showPC(PC.Mat, Linie, ColoanaPC);
		}
		printScore(nrows, ncols, Linie, ColoanaPC, *score);
		sleep(1);

		if (Over(PC.Ships) && Over(Jucator.Ships)) {
			return 3;
		} else if (Over(PC.Ships)) {
			return 1;
		} else if (Over(Jucator.Ships)) {
			return 2;
		}


	}

	return 0;

}

void retine(configuratie PC, configuratie Jucator) {
	FILE *fila;
	fila = fopen("existaJoc.txt", "w");

	if (fila != NULL) {
		int i, j;
		char *string;
		char number[3];
		fputc('1', fila);
		fputc('\n', fila);
		string = malloc(50 * sizeof(char));
		//salvez configuratia pcului
		for (i = 0; i < 10; ++ i) {
			string[0] = '\0';

			for (j = 0; j < 10; ++ j) {
				sprintf(number, "%d ", PC.Mat[i][j]);
				strcat(string, number);
			}

			fputs(string, fila);
			fputc('\n', fila);
		}

		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.StartI[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.StartJ[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.Directie[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.Ships[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", PC.Vap[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);


		//salvez configuratia jucatorului
		for (i = 0; i < 10; ++ i) {
			string[0] = '\0';

			for (j = 0; j < 10; ++ j) {
				sprintf(number, "%d ", Jucator.Mat[i][j]);
				strcat(string, number);
			}

			fputs(string, fila);
			fputc('\n', fila);
		}

		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.StartI[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.StartJ[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.Directie[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.Ships[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);
		string[0] = '\0';

		for (i = 0; i < 10; ++ i) {
			sprintf(number, "%d ", Jucator.Vap[i]);
			strcat(string, number);
		}
		fputs(string, fila);
		fputc('\n', fila);
		
		free(string);
		fclose(fila);
	}
}

//Meniu de iesire
void ExitMenu(int ncols, int nrows) {	
	start_color();
	init_pair(BOX, COLOR_BLACK, COLOR_CYAN);
	WINDOW *win = newwin(10, ncols / 3, nrows / 2 - 6, ncols / 3);
	box(win, 0, 0);
	wbkgd(win, COLOR_PAIR(BOX));
	attron(COLOR_PAIR(BOX));
	char **elem;
	elem = malloc(3 * sizeof(char *));
	elem[0] = strdup("Do you want to exit?");
	elem[1] = strdup("Yes(Y)");
	elem[2] = strdup("No(N)");
	int v = nrows / 2;
	mvprintw(v - 4, ncols / 3 + (ncols / 3 - 20 ) / 2 , "%s", elem[0]);
	mvprintw(v + 2, ncols / 3 + (ncols / 3 - 11 ) / 3, "%s", elem[1]);
	mvprintw(v + 2, ncols / 3 + 2 * (ncols / 3 - 11 ) / 3 + 7, "%s", elem[2]);
	wrefresh(win);
	attroff(COLOR_PAIR(BOX));
	int i;

	for (i = 0; i < 3; ++i) {
		free(elem[i]);
	}

	free(elem);
}

//jocul e gata
void nuAreJoc() {
	FILE *fila;
	fila = fopen("existaJoc.txt", "w");
	
	if (fila != NULL) {
		fputc('0', fila);
		fputc('\n', fila);
		fclose(fila);
	}
	
}

//afisez cine castiga
void MesajFinal(int x, int ncols, int nrows) {
	start_color();
	init_pair(BOX2, COLOR_BLACK, COLOR_CYAN);
	WINDOW *win5 = newwin(10, ncols / 3, nrows / 2 - 2, ncols / 3);
	box(win5, 0, 0);
	wbkgd(win5, COLOR_PAIR(BOX2));
	init_pair(BOX, COLOR_BLACK, COLOR_CYAN);
	wrefresh(win5);
	attron(COLOR_PAIR(BOX2));
	char **elem2;
	elem2 = malloc(3 * sizeof(char *));
	elem2[0] = strdup("Ai Castigat");
	elem2[1] = strdup("Calculatorul a castigat");
	elem2[2] = strdup("Remiza");
	mvwaddstr(win5, 4, (ncols / 3 - strlen(elem2[x - 1])) / 2, elem2[x - 1]);
	wrefresh(win5);
	attroff(COLOR_PAIR(BOX2));
	int i;

	for (i = 0; i < 3; ++i) {
		free(elem2[i]);
	}

	free(elem2);
}

//aflu coordonatele in matrice
void permuta(int *x, int *y, int Linie, int Coloana) {
	*x = *x - Coloana;
	*x = *x / 4;
	*y = *y - Linie;
	*y = *y / 2;
}

//aflu coordonatele in matrice
void permutaMic(int *x, int *y, int Linie, int Coloana) {
	*x = *x - Coloana;
	*x = *x / 2;
	*y = *y - Linie;
}

//informatii despre joc
void scrieComenzi(int nrows, int ncols, int Linie, int Coloana) {
	init_pair(BACKGROUND_PAIR,COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(BACKGROUND_PAIR));
	mvaddstr(Linie - 6, Coloana, "R - Randomize map");
	mvaddstr(Linie - 5, Coloana, "D - Go 10 steps forward(destroy)");
	mvaddstr(Linie - 4, Coloana, "Click on right map to select");
	mvaddstr(Linie - 3, Coloana, "Double click on right map for choosing");
	attroff(COLOR_PAIR(BACKGROUND_PAIR));
	refresh();
}

//retin scorul pentru resume game
void retineScor(int score) {
	FILE *fila;
	char numar[10];
	fila = fopen("Scor.txt", "w");

	if (fila != NULL) {
		sprintf(numar, "%d", score);
		fputs(numar, fila);
		fclose(fila);
	}
}

//bag scorul final in top
void retineScorF(int score) {
	FILE *fila;
	char numar[10];
	int valori[6] = { 0 }, i;
	fila = fopen("ScorRec.txt", "r");

	if (fila != NULL) {
		for (i = 0; i < 5; ++i) {
			fgets(numar, 10, fila);
			int j = 0;
			while (j < 10 && numar[j] >= '0' && numar[j] <= '9' ) {
				j ++;
			}
			if (j < 10) {
				numar[j] = '\0';
			}
			valori[i] = atoi(numar);
		}

		int pozitie = 0;

		for (i = 0; i < 5; ++i) {
			if (valori[i] < score) {
				pozitie = i;
				break; 
			}
		}

		for (i = 4; i > pozitie; --i) {
			valori[i] = valori[i - 1];
		}

		valori[pozitie] = score;
		int j;

		for (i = 0; i < 4; ++i) {
			for (j = i + 1; j < 5; ++j) {
				if (valori[i] < valori[j]) {
					int aux = valori[i];
					valori[i] = valori[j];
					valori[j] = aux;
				}
			}
		}	

		fclose(fila);
	}	

	fila = fopen("ScorRec.txt", "w");

	if (fila != NULL) {
		for (i = 0; i < 5; ++i) {
			sprintf(numar, "%d", valori[i]);
			fputs(numar, fila);
			fputc('\n', fila);
		}
		
		fclose(fila);
	}
}

//incep un nou joc si realizez mutarile si fac swap intre randul
//jucatorului si al PC-ului
void startGame(configuratie PC, configuratie Jucator, WINDOW *terminal,
 int score) {
	int i, j, nrows, ncols, d;
	getmaxyx(terminal, nrows, ncols);
	initWindows(nrows, ncols);
	int caracter, raspuns;
	int Bonus = 1;
	int in = 0, jn = 0, directie = 0, numaratoare = 0;

	int Linie = 15, ColoanaJuc = 25, ColoanaPC = ncols - 65;
	if (nrows > 38 && ncols > 132) {
		ColoanaJuc = 25;
		ColoanaPC = ncols - 65;
		Linie = 15;
		showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
		showConfigPC(PC.Mat, Linie, ColoanaPC);
	} else {
		Linie = 10;
		ColoanaJuc = 15;
		ColoanaPC = ncols - 35;
		showConfig(Jucator.Mat, Linie, ColoanaJuc);
		showPC(PC.Mat, Linie, ColoanaPC);
	}
	printScore(nrows, ncols, Linie, ColoanaPC, score);
	scrieComenzi(nrows, ncols, Linie, ColoanaJuc);
	int checker = 1, turn = 1;
	i = j = 0;

	if (nrows > 38 && ncols > 132) {
		coloreazaCelula(i, j, Linie, ColoanaPC);
	} else {
		coloreazaCelulaM(i, j, Linie, ColoanaPC);	
	}

	init_pair(BACKGROUND_PAIR,COLOR_BLACK, COLOR_CYAN);
	attron(COLOR_PAIR(BACKGROUND_PAIR));
	mvaddstr(nrows - 3, (ncols - 13) / 2, "Randul vostru");
	attroff(COLOR_PAIR(BACKGROUND_PAIR));
	refresh();
	cbreak();
	noecho();
	MEVENT event;
	mousemask(ALL_MOUSE_EVENTS, NULL);
	int oldcols, oldrows;
	oldcols = ncols;
	oldrows = nrows;
	int ocp = 0;

	while(checker) {
		getmaxyx(terminal, nrows, ncols);
		if (nrows != oldrows || ncols != oldcols) {
			ColoanaPC = ncols - 65;
			oldrows = nrows;
			oldcols = ncols;
			initWindows(nrows, ncols);
			if (nrows > 38 && ncols > 132) {
				ColoanaJuc = 25;
				ColoanaPC = ncols - 65;
				Linie = 15;
				showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
				showConfigPC(PC.Mat, Linie, ColoanaPC);
			} else {
				ColoanaJuc = 15;
				ColoanaPC = ncols - 35;
				Linie = 10;
				showConfig(Jucator.Mat, Linie, ColoanaJuc);
				showPC(PC.Mat, Linie, ColoanaPC);
			}
			printScore(nrows, ncols, Linie, ColoanaPC, score);
			scrieComenzi(nrows, ncols, Linie, ColoanaJuc);
		}	

		if (turn == 1) {
			stergeLinie(nrows - 3, ncols);
			init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
			attron(COLOR_PAIR(BACKGROUND_PAIR));
			mvaddstr(nrows - 3, (ncols - 13) / 2, "Randul vostru");
			attroff(COLOR_PAIR(BACKGROUND_PAIR));
			refresh();
		} else {
			stergeLinie(nrows - 3, ncols);
			init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
			attron(COLOR_PAIR(BACKGROUND_PAIR));
			mvaddstr(nrows - 3, (ncols - 15) / 2, "Randul PC-ului");
			attroff(COLOR_PAIR(BACKGROUND_PAIR));
			refresh();
			sleep(1);
		}

		if (turn == 1) { // jucator
			int y, x;
			if (nrows > 38 && ncols > 132) {
				coloreazaCelula(i, j, Linie, ColoanaPC);
			} else {
				coloreazaCelulaM(i, j, Linie, ColoanaPC);
			}
			if ((d = getch())) {
				switch(d){
					case KEY_MOUSE:
						if (getmouse(&event) == OK) {
							if (event.bstate & BUTTON1_DOUBLE_CLICKED) {
								y = event.y;
								x = event.x;
								if (y >= Linie && 
									y < (Linie + 
									((nrows > 38 && ncols > 132) ? 20 : 10))
									&& x >= ColoanaPC && x < (ColoanaPC +
									 ((nrows > 38 && ncols > 132) ? 40 : 20)))
								{

									if (nrows > 38 && ncols > 132) {
										permuta(&x, &y, Linie, ColoanaPC);
									} else {
										permutaMic(&x, &y, Linie, ColoanaPC);
									}

									j = x;
									i = y;
									if (PC.Mat[y][x] != -1 
										&& PC.Mat[y][x] != -2) {
										if (PC.Mat[y][x] > 0) {
											PC.Ships[ PC.Mat[y][x] - 1 ] --;
											Bonus ++;
											ocp = PC.Ships[PC.Mat[y][x] - 1];
											if (ocp == 0) {
												acopera(PC, PC.Mat[y][x] - 1);
												Bonus *= 2;
											}

											PC.Mat[y][x] = -2;
										} else {
											PC.Mat[y][x] = -1;
											Bonus = 1;
											turn = 2;
										}

										score += Bonus;

									}
									if (nrows > 38 && ncols > 132) {
											ColoanaJuc = 25;
											ColoanaPC = ncols - 65;
											Linie = 15;
											showConfigBig(Jucator.Mat, Linie,
											 ColoanaJuc);
											showConfigPC(PC.Mat, Linie,
											 ColoanaPC);
										} else {
											ColoanaJuc = 15;
											ColoanaPC = ncols - 35;
											Linie = 10;
											showConfig(Jucator.Mat, Linie,
											 ColoanaJuc);
											showPC(PC.Mat, Linie, ColoanaPC);
										}
									printScore(nrows, ncols, Linie,
									 ColoanaPC, score);

									if (Over(PC.Ships)) {
										retineScorF(score);
										MesajFinal(1, ncols, nrows);
										sleep(2);
										checker = 0;
										nuAreJoc();
									}
								}
							} else if (event.bstate & BUTTON1_CLICKED) {
								y = event.y;
								x = event.x;
								if (y >= Linie && 
									y < Linie + 
									((nrows > 38 && ncols > 132) ? 20 : 10 )
									 && x >= ColoanaPC && 
									 x < ColoanaPC + 
									 ((nrows > 38 && ncols > 132) ? 40 : 20))
								{
									if (nrows > 38 && ncols > 132) {
										permuta(&x, &y, Linie, ColoanaPC);
									} else {
										permutaMic(&x, &y, Linie, ColoanaPC);
									}
									if (PC.Mat[y][x] != -1 
										&& PC.Mat[y][x] != -2) {
										i = y;
										j = x;
									}
								}
							}
						}
						break;
					case KEY_DOWN:
						i++;
						i = (i > 9) ? 0 : i;
						break;
					case KEY_UP:
						i--;
						i = (i < 0) ? 9 : i;
						break;
					case KEY_RIGHT:
						j++;
						j = (j > 9) ? 0 : j;
						break;
					case KEY_LEFT:
						j--;
						j = (j < 0) ? 9 : j;
						break;  
					case 10:
						if (PC.Mat[i][j] != -1 && PC.Mat[i][j] != -2) {
							if (PC.Mat[i][j] > 0) {
								PC.Ships[ PC.Mat[i][j] - 1 ] --;
								Bonus ++;

								if (PC.Ships[PC.Mat[i][j] - 1] == 0) {
									acopera(PC, PC.Mat[i][j] - 1);
									Bonus *= 2;
								}

								PC.Mat[i][j] = -2;

							} else {
								PC.Mat[i][j] = -1;
								turn = 2;
								Bonus = 1;
							}

							score += Bonus;
						}
						if (nrows > 38 && ncols > 132) {
							ColoanaJuc = 25;
							ColoanaPC = ncols - 65;
							Linie = 15;
							showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
							showConfigPC(PC.Mat, Linie,
							 ColoanaPC);
						} else {
							ColoanaJuc = 15;
							ColoanaPC = ncols - 35;
							Linie = 10;
							showConfig(Jucator.Mat, Linie, ColoanaJuc);
							showPC(PC.Mat, Linie, ColoanaPC);
						}
						printScore(nrows, ncols, Linie, ColoanaPC, score);

						if (Over(PC.Ships)) {
							retineScorF(score);
							MesajFinal(1, ncols, nrows);
							sleep(2);
							checker = 0;
							nuAreJoc();
						}  
						break;
					case 'q':
						ExitMenu(ncols, nrows);
						caracter = getch();
						while (caracter != 'Y' && caracter != 'N' 
							&& caracter != 'y' && caracter != 'n') {
							caracter = getch();
						}
						if (caracter == 'Y' || caracter == 'y') {
							retine(PC, Jucator);
							retineScor(score);
							checker = 0;
						}
						initWindows(nrows, ncols);
						if (nrows > 38 && ncols > 132) {
							ColoanaJuc = 25;
							ColoanaPC = ncols - 65;
							Linie = 15;
							showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
							showConfigPC(PC.Mat, Linie, ColoanaPC);
						} else {
							ColoanaJuc = 15;
							ColoanaPC = ncols - 35;
							Linie = 10;
							showConfig(Jucator.Mat, Linie, ColoanaJuc);
							showPC(PC.Mat, Linie, ColoanaPC);
						}
						printScore(nrows, ncols, Linie, ColoanaPC, score);
						scrieComenzi(nrows, ncols, Linie, ColoanaJuc);
						if (turn == 1) {
							if (nrows > 38 && ncols > 132) {
								coloreazaCelula(i, j, Linie, ColoanaPC);
							} else {
								coloreazaCelulaM(i, j, Linie, ColoanaPC);
							}	
						}
						break;
					case 'Q':
						ExitMenu(ncols, nrows);
						caracter = getch();
						while (caracter != 'Y' && caracter != 'N' 
							&& caracter != 'y' && caracter != 'n') {
							caracter = getch();
						}
						if (caracter == 'Y' || caracter == 'y') {
							retine(PC, Jucator);
							retineScor(score);
							checker = 0;
						}
						initWindows(nrows, ncols);
						if (nrows > 38 && ncols > 132) {
							ColoanaJuc = 25;
							ColoanaPC = ncols - 65;
							Linie = 15;
							showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
							showConfigPC(PC.Mat, Linie, ColoanaPC);
						} else {
							ColoanaJuc = 15;
							ColoanaPC = ncols - 35;
							Linie = 10;
							showConfig(Jucator.Mat, Linie, ColoanaJuc);
							showPC(PC.Mat, Linie, ColoanaPC);
						}
						printScore(nrows, ncols, Linie, ColoanaPC, score);
						scrieComenzi(nrows, ncols, Linie, ColoanaJuc);
						if (turn == 1) {
							if (nrows > 38 && ncols > 132) {
								coloreazaCelula(i, j, Linie, ColoanaPC);
							} else {
								coloreazaCelulaM(i, j, Linie, ColoanaPC);
							}	
						}
						break;
					case 'D':
						raspuns = distruge(PC, Jucator, ColoanaPC, Linie,
						 ColoanaJuc, nrows, ncols, &(score));
						if (raspuns > 0) {
							retineScorF(score);
							MesajFinal(raspuns, ncols, nrows);
							sleep(2);
							checker = 0;
							nuAreJoc();
						}
						printScore(nrows, ncols, Linie, ColoanaPC, score);
						break;
					case 'd':
						raspuns = distruge(PC, Jucator, ColoanaPC, Linie,
						 ColoanaJuc, nrows, ncols, &(score));
						if (raspuns > 0) {
							retineScorF(score);
							MesajFinal(raspuns, ncols, nrows);
							sleep(2);
							checker = 0;
							nuAreJoc();
						}
						printScore(nrows, ncols, Linie, ColoanaPC, score);
						break;
					case 'R':
						genereaza(Jucator);
						break;
					case 'r':
						genereaza(Jucator);
						break;
				}
			}	
			if (nrows > 38 && ncols > 132) {
				ColoanaJuc = 25;
				ColoanaPC = ncols - 65;
				Linie = 15;
				showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
				showConfigPC(PC.Mat, Linie, ColoanaPC);
			} else {
				ColoanaJuc = 15;
				ColoanaPC = ncols - 35;
				Linie = 10;
				showConfig(Jucator.Mat, Linie, ColoanaJuc);
				showPC(PC.Mat, Linie, ColoanaPC);
			}
			printScore(nrows, ncols, Linie, ColoanaPC, score);
			scrieComenzi(nrows, ncols, Linie, ColoanaJuc);
			if (turn == 1) {
				if (nrows > 38 && ncols > 132) {
					coloreazaCelula(i, j, Linie, ColoanaPC);
				} else {
					coloreazaCelulaM(i, j, Linie, ColoanaPC);
				}
			}
			
		} else { // calculator
			PCTurn(Jucator, Linie, ColoanaJuc, nrows, ncols, &directie,
				&numaratoare, &in, &jn);
			if (nrows > 38 && ncols > 132) {
				ColoanaJuc = 25;
				ColoanaPC = ncols - 65;
				Linie = 15;
				showConfigBig(Jucator.Mat, Linie, ColoanaJuc);
				showConfigPC(PC.Mat, Linie, ColoanaPC);
			} else {
				ColoanaJuc = 15;
				ColoanaPC = ncols - 35;
				Linie = 10;
				showConfig(Jucator.Mat, Linie, ColoanaJuc);
				showPC(PC.Mat, Linie, ColoanaPC);
			}
			printScore(nrows, ncols, Linie, ColoanaPC, score);
			scrieComenzi(nrows, ncols, Linie, ColoanaJuc);
			turn = 1;

			if (Over(Jucator.Ships)) {
				retineScorF(score);
				MesajFinal(2, ncols, nrows);
				sleep(2);
				checker = 0;
				nuAreJoc();
			} else {
				init_pair(BACKGROUND_PAIR,COLOR_BLACK, COLOR_CYAN);
				attron(COLOR_PAIR(BACKGROUND_PAIR));
				mvaddstr(nrows - 3, (ncols - 13) / 2, "Randul vostru");
				attroff(COLOR_PAIR(BACKGROUND_PAIR));
			}

		}

		flushinp();
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

//text pentru new game
void NGText(char **elements, int linieText, int coloanaText,
 int poz, int number) {
	// int i, linieText, coloanaText;
	// linieText = nrows / 3;
	// coloanaText = ncols / 2 - 10;
	char Pointer = (char) 62; 

	if (poz < number - 2) {
		attron(A_STANDOUT);
		move(linieText, coloanaText - 2);
		addch(Pointer);
		move(linieText, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText, coloanaText, elements[poz]);
		move(linieText, coloanaText + strlen(elements[poz]));
		addch(' ');
		attroff(A_STANDOUT);
		refresh();
		start_color();
		init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
		attron(COLOR_PAIR(BACKGROUND_PAIR));
		move(linieText + 3, coloanaText - 2);
		move(linieText + 3, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText + 3, coloanaText, elements[number - 2]);
		move(linieText + 3, coloanaText + strlen(elements[number - 2]));
		addch(' ');
		move(linieText + 6, coloanaText - 2);
		move(linieText + 6, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText + 6, coloanaText, elements[number - 1]);
		move(linieText + 6, coloanaText + strlen(elements[number - 1]));
		addch(' ');
		attroff(COLOR_PAIR(BACKGROUND_PAIR));
		refresh();
	} else if (poz == number - 2){
		start_color();
		init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
		attron(COLOR_PAIR(BACKGROUND_PAIR));
		move(linieText, coloanaText - 2);
		move(linieText, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText, coloanaText, elements[0]);
		move(linieText, coloanaText + strlen(elements[0]));
		addch(' ');
		attroff(COLOR_PAIR(BACKGROUND_PAIR));
		refresh();
		attron(A_STANDOUT);
		move(linieText + 3, coloanaText - 2);
		addch(Pointer);
		move(linieText + 3, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText + 3, coloanaText, elements[number - 2]);
		move(linieText + 3, coloanaText + strlen(elements[number - 2]));
		addch(' ');
		attroff(A_STANDOUT);
		refresh();
		start_color();
		init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
		attron(COLOR_PAIR(BACKGROUND_PAIR));
		move(linieText + 6, coloanaText - 2);
		move(linieText + 6, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText + 6, coloanaText, elements[number - 1]);
		move(linieText + 6, coloanaText + strlen(elements[number - 1]));
		addch(' ');
		attroff(COLOR_PAIR(BACKGROUND_PAIR));
		refresh();
	} else {
		start_color();
		init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
		attron(COLOR_PAIR(BACKGROUND_PAIR));
		move(linieText, coloanaText - 2);
		move(linieText, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText, coloanaText, elements[0]);
		move(linieText, coloanaText + strlen(elements[0]));
		addch(' ');
		move(linieText + 3, coloanaText - 2);
		move(linieText + 3, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText + 3, coloanaText, elements[number - 2]);
		move(linieText + 3, coloanaText + strlen(elements[number - 2]));
		addch(' ');
		attroff(COLOR_PAIR(BACKGROUND_PAIR));
		refresh();
		attron(A_STANDOUT);
		move(linieText + 6, coloanaText - 2);
		addch(Pointer);
		move(linieText + 6, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText + 6, coloanaText, elements[number - 1]);
		move(linieText + 6, coloanaText + strlen(elements[number - 1]));
		addch(' ');
		attroff(A_STANDOUT);
		refresh();
	}

	move(0, 0);
}

//text pentru OLDconfig
void NGOLD(char **elements, int linieText, int coloanaText,
 int poz, int number) {
	// int i, linieText, coloanaText;
	// linieText = nrows / 3;
	// coloanaText = ncols / 2 - 10;
	char Pointer = (char) 62; 

	if (poz < number - 1) {
		attron(A_STANDOUT);
		move(linieText, coloanaText - 2);
		addch(Pointer);
		move(linieText, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText, coloanaText, elements[poz]);
		move(linieText, coloanaText + strlen(elements[poz]));
		addch(' ');
		attroff(A_STANDOUT);
		refresh();
		start_color();
		init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
		attron(COLOR_PAIR(BACKGROUND_PAIR));
		move(linieText + 3, coloanaText - 2);
		move(linieText + 3, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText + 3, coloanaText, elements[number - 1]);
		move(linieText + 3, coloanaText + strlen(elements[number - 1]));
		addch(' ');
		attroff(COLOR_PAIR(BACKGROUND_PAIR));
		refresh();
	} else if (poz == number - 1){
		start_color();
		init_pair(BACKGROUND_PAIR, COLOR_BLACK, COLOR_CYAN);
		attron(COLOR_PAIR(BACKGROUND_PAIR));
		move(linieText, coloanaText - 2);
		move(linieText, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText, coloanaText, elements[0]);
		move(linieText, coloanaText + strlen(elements[0]));
		addch(' ');
		attroff(COLOR_PAIR(BACKGROUND_PAIR));
		refresh();
		attron(A_STANDOUT);
		move(linieText + 3, coloanaText - 2);
		addch(Pointer);
		move(linieText + 3, coloanaText - 1);
		addch(' ');
		mvaddstr(linieText + 3, coloanaText, elements[number - 1]);
		move(linieText + 3, coloanaText + strlen(elements[number - 1]));
		addch(' ');
		attroff(A_STANDOUT);
		refresh();
	} 

	move(0, 0);
}

//instructiuni de folosire a meniului
void scrieComenziM(int nrows, int ncols, int Linie, int Coloana) {
	start_color();
	init_pair(BOX, COLOR_BLACK, COLOR_CYAN);
	WINDOW *win = newwin(8, ncols / 3, Linie - 9, Coloana - 1);
	wbkgd(win, COLOR_PAIR(BOX));
	wrefresh(win);
	scrollok(win, TRUE);
	attron(COLOR_PAIR(BOX));
	char s[70];
	mvwprintw(win, 0, 0, "-Arrow UP - move up in menu - navigare prin meniu");
	strcpy(s, "-Arrow DOWN - move down in menu - navigare prin meniu");
	mvwprintw(win, 2, 0, s);
	strcpy(s, "-Arrow LEFT or RIGHT - Change menu - Meniul de jos sau sus");
	mvwprintw(win, 4, 0, s);
	mvwprintw(win, 6, 0, "-Q or q - Quit - Revii la meniul principal");
	wrefresh(win);
	attroff(COLOR_PAIR(BOX));
}

// generez meniul cu configuratii vechi
void OldConfig(configuratie PC, configuratie *Configuratii,
 int marime, WINDOW *terminal, int *out) {
	int i, nrows, ncols;
	char **meniulVechi;
	configuratie Salvare;

	meniulVechi = malloc((marime + 1) * sizeof(char *));

	getmaxyx(terminal, nrows, ncols);
	initWindows(nrows, ncols);
	int linieText, coloanaText;
	if (nrows < 30) {
		linieText = nrows / 3 + 5;
		coloanaText = ncols / 2 - 10;
	} else {
		linieText = nrows / 3;
		coloanaText = ncols / 2 - 10;
	}

	for (i = 0; i < marime; ++i) {
		char buffer[30];
		sprintf(buffer, "Configuration number %d", i + 1);
		buffer[strlen(buffer)] = '\0';
		meniulVechi[i] = strdup(buffer);
	}

	meniulVechi[marime] = strdup("Go back to main menu\0");

	int checker = 1, d, j;
    i = j = 0;
    NGOLD(meniulVechi, linieText, coloanaText, 0, marime + 1);
    scrieComenziM(nrows, ncols, linieText, coloanaText);
    if (marime > 0 && ncols > 120) {
  		showConfigBig(Configuratii[i].Mat, 3, 3);
	} else if (marime > 0 && ncols > 78) {
    	showConfig(Configuratii[0].Mat, 3, 3);
    }

    cbreak();
	noecho();

    while (checker)
	{
		getmaxyx(terminal, nrows, ncols);
		if (nrows < 30) {
			linieText = nrows / 3 + 5;
			coloanaText = ncols / 2 - 10;
		} else {
			linieText = nrows / 3;
			coloanaText = ncols / 2 - 10;
		}
		initWindows(nrows, ncols);
	  	NGOLD(meniulVechi, linieText, coloanaText, i, marime + 1);
	  	scrieComenziM(nrows, ncols, linieText, coloanaText);
	  	if (i < marime && ncols > 120) {
	  		showConfigBig(Configuratii[i].Mat, 3, 3);
	  	} else if (i < marime && ncols > 78) {
	  		showConfig(Configuratii[i].Mat, 3, 3);
	  	}
		if ((d = getch())) {
			switch( d ){
				case KEY_DOWN:
							if (j == 0) {
								i++;
								i = ( i > marime - 1) ? 0 : i;
							} else {
								i = marime;
							}
							break;
				case KEY_UP:
							if (j == 0) {
								i--;
								i = ( i < 0) ? (marime - 1) : i;
							} else {
								i = marime;
							}
							break;
				case KEY_RIGHT:
							j++;
							if (j == 2) {
								j = 0;
								i = 0;
							} else if (j == 1) {
								i = marime;
							}
							break; 
				case KEY_LEFT:
							j--;
							if (j == -1) {
								j = 1;
								i = marime;
							} else if (j == 0) {
								i = 0;
							}
							break;
				case 10:
							if (i == marime) {
								checker = 0;
							} else if (i < marime) {
								alocare(&Salvare);
								Copiere(Salvare, Configuratii[i]);
								startGame(PC, Salvare, terminal, 0);
								*out = 0;
								dealoca(Salvare);
								for (i = 0; i < marime + 1; ++ i) {
									free(meniulVechi[i]);
								}

								free(meniulVechi);
								return;
							}
							break;
				case 'q':
							checker = 0;
							break;
				case 'Q':
							checker = 0;
			}
		}	
		
	  	flushinp();
	}

	for (i = 0; i < marime + 1; ++ i) {
		free(meniulVechi[i]);
	}

	free(meniulVechi);

}

//generez meniul cu configuratii
void NewGame(configuratie PC, configuratie *Configuratii, int marime,
 configuratie *Nou, int dimensiune, WINDOW *terminal) {
    genereaza(PC);
    int i, nrows, ncols, w;
    configuratie Salvare;

	getmaxyx(terminal, nrows, ncols);
	initWindows(nrows, ncols);
	int linieText, coloanaText;
	if (nrows < 30) {
		linieText = nrows / 3 + 5;
		coloanaText = ncols / 2 - 10;
	} else {
		linieText = nrows / 3;
		coloanaText = ncols / 2 - 10;
	}

	char **meniulNou;
	meniulNou = malloc((dimensiune + 2) * sizeof(char *));

	for (i = 0; i < dimensiune; ++i) {
		char buffer[30];
		sprintf(buffer, "Configuration number %d", i + 1);
		buffer[strlen(buffer)] = '\0';
		meniulNou[i] = strdup(buffer);
	}

	meniulNou[dimensiune] = strdup("Choose an old configuration\0");
    meniulNou[dimensiune + 1] = strdup("Go back to main menu\0");

    int checker = 1, d, out = 1, j;
    i = j = 0;
    NGText(meniulNou, linieText, coloanaText, 0, dimensiune + 2);
    scrieComenziM(nrows, ncols, linieText, coloanaText);
    if (dimensiune > 0 && ncols > 120) {
 		showConfigBig(Nou[i].Mat, 3, 3);
	 } else if (dimensiune > 0 && ncols > 78) {
	  	showConfig(Nou[0].Mat, 3, 3);
	}

	cbreak();
	noecho();

    while (checker && out) {
		getmaxyx(terminal, nrows, ncols);
		if (nrows < 30) {
			linieText = nrows / 3 + 5;
			coloanaText = ncols / 2 - 10;
		} else {
			linieText = nrows / 3;
			coloanaText = ncols / 2 - 10;
		}
		initWindows(nrows, ncols);
	  	NGText(meniulNou, linieText, coloanaText, i, dimensiune + 2);
	  	scrieComenziM(nrows, ncols, linieText, coloanaText);
	  	if (i < dimensiune && ncols > 120) {
	  		showConfigBig(Nou[i].Mat, 3, 3);
	  	} else if (i < dimensiune && ncols > 78 ) {
	  		showConfig(Nou[i].Mat, 3, 3);
	  	}
		if ((d = getch())) {
			switch( d ) {
				case KEY_DOWN:
					if (j == 0) {
						i++;
						i = ( i > dimensiune - 1) ? 0 : i;
					} else {
						i++;
						i = ( i > dimensiune + 1) ? dimensiune : i;
					}
					break;
				case KEY_UP:
					if (j == 0) {
						i--;
						i = ( i < 0) ? (dimensiune - 1) : i;
					} else {
						i--;
						i = ( i < dimensiune) ? (dimensiune + 1) : i;
					}
					break;
				case KEY_RIGHT:
					j++;
					if (j == 2) {
						j = 0;
						i = 0;
					} else if (j == 1) {
						i = dimensiune;
					}
					break; 
				case KEY_LEFT:
					j--;
					if (j == -1) {
						j = 1;
						i = dimensiune;
					} else if (j == 0) {
						i = 0;
					}
					break;
				case 10:
					if (i == dimensiune + 1) {
						checker = 0;
					} else if (i == dimensiune) {
						OldConfig(PC, Configuratii, marime, terminal, &out);
					} else if (i < dimensiune) {
						alocare(&Salvare);
						Copiere(Salvare, Nou[i]);
						startGame(PC, Salvare, terminal, 0);
						dealoca(Salvare);
						for (w = 0; w < dimensiune + 2; ++ w) {
							free(meniulNou[w]);
						}

						free(meniulNou);
						return;
					}
					break;
				case 'q':
					checker = 0;
					break;
				case 'Q':
					checker = 0;
					break;
			}
		}	
	 
		flushinp(); 	
	}

	for (i = 0; i < dimensiune + 2; ++ i) {
		free(meniulNou[i]);
	}

	free(meniulNou);
}

//datele pentru Resume Game
void dateJoc(configuratie Jucator, configuratie PC, int *scor) {
	FILE *fila;
	fila = fopen("existaJoc.txt" , "r");
	char sr[40];
	char *p;
	int j, k;
	if (fila != NULL) {
		fgets(sr, 40, fila);
		//PC
		for (j = 0; j < 10; ++j) {
			fgets(sr, 40, fila);
			p = strtok(sr, " ");
			k = 0;

			while (p) {
				PC.Mat[j][k ++] = atoi(p);
				p = strtok(NULL, " ");
			}
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			PC.StartI[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			PC.StartJ[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			PC.Directie[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			PC.Ships[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			PC.Vap[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		//Jucator
		for (j = 0; j < 10; ++j) {
			fgets(sr, 40, fila);
			p = strtok(sr, " ");
			k = 0;

			while (p) {
				Jucator.Mat[j][k ++] = atoi(p);
				p = strtok(NULL, " ");
			}
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			Jucator.StartI[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			Jucator.StartJ[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			Jucator.Directie[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			Jucator.Ships[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		fgets(sr, 40, fila);
		p = strtok(sr, " ");
		k = 0;

		while (p) {
			Jucator.Vap[k ++] = atoi(p);
			p = strtok(NULL, " ");
		}

		fclose(fila);
	}

	fila = fopen("Scor.txt" , "r");

	if (fila != NULL) {
		char s[10];
		fgets(s, 10, fila);
		*scor = atoi(s);
		fclose(fila);
	} else {
		*scor = 0;
	}

}

// verific daca exista deja un joc
void eJoc(int *hasGame) {
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
		free(sr);
	}
}

//citesc configuratiile vechi si noi ale jucatorului din fisiere
void readData(configuratie **Configuratii, int *marime, int argc,
 char *argv[], configuratie **Nou, int *dimensiune, int *eroare) {
	FILE *fila;
	fila = fopen("configuratii.txt", "r");

	if (fila != NULL) {
		char *sr;
		sr = malloc(40 * sizeof(char));
		fgets(sr, 40, fila);
		*marime = atoi(sr);
		int i, j, k;
		*Configuratii = malloc(*marime * sizeof(configuratie));

		for (i = 0; i < *marime; ++i) {
			alocare(&(*Configuratii)[i]);
		}

		for (i = 0; i < *marime; ++i) {
			char *p;

			for (j = 0; j < 10; ++j) {
				fgets(sr, 40, fila);
				p = strtok(sr, " \n");
				k = 0;

				while (p) {
					(*Configuratii)[i].Mat[j][k ++] = atoi(p);
					p = strtok(NULL, " \n");
				}
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

			fgets(sr, 40, fila);
			p = strtok(sr, " ");
			k = 0;

			while (p) {
				(*Configuratii)[i].Directie[k ++] = atoi(p);
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
				char separator[] = "|";
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

						while (pozitie < 9 && 
							(*Nou)[i - 1].Mat[j][pozitie + 1] == -1) {
							counter ++;
							pozitie ++;
							directie = 1;
						}

						pozitie = j;

						while(pozitie < 9 && 
							(*Nou)[i - 1].Mat[pozitie + 1][k] == -1) {
							counter ++;
							pozitie ++;
							directie = 2;
						}

						if (directie == 1) {
							pozitie = k;

							if (counter == 4) {
								while (pozitie < 10 && 
									(*Nou)[i - 1].Mat[j][pozitie] == -1) {
									(*Nou)[i - 1].Mat[j][pozitie] = 1;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[0] = 1;
								(*Nou)[i - 1].StartI[0] = j;							
								(*Nou)[i - 1].StartJ[0] = k;
							} else if (counter == 3) {

								while (pozitie < 10 && 
									(*Nou)[i - 1].Mat[j][pozitie] == -1) {
									(*Nou)[i - 1].Mat[j][pozitie] = 2 + trei;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[2 + trei - 1] = 1;
								(*Nou)[i - 1].StartI[2 + trei - 1] = j;							
								(*Nou)[i - 1].StartJ[2 + trei - 1] = k;
								trei ++;

							} else if (counter == 2) {

								while (pozitie < 10 && 
									(*Nou)[i - 1].Mat[j][pozitie] == -1) {
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
								while (pozitie < 10 && 
									(*Nou)[i - 1].Mat[pozitie][k] == -1) {
									(*Nou)[i - 1].Mat[pozitie][k] = 1;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[0] = 2;
								(*Nou)[i - 1].StartI[0] = j;							
								(*Nou)[i - 1].StartJ[0] = k;
							} else if (counter == 3) {

								while (pozitie < 10 && 
									(*Nou)[i - 1].Mat[pozitie][k] == -1) {
									(*Nou)[i - 1].Mat[pozitie][k] = 2 + trei;
									pozitie ++;
								}

								(*Nou)[i - 1].Directie[2 + trei - 1] = 2;
								(*Nou)[i - 1].StartI[2 + trei - 1] = j;							
								(*Nou)[i - 1].StartJ[2 + trei - 1] = k;
								trei ++;

							} else if (counter == 2) {

								while (pozitie < 10 && 
									(*Nou)[i - 1].Mat[pozitie][k] == -1) {
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
			fclose(fila);
		} else {
			*eroare = 1;
			char *s;
			s = strdup(argv[i]);
			fprintf(stderr, "[Eroare]: Fisierul %s nu poate fi deschis\n", s);
			free(s);
			return;
		}
	}
}

//salvez configuratiile
void salveazaConfiguratii(configuratie *Nou, int dimensiune) {
	int i, j, k;
	FILE *fila;
	fila = fopen("configuratii.txt", "w");

	if (fila != NULL) {
		char ssir[10];
		sprintf(ssir, "%d", dimensiune);
		fputs(ssir, fila);
		fputc('\n', fila);

		for (k = 0; k < dimensiune; ++k) {
			char *string;
			char number[3];
			string = malloc(30 * sizeof(char));

			for (i = 0; i < 10; ++ i) {
				string[0] = '\0';

				for (j = 0; j < 10; ++ j) {
					sprintf(number, "%d ", Nou[k].Mat[i][j]);
					strcat(string, number);
				}

				fputs(string, fila);
				fputc('\n', fila);
			}

			string[0] = '\0';

			for (i = 0; i < 10; ++ i) {
				sprintf(number, "%d ", Nou[k].StartI[i]);
				strcat(string, number);
			}
			fputs(string, fila);
			fputc('\n', fila);
			string[0] = '\0';

			for (i = 0; i < 10; ++ i) {
				sprintf(number, "%d ", Nou[k].StartJ[i]);
				strcat(string, number);
			}
			fputs(string, fila);
			fputc('\n', fila);
			string[0] = '\0';

			for (i = 0; i < 10; ++ i) {
				sprintf(number, "%d ", Nou[k].Directie[i]);
				strcat(string, number);
			}
			fputs(string, fila);
			fputc('\n', fila);

			free(string);
		}
		fclose(fila);
	}	
}

//afisez informatii despre Joc
void viewInfo(WINDOW *terminal, int nrows, int ncols) {
	int initial = 8000;
	char *elem;
	elem = malloc(initial * sizeof(char));
	strcpy(elem, "-Apasa Q sau q pentru a iesi.\n");
	strcat(elem, "-Prin meniul puteti naviga doar cu sagetile.\n");
	strcat(elem, "-In meniul New Game si Choose an old config ");
	strcat(elem, "navigati treceti la ultimele 2 variante ");
	strcat(elem, "apasand sagetiile stanga sau dreapta.\n");
	strcat(elem, "-Jocul e cat de cat Responsive, dar recomandat ");
	strcat(elem, "e sa nu dati resize cand e randul calculatorului ");
	strcat(elem, "sau dupa ce ati apasat varianta de mers 10 pasi ");
	strcat(elem, "inainte(D), deoarece nu o sa mearga resize.\n");
	strcat(elem, "-Cu un click selectati casuta si cu dublu click ");
	strcat(elem, "atacati respectiva casuta.\n");
	strcat(elem, "-Pentru o experienta de joc buna se recomanda o ");
	strcat(elem, "dimensiune de peste 38x130 a terminalului.\n");
	strcat(elem, "-Distractie placuta.\n");
	start_color();
	init_pair(BOX, COLOR_BLACK, COLOR_CYAN);
	WINDOW *win = newwin(nrows - 2, ncols / 3, 1, ncols / 3);
	wbkgd(win, COLOR_PAIR(BOX));
	wrefresh(win);
	scrollok(win, TRUE);
	attron(COLOR_PAIR(BOX));
	mvwprintw(win, 0, 0, "%s", elem);
	wrefresh(win);
	attroff(COLOR_PAIR(BOX));

	int d;
	while (1) {
		getmaxyx(terminal, nrows, ncols);
		initWindows(nrows, ncols);
		win = newwin(nrows - 2, ncols / 3, 1, ncols / 3);
		scrollok(win, TRUE);
		wbkgd(win, COLOR_PAIR(BOX));
		refresh();
		scrollok(win,TRUE);
		attron(COLOR_PAIR(BOX));
		mvwprintw(win, 0, 0, "%s", elem);
		wrefresh(win);
		attroff(COLOR_PAIR(BOX));
		d = getch();
		if (d == 'Q' || d == 'q') {
			free(elem);
			return;
		}

	}

	free(elem);

}

//afisez scoreboard
void afiseazaScoreBoard(int nrows, int ncols, WINDOW *terminal) {
	FILE *fila;
	fila = fopen("ScorRec.txt", "r");
	char **numar, ceva[30];
	numar = malloc(7 * sizeof(char *));
	int i, d, linieText, coloanaText;

	for (i = 0; i < 7; ++i) {
		numar[i] = malloc(30 * sizeof(char));
	}

	strcpy(numar[0], "Iesiti apasand Q sau q\0");
	strcpy(numar[1], "Scoreboard\0");
	linieText = nrows / 5 - 2;
	coloanaText = ncols / 2 - 10;

	if (fila != NULL) {
		for (i = 0; i < 5; ++i) {
			fgets(ceva, 30, fila);
			int j = 0;
			while (ceva[j] >= '0' && ceva[j] <= '9' && j < 30) {
				j ++;
			}
			if (j < 30) {
				ceva[j] = '\0';
			}
			strcpy(numar[i + 2], ceva);
		}

		fclose(fila);
	} else {
		for (i = 0; i < 5; ++i) {
			strcpy(numar[i + 2], "0");
		}		
	}

	initWindows(nrows, ncols);
	initText(numar, linieText, coloanaText, -1, 7);
	int checker = 1;

	while (checker) {
	getmaxyx(terminal, nrows, ncols);
	linieText = nrows / 5 - 2;
	coloanaText = ncols / 2 - 10;
	initWindows(nrows, ncols);
	initText(numar, linieText, coloanaText, -1, 7);
		if ((d = getch())) {
			if (d == 'Q' || d == 'q') {
				checker = 0;
			}
		}

	}

	for (i = 0; i < 7; ++i) {
		free(numar[i]);
	}

	free(numar);
}

//main function
int main(int argc, char *argv[])
{
	if (argc <= 1) {
		fprintf(stderr, "[Eroare]: Nu s-au dat argumente de comanda.\n");
		return 1;
	}

	int eroare = 0;
	time_t t;
	srand((unsigned) time(&t));
	int nrows, ncols, d;
	WINDOW *terminal;
	nrows = ncols = 0;
	textinitial meniu[2];
	meniu[0].valoare = 4;
	meniu[1].valoare = 5;
	meniu[0].elemente = malloc(4 * sizeof(char *));
	meniu[0].elemente[0] = strdup("New Game\0");
	meniu[0].elemente[1] = strdup("Info\0");
	meniu[0].elemente[2] = strdup("Scoreboard\0");
	meniu[0].elemente[3] = strdup("Quit(Q)\0");
	meniu[1].elemente = malloc(5 * sizeof(char *));
	meniu[1].elemente[0] = strdup("New Game\0");
	meniu[1].elemente[1] = strdup("Resume Game\0");
	meniu[1].elemente[2] = strdup("Info\0");
	meniu[1].elemente[3] = strdup("Scoreboard\0");
	meniu[1].elemente[4] = strdup("Quit(Q)\0");
	configuratie *Configuratii, *Nou, PC, Player;
	int hasGame = 0, marime = 0, dimensiune = 0;
	eJoc(&hasGame);
	readData(&Configuratii, &marime, argc, argv, &Nou, &dimensiune, &eroare);
	if (eroare == 1) {
		return 1;
	}

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
	alocare(&Player);
	i = 0;
	initWindows(nrows, ncols);
	initText(meniu[hasGame].elemente, linieText,
	 coloanaText, 0, meniu[hasGame].valoare);
	int scor = 0;

	while (checker)
	{	
		getmaxyx(terminal, nrows, ncols);
		linieText = nrows / 3;
		coloanaText = ncols / 2 - 10;
		initWindows(nrows, ncols);
		initText(meniu[hasGame].elemente, linieText,
		 coloanaText, i, meniu[hasGame].valoare);
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
							initializare(PC);
							NewGame(PC, Configuratii, marime, Nou,
							 dimensiune, terminal);
							initWindows(nrows, ncols);
							eJoc(&hasGame);
						} else if (i == 1)
						{
							dateJoc(Player, PC, &scor);
							startGame(PC, Player, terminal, scor);
							eJoc(&hasGame);
						} else if (i == 2) {
							viewInfo(terminal, nrows, ncols);
						} else if (i == 3) {
							afiseazaScoreBoard(nrows, ncols, terminal);
						} else if (i == 4) {
							salveazaConfiguratii(Nou, dimensiune);
							checker = 0;
						}
					} else {
						if (i == 0) {
							initializare(PC);
							NewGame(PC, Configuratii, marime, Nou,
							 dimensiune, terminal);
							initWindows(nrows, ncols);
							eJoc(&hasGame);
						} else if (i == 1) {
							viewInfo(terminal, nrows, ncols);
						} else if (i == 2) {
							afiseazaScoreBoard(nrows, ncols, terminal);
						} else if (i == 3) {
							salveazaConfiguratii(Nou, dimensiune);
							checker = 0;
						}
					}
					break;
			}
		} else if( d == 'Q' || d == 'q') {
			salveazaConfiguratii(Nou, dimensiune);
			break;
		}

		
		flushinp();
	}

	endwin();

	for (i = 0; i < marime; ++ i) {
		dealoca(Configuratii[i]);
	}

	for (i = 0; i < dimensiune; ++ i) {
		dealoca(Nou[i]);
	}

	dealoca(PC);
	dealoca(Player);
	free(Configuratii);
	free(Nou);

	for ( i = 0; i < 5; ++ i) {
		free(meniu[1].elemente[i]);
	}

	free(meniu[1].elemente);

	for ( i = 0; i < 4; ++ i) {
		free(meniu[0].elemente[i]);
	}

	free(meniu[0].elemente);

	return 0;
}