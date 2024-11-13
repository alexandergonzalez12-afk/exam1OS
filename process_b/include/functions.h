#ifndef FUNCTIONS_H
#define FUNCTIONS_H


extern double* shared_memory;
extern pthread_mutex_t memory_mutex;
void sigalhandler(int signal);
void* ProcessData(void* arg); 
extern int flag_init_buffer_filled;   
void attach_shared_memory(int shmid, double** shared_memory);


#endif
