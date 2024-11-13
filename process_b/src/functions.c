#include <sys/shm.h>  
#include <sys/ipc.h>  
#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "functions.h"


int flag_init_buffer_filled = 0;  

// ProcessData is going to send the signal to A and invert the val 
void* ProcessData(void* arg) {
    printf("processing the data\n");

    // lock the shared memory , ok the logic here is that if its locked then one process can modify it

    pthread_mutex_lock(&memory_mutex);

    for (int i = 0; i < 100; i++) {
        shared_memory[i] = -shared_memory[i];
    }

    pthread_mutex_unlock(&memory_mutex);

    printf("mem has been inverted\n");

    // Send SIGUSR2 to Process A
    int pid_a;
    printf("write me the pid of A to send the sigusr2 please: ");
    scanf("%d", &pid_a);
    kill(pid_a, SIGUSR2);

    return NULL;
}

// Handle SIGALRM by setting the flag
void sigalhandler(int signal) {
    printf("received SIGALRM\n");
    flag_init_buffer_filled = 1;
}

// Attach shared memory
void attach_shared_memory(int shared_mem, double** shared_memory) {
    *shared_memory = (double*)shmat(shared_mem, NULL, 0);
    if (*shared_memory == (void*)-1) {
        perror("failed to attach mem");
    } else {
        printf("attached to shared memory!\n");
    }
}
