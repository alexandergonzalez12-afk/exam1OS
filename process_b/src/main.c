#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "functions.h"

double* shared_memory;  
extern int flag_init_buffer_filled;  
pthread_mutex_t memory_mutex = PTHREAD_MUTEX_INITIALIZER;  

void sigalhandler(int signal);  
void* ProcessData(void* arg);     

// this will check the flag , and see if it needs changing
void* CheckingBuffer(void* arg) {
    while (1) {
        if (flag_init_buffer_filled == 1) {
            printf("buffer filled\n");
            flag_init_buffer_filled = 0;

            //  here im creating and detaching the process data
            pthread_t procdata_th;
            pthread_create(&procdata_th, NULL, ProcessData, NULL);
            pthread_detach(procdata_th);
        }
        usleep(500000);  
    }
    return NULL;
}

int main() {
    printf("B's pid: %d\n", getpid());

    // signal handler for SIGALRM
    struct sigaction sa;
    sa.sa_handler = sigalhandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);

    // asking for the memory id in order to attach it
    int shared_mem;
    printf("enter the mem id: ");
    scanf("%d", &shared_mem);

    // attaching the shared memory
    attach_shared_memory(shared_mem, &shared_memory);

    // starting the checking thread
    pthread_t checking_thread;
    pthread_create(&checking_thread, NULL, CheckingBuffer, NULL);

    printf("checking the thread... (MAKE SURE TO WRITE NOW EVERYTHING ON B , BECAUSE IT WONT WORK\n");


    while (1) {
        usleep(500000);  
    }

    return 0;
}
