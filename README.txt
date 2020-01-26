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
