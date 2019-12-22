build:
	gcc  battleship.c  -o battleship -lncurses -lm -Wall 
run:
	valgrind --leak-check=full --show-leak-kinds=all ./battleship ExampleMatrix.txt Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8 Test9 Test10
clean:
	rm battleship

test:
	./battleship Test11