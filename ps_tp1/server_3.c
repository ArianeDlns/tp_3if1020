/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
 */

/*
On peut distinguer les deux types de messages en fonction du <pid> et <fatherpid>. 
CTRL+C tue les deux processus. 

En arrêtant le processus avec kill <pid>, le père ou le fils continue d'exister. 
 */


// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>
// For signal management
#include <signal.h>

bool running(true);

void stop_handler(int sig){
    // stop handler
    printf("Received: signal %d \n" , (sig));
    running = false;
}

void exit_message(){
    // function adding an exit message 
     printf("Ending the program.... Goodbye, see you soon, take care ! :) \n" );
}

int main()  
{
    pid_t c_pid = fork();

    if (c_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);} 

    // structure for sigaction 
    struct sigaction s; 
    s.sa_handler = &stop_handler; 
    s.sa_flags = 0; 
    sigaction(SIGINT, &s, NULL);
    // adding SIGTERM signal 
    sigaction(SIGTERM, &s, NULL);

    printf("Starting program \n");

    while (running){
        // boucle infine
          int pid(getpid());
          int fatherpid(getppid());
          int random_nub(rand() % 100);

          printf("pid: %d \n" , (pid));
          printf("father pid: %d \n" , (fatherpid));
          printf("randint: %d \n\n" , (random_nub));

          sleep(1);
    }

    atexit(exit_message);

    return EXIT_SUCCESS;
}

