/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
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

int main()
{
    // structure for sigaction 
    struct sigaction s; 
    s.sa_handler = &stop_handler; 
    s.sa_flags = 0; 
    sigaction(SIGINT, &s, NULL);

    printf("Starting program \n");

    while (running){
        // boucle infine
          int pid(getpid());
          int fatherpid(getppid());
          int random_nub(rand() % 100);

          printf("pid: %d \n" , (pid));
          printf("father pid: %d \n" , (fatherpid));
          printf("randint: %d \n" , (random_nub));

          sleep(1);
    }
        
    return EXIT_SUCCESS;
}

