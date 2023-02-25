tas: threads_taslock.c
	gcc -pthread -o threads threads_taslock.c

locks: threads_locks.c
	gcc -pthread -o threads threads_locks.c

nosync: threads_nosync.c
	gcc -pthread -o threads threads_nosync.c
