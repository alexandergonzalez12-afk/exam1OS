#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void shm_create(int* shared_mem, double** shared_memory);
void filler(double* shared_memory);
void signal_sender(int pid_b, int signal);
char conf[10]; // this char is to write yes 
int shared_mem; // this has the id of the shared memory
struct sigaction sa;
#endif
