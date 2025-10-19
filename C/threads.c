#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 100
#define ACCOUNTS 20

int accounts[ACCOUNTS] = {0};
pthread_mutex_t account_lock = PTHREAD_MUTEX_INITIALIZER;

void *run_thread (void *argument) {
	int *p = argument;
    int pos = *p;

	for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&account_lock);
		accounts[*p] += i*pos;
        pthread_mutex_unlock(&account_lock);
	}

	return NULL;
}

void create_n_threads(int n_threads) {
    assert (0 < n_threads && n_threads < MAX_THREADS);
    pthread_t thread_id1;
	int thread_number1 = 1;
	pthread_create(&thread_id1, NULL, run_thread, &thread_number1);

    pthread_t thread_id[n_threads];
	int argument[n_threads];

    for (int i = 0; i < n_threads; i++) {
		argument[i] = i;
		pthread_create(&thread_id[i], NULL, run_thread, &argument[i]);
	}
    for (int i = 0; i < n_threads; i++) {
		pthread_join(thread_id[i], NULL);
	}


    for (int i = 0; i < n_threads; i++) {
        pthread_mutex_lock(&account_lock);
        printf("Account %d has $%d.00 in it.\n", i+1, accounts[i]);
        pthread_mutex_unlock(&account_lock);
    }

}


int main(void) {
    
    create_n_threads(15);

    return EXIT_SUCCESS;
}