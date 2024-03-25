project: user_interface.o database.o
	gcc -o project user_interface.o database.o

user_interface.o: user_interface.c database.h
	gcc -pedantic-errors -Wall -c -ansi user_interface.c

database.o: database.c record.h
	gcc -pedantic-errors -Wall -c -ansi database.c
