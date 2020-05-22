Romanian:
Dumitrescu Andrei 313CC

Idei principale:
-Am implementat jocul in fereastra terminalului, alte WINDOW-uri fiind
folosite pentru informatii mai scurte.
-Jocul are ca fucntii de baza grafice initWindows si initText, 
care coloreaza imaginea cu CYAN si printeaza scrisul.
-Interfata grafica este una simpla, usor de folosind, prezentant mai multe
in cele ce urmeaza despre fiecare interfata.
-Din majoritatea interfetelor se iese apasant Q sau q, iar unele au si 
optiunea d eselectat "QUIT".
-In fisierul ExampleMatrix.txt este un model de configuratie al jucatorului,
unde 'X' inseamna  o parte din nava, ' ' reprezinta spatiu liber, iar
'|' inseamna caracterul delimitator dintre celule.

Model configuratie jucator in fisier in ExampleMatrix.txt:
	| | | | | |X| | | | |
	|X|X|X|X| | | | | | |
	| | | | | | | |X|X|X|
	| |X| | | | | | | | |
	| | | | |X| | | | |X|
	| | | | |X| | | | | |
	|X|X| | |X| | |X|X| |
	| | | | | | | | | | |
	| | |X| | | | |X| | |
	| | |X| | | | | | | |

Generarea matricei calculatorului:
	Algoritmul de generare este unul simplu si se bazeaza pe faptul ca
	dupa plasarea unei nave, conturul ei sa fie marcat cu -1, iar apoi
	cand se plaseaza alta nava se verifica daca aria dreptunghiului
	nu cuprinde alte numere decat 0 si -1. De exemplu:
	-1 -1 -1 
	-1  3 -1 -1 -1 -1 
	-1  3 -1  2  2 -1
	-1  3 -1 -1 -1 -1 
	-1 -1 -1
	este valid pentru o nada de 3 si una de 2 cu 1 spatiu intre ele.

In cele ce urmeaza o sa explic mai mult cerintele problemei, iar anumite 
detalii vor si explicate mai bine in bonusuri.
La final sunt informatii despre fisiere.

Cerinte si meniuri:
 Cerinta 1:
 	Meniu simplu, cu 4-5 optiuni (New Game, Resume Game, daca are, Info, 
 	Scoreboard, Quit(Q)). Optiunea Resume Game apare doar daca exista
 	un joc care nu s-a terminat.
 Meniul New Game:
 	Odata ce s-a apasa New Game din meniul principal se genereaza matricea
 	calculatorului. Acest Meniul este alcatuit din 2 bucati. Partea de sus
 	cuprinde selectia configuratiei de joc care sunt fisiere citite din 
 	linia de comanda. acestea se selecteaza folosind sagetile de sus si jos.
 	Pentru a trece in partea de jos se folsoesc sagetiile stanga si dreapta,
 	iar navigarea in acesta se face tot cu sagetiile sus si jos. Odata ce 
 	s-a ales o configuratie se trece in interfata jocului.
 	Mai multe o sa fie explicate in bonusuri.
 Meniul Resume Game:
 	Apare doar daca exista un joc neterminat. 
 Cerinta 2:
 	Matricea calculatorului se va genera odata ce s-a apasat New Game, iar
 	configuratia jucatorului se selecteaza dintr-o lista de configuratii
 	oferite prin linia de comanda. Daca nu s-a introdus nici o configuratie
 	atunci se iese automat si se afiseaza un mesaj de eroare. De asemenea, 
 	daca un fisier nu poate fi deschis se iese din program si se afiseaza
 	un mesaj de eroare.
 Cerinta 3:
 	Dupa ce s-a selectat o configuratie de joc pentru jucator se trece in
 	urmatoarea interfata unde se afiseaza 2 matrice, cea din stanga a 
 	jucatorului, iar cea din dreapta a calculatorului. Jucatorul poate
 	selecta o casuta din matricea calcualtorului folosind sagetiile sau 
 	mouseul( 1 click pentru a selecta si dublu pentru a lovi acel punct)
 	Nu se pot ataca casutele deja lovite. La randul calculatorului am 
 	decis sa aleg 1 secunda intre loviturile sale, deoarece 3 erau prea multe
 	si 3 secunde intre randul calculatorului si cel al jucatorului.
 	Dupa ce s-a incheiat jocul se afiseaza un mesaj specific.
 	De asemenea, daca apasati Q apare un mesaj de confirmare a dorintei de a
 	iesi din joc, iar daca raspunsul este "Yes" se iese din joc si se salveaza
 	prograsul.
 Cerinta 4:
 	Am ales tastele R pentru randomizare si D pentru a distruge. Astfel, cand
 	se apara pe D se distrug aleator 10 spatii si se revine la randul 
 	Jucatorului. De asemenea dupa fiecare lovitura se verifica daca jocul
 	s-a terminat si se afiseaza un mesaj specific. Cand se apasa R se 
 	randomizeaza mapa folosind algoritmul de generare al matricei 
 	Calculatorului.
 Cerinta 5:
 	Jocul se termina cand unul din jucatori isi pierde navele sau cand amandoi
 	le pierd si se afiseaza un mesaj specific.

Bonusuri:
 Implementari usoare:
 	Meniul Info:
 		Afisez informatii despre cum ar trebui jucat jocul si despre joc.
 	Mesaje Informative:
 		In timpul jocului jos se afla un mesaj care spuen al cui este randul
 		sau cat timp mai este pana la runda jucatorului. De asemenea sunt 
 		afisate informatii despre cum se poate naviga prin anumite meniuri
 		si despre cum se poate juca jocul si ce taste se pot folosi.
 	Afisarea configuratiei:
 		Atunci cand se selecteaza o configuratie de joc, aceasta este afisata
 		in coltul din stanga sus pentru a vedea despre ce configuratie este
 		vorba.
 Implementari cu grad mediu de dificultate:
 	Meniu cu configuratii vechi:
 		Dupa ce se iese din joc se salveaza intr-un fisier toate 
 		configuratiile introduse si se afiseaza in meniul 'Choose an old 
 		configuration' din Meniul 'New Game'. Astfel o sa apara o arie
 		mai larga de selectie a configuratiei.
 	Meniu pentru prea multe configuratii:
 		In 'New Game' si in 'Choose an old configuration', configuratiile
 		nu sunt asezate una sub alta ci doar cate una. Pentru a naviga 
 		printre configuratii se folosesc sagetiile Sus si Joc. Pentru
 		a trece la urmatoarele 2 optiune de quit si 'Choose an old 
 		configuration' se folosesc sagetiile stanga si drepta, la fel
 		si in meniul cu configuratii vechi. Sunt afisate informatii 
 		in fiecare meniu. Astfel am redus mult linii la una singura care
 		se schimba in functie de selectie.
 	Resposive >70%:
 		Am incercat sa fac jocul cat de cat responsive.  Astfel majoritatea
 		meniurilor arata bine la resize. Astfel matricele devin mai mici
 		cand fereastra se afla sub anumite valori. recomandat este
 		sa se joace in ferestre care cuprind tot ecranul sau
 		o rezolutie a ferestrei mai mare de 24 x 75. 
 		Sub o anumita rezolutie, in meniul de selectie al configuratiei
 		nu mai apare matricea in stanga, deoarece fereastra este prea mica.
 		A NU SE da resize cat in timpul
 		rundei calculatorului sau in timp ce se foloseste optiunea
 		de distrugere in avans a 10 spatii sau atunci cand se apasa Q si
 		apare fereastra de confirmare a iesirii din joc.
 	Scoreboard:
 		In meniul principal se afla o ptiune cu scoruri record in care se afla
 		un top 5 al celor mai bune scoruri. De asemenea, in timpul jocului se
 		afiseaza live scorul curent al jucatorului deasupra matricei 
 		calculatorului. Scorul se calcuelaza astfel:
 						Daca se nimereste un spatiul gol se aduna 1.
 						Daca se nimereste o nava creste bonusul de adaugare.
 						cu 1, iar daca se distruge o nava se dubleaza Bonusul
 						Bonusul se aduna la Scor.
 						Scorul se face si cand se selecteaza optiune de
 						distrugere in avans a 10 spatii.
 Implementare grea:
 	Algoritm pentru Calculator:
 		Calculatorul loveste random. Daca nimereste o parte din nava incearca
 		sa anticipeze in ce parte este nava cautand directie sa. Astfel
 		prima data verifica in stanga, apoi dreapta, apoi jos, apoi in sus.
 		Daca una din parti e buna, epuizeaza nava in acea parte apoi merge 
 		in sens opus sa vada daca o nava se mai afla acolo. Dupa ce nimereste
 		o intreaga nava, acesta cauta iar random.


Fisiere adaugate in plus:
	Fisierele T* sunt teste generate de mine. Pentru a genera teste am facut
	fisierul generare.c care genereaza random teste. pentru a genera un numar
	de teste se intra in makefile si acolo la optiunea generare se pune in 
	loc de acel numar valoare de teste pe care o doriti. si se ruleaza "make 
	generare".

Comenzi pentru make:
	"make" sau "make build" pentru a compila programul, "make run" pentru a 
	rula programul, "make runWLeaks" pentru a rula cu valgrind si a pune
	erorile intr-un fisier "ceva.txt". "make clean" pentru a sterge 
	executabilul, "make sterge" pentru a sterge executabilul generarii,
	"make generare" pentru a genera teste si "make test" pentru a 
	verifica daca transmiterea unui fisier gresit iese din program.

Navigare prin joc:
	Prin toate meniurile se navigheaza doar cu sagetiile. Numai in joc
	se pot selecta casute cu mouseul, iar mouseul merge doar in matricea
	calculatorului.

Am folosit structuri pentru a salva informatii despre configuratii, cum ar fi
directia in care se afla nava fata de punctul de incepere, coordonatele
punctelor de incepere ale navelor, vectorul navelor si vectorul vapoarelor, 
folosit pentru a vedea marimea navei respective. Aceste structuri au usurat
mult programul si munca de implementare a acestuia. 

Fisiere auxiliare:
	-ExampleMatrix.txt unde este un model de configuratie a jucatorului.
	-configuratii.txt unde se afla configuratiile folosite precedent.
	si care se pot refolosi in joc.
	-existaJoc.txt unde se verfifica daca jocul exista(1) sau nu(0).
	-Scor.txt unde se retine scorul de la un meci neterminat.
	-ScorRec.txt unde se retin cele mai mari 5 scoruri inregistrate.
	-Makefile unde sunt comenzile make.

Memory Leaks:
	Nu am putut rezolva leak-urile legate de ncurses. Am cautat pe net
	daca pot cumva sa eliberez memoria si am vazut ca in majoritatea
	cazurilor aceasta nu poate fi stearsa. Am putut dealoca complet
	doar ce tine de memoria alocata dinamic de mine.

P.S.:
	Am trimis proiectul fara nici o configuratie veche. Pentru a avea
	configuratii vechi se iasa din joc si se reintra iar, deoarece
	jocul salveaza configuratiile care au fost introduse ultima data 
	de jucator.
	In fisierul Scor.txt daca vreti sa nu se salveze scorul puteti pune
	valoare 0. De asemenea in ScorRec.txt daca vreti sa resetati toate 
	scorurile puneti 0 pe primele 5 linii. Fisierul ExampleMatrix.txt
	este un exemplu de configuratie. in fisierul configuratii.txt, 
	daca vreti sa nu fie nici o configuratie veche puneti 0 pe prima 
	linie. in fisierul existaJoc.txt, puneti 0 pe prima linie daca vreti
    	sa nu existe un joc. 

English:
This was a faculty project for Computer Programming course.
 Main ideas:
-I implemented the game in the terminal window, other WINDOWs being
used for shorter information.
-The game has as basic graphical functions initWindows and initText,
which colors the image with CYAN and prints the writing.
-The graphical interface is a simple one, easy to use, presenting several
in the following about each interface.
-From most interfaces you press Q or q, and some have
the option to select "QUIT".
-In the ExampleMatrix.txt file is a player configuration template,
where 'X' means a part of the ship, '' represents free space, and
'|' means the delimiting character between the cells.

Configuration example:
	| | | | | |X| | | | |
	|X|X|X|X| | | | | | |
	| | | | | | | |X|X|X|
	| |X| | | | | | | | |
	| | | | |X| | | | |X|
	| | | | |X| | | | | |
	|X|X| | |X| | |X|X| |
	| | | | | | | | | | |
	| | |X| | | | |X| | |
	| | |X| | | | | | | |
X is for ships.
Computer matrix generation:
The generation algorithm is simple and is based on the fact that
after placing a ship, its contour should be marked with -1, and then
when another ship is placed, check the area of ​​the rectangle
does not include numbers other than 0 and -1. E.g:
-1 -1 -1
-1 3 -1 -1 -1 -1
-1 3 -1 2 2 -1
-1 3 -1 -1 -1 -1
-1 -1 -1
it is valid for a bait of 3 and a bait of 2 with 1 space between them.

In the following I will explain more the requirements of the problem, and certain ones
details will be better explained in bonuses.
At the end there is information about the files.

Requirements and menus:
 Requirement 1:
	 Simple menu, with 4-5 options (New Game, Resume Game, if it has, Info,
	 Scoreboard, Quit (Q)). The Resume Game option appears only if it exists
	 a game that is not over.
	 New Game menu:
	 Once New Game is pressed from the main menu, the matrix is ​​generated
	 computer. This menu consists of 2 pieces. The top
	 includes selection of game settings that are files read from
	 command line. these are selected using the up and down arrows.
	 To move to the bottom, use the left and right arrows,
	 and navigating it is also done with the up and down arrows. Once
	 a configuration has been chosen to switch to the game interface.
	 More will be explained in bonuses.
	 Resume Game menu:
	 It only appears if there is an unfinished game.
 Requirement 2:
	 The computer matrix will be generated once the New Game is clicked again
	 the player configuration is selected from a list of configurations
	 offered through the command line. If no configuration has been entered
	 then it automatically exits and displays an error message. Also,
	 if a file cannot be opened it exits the program and is displayed
	 an error message.
 Requirement 3:
	 Once a game configuration has been selected for the player, switch to
	 the next interface where 2 matrices are displayed, the one on the left a
	 the player, and the one on the right of the computer. The player can
	 select a box in the computer matrix using its arrows
	 mouse (1 click to select and double to hit that point)
	 You can't attack the already hit houses. In the computer line I have
	 decided to choose 1 second between his shots, because 3 were too many
	 and 3 seconds between the computer and the player's turn.
	 After the game is over, a specific message is displayed.
	 Also, if you press Q, a message appears confirming the desire to
	 exit the game, and if the answer is "Yes" exit the game and save
	 Advancing.
 Requirement 4:
	 I chose the R keys for randomization and the D keys to destroy. Thus, when
	 defend on D randomly destroy 10 spaces and return to the turn
	 Player. Also after each shot it is checked if the game
	 finished and a specific message is displayed. When R is pressed
	 randomizes the map using the matrix generation algorithm
	 Computer.
 Requirement 5:
	 The game ends when one of the players loses his ships or when both
	 I lose them and a specific message is displayed.

Bonuses:
	 Easy implementations:
		 Info menu:
			 I display information about how the game should be played and about the game.
		 Informative Messages:
			 During the game below there is a message that says whose turn it is
			 or how long it is until the player's round. They are also
			 displayed information on how to navigate certain menus
			 and how to play the game and what keys to use.
		 Configuration display:
			 When a game configuration is selected, it is displayed
			 in the upper left corner to see what the configuration is about
			 words.
	 Implementations with medium degree of difficulty:
		 Menu with old configurations:
	 		After exiting the game all are saved in one file
	 		the configurations entered and are displayed in the 'Choose an old' menu
	 		configuration 'from the' New Game 'Menu. This is how an area will appear
	 		wider configuration selection.
	 	Menu for too many configurations:
	 		In 'New Game' and in 'Choose an old configuration', the configurations
	 		they are not placed one below the other but only one at a time. To navigate
	 		among the configurations are used the Up and Game arrows. For
	 		move on to the next 2 quit options and 'Choose an old
	 		configuration 'use the left and right arrows as well
	 		and in the menu with old configurations. Information is displayed
	 		in each menu. So I cut a lot of lines to one
	 		it changes depending on the selection.
		Responsive >70%:
			 I tried to make the game somewhat responsive. Thus the majority
			 the menus look good on resize. Thus the matrices become smaller
			 when the window is below certain values. is recommended
			 to play in windows that cover its entire screen
			 a window resolution greater than 24 x 75.
			 Below a certain resolution, in the configuration selection menu
			 the matrix on the left no longer appears because the window is too small.
			 DO NOT resize as long as possible
			 round your computer while using the option
			 advance destruction of 10 spaces or when pressing Q and
			 the exit confirmation window appears.
 		Scoreboard:
			 In the main menu there is a section with record scores in which it is located
			 a top 5 of the best scores. Also during the game
			 displays live the player's current score above the matrix
			 computer. The score is calculated as follows:
				 If an empty space is found, add 1.
				 If a ship is hit, the addition bonus increases.
				 with 1, and if a ship is destroyed, the Bonus is doubled
				 The bonus is added to the score.
				 The score is also made when the option is selected
				 advance destruction of 10 spaces.
 	Heavy implementation:
 		Computer Algorithm:
			 The computer hits randomly. If he hits a part of the ship, it tries
			 to anticipate in which direction the ship is, looking for its direction. So
			 first check left, then right, then down, then up.
			 If one of the parts is good, it exhausts the ship in that part and then it goes
			 in the opposite direction to see if a ship is still there. After he hits
			 an entire ship, it searches randomly again.


	Additional files added:
		T * files are tests generated by me. To generate tests I did
		the generate.c file that generates random tests. to generate a number
		of tests you enter the makefile and there at the generation option you put in
		place that number of test value you want. and run "make
		generation".

	Make commands:
		"make" or "make build" to compile the program, "make run" to
		run the program, "make runWLeaks" to run with valgrind and put
		errors in a "something.txt" file. "make clean" to wipe
		executable, "make delete" to delete the generation executable,
		"make generation" to generate tests and "make test" to
		check if the transmission of the wrong file leaves the program.

	Navigation through the game:
		You can navigate through all the menus only with the arrows. Only in the game
		you can select boxes with the mouse, and the mouse only goes in the matrix
		computer.

	I used structures to save information about configurations, such as
	the direction of the ship from the starting point, the coordinates
	ship starting points, ship vector and ship vector,
	used to see the size of the ship. These structures have eased
	much of the program and its implementation work.

	Auxiliary files:
		-ExampleMatrix.txt where is a player configuration model.
		-configurations.txt where the previously used configurations are located.
		and which can be reused in the game.
		-existaJoc.txt where it is checked if the game exists (1) or not (0).
		-Score.txt where the score from an unfinished match is retained.
		-ScorRec.txt where the top 5 recorded scores are retained.
		-Makefile where the make commands are.

	Memory Leaks:
		I couldn't fix the leaks related to the race. I searched the net
		if I can somehow free up memory and I've seen that in most
		in some cases it cannot be deleted. I was able to deal completely
		just about the memory dynamically allocated by me.

	PS .:
		I sent the project without any old configuration. To have
		old configurations come out of the game and re-enter because
		the game saves the configurations that were last entered
		of the player.
		In the Scor.txt file if you want the score not to be saved you can put
		value 0. Also in ScorRec.txt if you want to reset all
		put the scores on the first 5 lines. The ExampleMatrix.txt file
		is an example configuration. in the configuration.txt file,
		if you want it to be no old configuration put 0 on the first one
		line. In the fileJoc.txt file, put 0 on the first line if you want
		there should be no game.

