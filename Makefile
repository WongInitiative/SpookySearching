all:
	$("Error, make to target thread or proc")
proc: searchtest.c multitest_proc.o
	gcc searchtest.c multitest_proc.o -o searchtest_proc.out
thread: searchtest.c multitest_thread.o
	gcc searchtest.c multitest_thread.o -o searchtest_thread.out
multitest_proc.o: multitest_proc.c
	gcc -c multitest_proc.c -lm -g
multitest_thread.o: multitest_thread.c
	gcc -c multitest_thread.c -lpthread -g
clean:
	rm multitest_*.o; rm searchtest_*.out
