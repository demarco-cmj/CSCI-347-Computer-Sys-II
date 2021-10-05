test_find: test_find.o find.o
	gcc -o test_find test_find.o find.o

test_find.o: test_find.c find.h
	gcc -c test_find.c

find.o: find.c find.h
	gcc -c find.c

clean:
	rm -f test_find test_find.exe
	rm -f *.o *.bak *~*
