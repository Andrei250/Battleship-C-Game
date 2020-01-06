build:
	gcc  battleship.c  -o battleship -ggdb3 -lncurses -lm -Wall 

run:
	./battleship ExampleMatrix.txt T1 T2 T3 T4 T5 T6 T7 T8 T9 T10

runWLeaks:
	valgrind --tool=memcheck --leak-check=full ./battleship ExampleMatrix.txt T1 T2 T3 T4 T5 T6 T7 T8 T9 T10 2> ceva.txt

clean:
	rm battleship

sterge:
	rm generat

rulare:
	gcc generare.c -o generat -ggdb3 -lncurses -lm -Wall

generare: rulare
	./generat 10

test:
	./battleship Test11423431