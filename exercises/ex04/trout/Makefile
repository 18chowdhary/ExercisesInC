main: trout.h util.h util.c trout.c main.c
	gcc -g trout.c util.c main.c -o main -Wall && ./main 127.0.0.1

test_util: util.h util.c minunit.h test_util.c
	gcc -g test_util.c util.c -o test_util && ./test_util

trout: trout.h trout.c util.h util.c
	gcc -g trout.c util.c -o trout

util: util.h util.c
	gcc -g util.c -o util
