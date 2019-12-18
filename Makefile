build:
	gcc  battleship.c  -o battleship -lncurses -lm -Wall 
run:
	./battleship ExampleMatrix.txt
clean:
	rm battleship