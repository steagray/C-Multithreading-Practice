#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

static atomic_flag lock = ATOMIC_FLAG_INIT;
static volatile int counter;

void *print_tid(void *tid){
	do {} while (atomic_flag_test_and_set(&lock));
	
	counter = counter + *(int*)tid;
	printf("Counter: %d\n", counter);

	atomic_flag_clear(&lock);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){
	if(argc != 5){
		printf("Usage: ./threads -x [# of threads] -y [counter]\n");
		exit(0);
	}
	
	int thread_count = atoi(argv[2]);
	int incby = atoi(argv[4]);
	counter = 0;
	pthread_t* threads = malloc(thread_count * sizeof(pthread_t));

	if(threads == NULL){
		printf("Unable to allocate memory for threads.\n");
		exit(-1);
	}

	int status, i;
	for(i = 0; i < thread_count; i++){
		printf("Main here, creating thread %d\n", i);
		int *j = &incby;
		status = pthread_create(&threads[i], NULL, print_tid, (void*)j);

		if(status != 0){
			printf("Oops, pthread_create returned error code %d\n", status);
			exit(-3);
		}
	}

	for(i = i; i >= 0; i--){
		pthread_join(threads[i], NULL);
	}
	free(threads);
	exit(0);
}
