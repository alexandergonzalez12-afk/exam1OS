#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "functions.h"

// it declares the signal handler for SIGUSR2
void handle_sigusr2(int signal);

double* shared_memory;  // variable to access shared memory 

int main() {
    printf("A's pid: %d\n", getpid());

    //  with this i will create the shared memory and fill it 
    shm_create(&shared_mem, &shared_memory);

    // here we print the mem id so you can input it in b so it attaches 
    printf("memory id: %d\n", shared_mem);


    filler(shared_memory);


    //  this is the setup for the sigusr2
    sa.sa_handler = handle_sigusr2;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR2, &sa, NULL);

    // here we will write the pid for to attach B to A
    int pid_b;
    printf("B's PID: ");
    scanf("%d", &pid_b);

    // small delay so that process B can attach to shared memory
    printf("waiting... \n");

    // here we we write yes to confirm that we have inputed everything
    printf("write yes' then press enter when you have inputed everything in B: ");
    scanf("%s", conf);

    if (conf[0] == 'y' || conf[0] == 'Y') {
        // here im sending the signal process to B 
        signal_sender(pid_b, SIGALRM);
    }

    // looping for 500ms 
    while (1) {
        usleep(500000);  
    }

    return 0;
}
