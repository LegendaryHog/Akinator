all: compall run

compall:
	gcc Tree/Tree.c problem/problem.c problem/main.c -o aki.out

run:
	./aki.out 

valrun:
	valgrind --leak-check=full -s ./aki.out