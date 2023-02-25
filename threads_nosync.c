#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int incr;

void *print_tid(void *tid){
	(*(int *)tid) = *(int*)tid + incr;
	printf("Counter: %d\n", *(int *)tid);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){
	if(argc < 5){
		printf("Usage: ./threads -x [# of threads] -y [counter]\n");
		exit(0);
	}
	
	int thread_count = atoi(argv[2]);
	incr = atoi(argv[4]);
	int counter = 0;
	pthread_t* threads = malloc(thread_count * sizeof(pthread_t));

	if(threads == NULL){
		printf("Unable to allocate memory for threads.");
		exit(1);
	}

	int status, i;
	for(i = 0; i < thread_count; i++){
		printf("Main here, creating thread %d\n", i);
		status = pthread_create(&threads[i], NULL, print_tid, (void *)&counter);

		if(status != 0){
			printf("Oops, pthread_create returned error code %d\n", status);
			exit(-1);
		}
	}

	for(i = i; i >= 0; i--){
		pthread_join(threads[i], NULL);
	}
	free(threads);
	exit(0);
}
