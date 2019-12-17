// //verific daca unelement este valid in matrice
// //adica daca are vecini vizi sau daca sunt de acelasi tip
// int checks(char **Matrix, char value, int row, int column)
// {
// 	int deplY[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
// 	int deplX[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
// 	int i;

// 	if (Matrix[row][column] != '0') {
// 		return 0;
// 	}

// 	for (i = 0; i < 8; ++i) {
// 		int nextRow = row + deplX[i];
// 		int nextColumn = column + deplY[i];

// 		if (nextRow >= 0 && nextRow < 10 && nextColumn >= 0 && nextColumn < 10) {
// 			if (Matrix[nextRow][nextColumn] != '0' && Matrix[nextRow][nextColumn] != value) {
// 				return 0;
// 			}
// 		}

// 	}

// 	return 1;
// }

// //caut o locatie unde sa pun urmatoarea nava in fuctie de cat de mare e
// // si de valoarea sa
// void gaseste(char **Matrix, char value, int element)
// {
// 	int linie, coloana;

// 	while (TRUE)
// 	{
// 		linie = randomize();
// 		coloana = randomize();

// 		if (Matrix[linie][coloana] == '0') { //stanga
// 			if (coloana - element >= 0) {
// 				int linieL = linie, coloanaC = coloana;
// 				int numarare = element;
				
// 				while (checks(Matrix, value, linieL, coloanaC) && numarare) {
// 					Matrix[linieL][coloanaC] = value;
// 					numarare --;
// 					coloanaC --;
// 				}

// 				if (numarare == 0) {
// 					return;
// 				} else {
// 					numarare = element - numarare ;
// 					linieL = linie;
// 					coloanaC = coloana;

// 					while( numarare ) {
// 						Matrix[linieL][coloanaC] = '0';
// 						numarare --;
// 						coloanaC --;
// 					}

// 				}

// 			}
// 			if (linie - element >= 0) { //sus

// 				int linieL = linie, coloanaC = coloana;
// 				int numarare = element;
				
// 				while (checks(Matrix, value, linieL, coloanaC) && numarare) {
// 					Matrix[linieL][coloanaC] = value;
// 					numarare --;
// 					linieL --;
// 				}

// 				if (numarare == 0) {
// 					return;
// 				} else {
// 					numarare = element - numarare ;
// 					linieL = linie;
// 					coloanaC = coloana;

// 					while( numarare ) {
// 						Matrix[linieL][coloanaC] = '0';
// 						numarare --;
// 						linieL --;
// 					}

// 				}

// 			}

// 			if (coloana + element < 10) { //dreapta

// 				int linieL = linie, coloanaC = coloana;
// 				int numarare = element;
				
// 				while (checks(Matrix, value, linieL, coloanaC) && numarare) {
// 					Matrix[linieL][coloanaC] = value;
// 					numarare --;
// 					coloanaC ++;
// 				}

// 				if (numarare == 0) {
// 					return;
// 				} else {
// 					numarare = element - numarare ;
// 					linieL = linie;
// 					coloanaC = coloana;

// 					while( numarare ) {
// 						Matrix[linieL][coloanaC] = '0';
// 						numarare --;
// 						coloanaC ++;
// 					}

// 				}

// 			}

// 			if (linie + element < 10 ) { // jos

// 				int linieL = linie, coloanaC = coloana;
// 				int numarare = element;
				
// 				while (checks(Matrix, value, linieL, coloanaC) && numarare) {
// 					Matrix[linieL][coloanaC] = value;
// 					numarare --;
// 					linieL ++;
// 				}

// 				if (numarare == 0) {
// 					return;
// 				} else {
// 					numarare = element - numarare ;
// 					linieL = linie;
// 					coloanaC = coloana;

// 					while( numarare ) {
// 						Matrix[linieL][coloanaC] = '0';
// 						numarare --;
// 						linieL ++;
// 					}

// 				}

// 			}

// 		}

// 	}

// }
