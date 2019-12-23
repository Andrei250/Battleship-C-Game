build:
	gcc  battleship.c  -o battleship -ggdb3 -lncurses -lm -Wall 

run:
	./battleship ExampleMatrix.txt Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8 Test9 Test10

runWLeaks:
	valgrind --leak-check=full ./battleship ExampleMatrix.txt Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8 Test9 Test10 2> ceva.txt

clean:
	rm battleship
	
test:
	./battleship Test11