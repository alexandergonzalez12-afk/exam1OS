#include <stdio.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

extern double* shared_memory;  
 // this is the signal handler for SIGUSR2
void handle_sigusr2(int signal) {
    char data_to_print[15];
    for (int i = 0; i < 100; i++) {
        snprintf(data_to_print, 10, "%.2f\n", shared_memory[i]);
        write(STDOUT_FILENO, data_to_print, strlen(data_to_print));
    }
}
 // this is the function to create the shared memory
void shm_create(int* shared_mem, double** shared_memory) {
    *shared_mem = shmget(IPC_PRIVATE, 100 * sizeof(double), IPC_CREAT | 0666);
    if (*shared_mem == -1) {
        perror("failed to create mem");
        return;
    }

    *shared_memory = (double*)shmat(*shared_mem, NULL, 0);
    if (*shared_memory == (void*)-1) {
        perror("failed to attach mem");
    }
}
 // the function filler just fills the memory with even numbers
void filler(double* shared_memory) {
    for (int i = 0; i < 100; i++) {
        shared_memory[i] = (i + 1) * 2;
    }
    printf("mem filled with even num.\n");
}
 // this function sends a signal to b 
void signal_sender(int pid_b, int signal) {
    if (kill(pid_b, signal) == -1) {
        perror("failed to send signal to B");
    } else {
        printf("signal sent to B.\n");
    }
}
