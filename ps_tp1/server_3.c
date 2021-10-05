/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
 */

/*
* On peut distinguer les deux types de messages en fonction du <pid> et <fatherpid>. 
* CTRL+C tue les deux processus.
* En arrêtant le processus avec kill <pid>:
* - kill du fils: le processus fils est toujours listé avec "ps a", il disparait après le kill du père 
* - kill du père: le processus fils continue d'exister
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
// For wait
#include <sys/wait.h>

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
    if(c_pid==0){
        printf("Child process \n");
    }
    else{
        printf("Father process \n");
        int child_status;
        wait(&child_status);
        printf("Child terminated with status %d\n", child_status);
    }

    // structure for sigaction 
    struct sigaction s; 
    s.sa_handler = &stop_handler; 
    s.sa_flags = 0; 
    sigaction(SIGINT, &s, NULL);
    // adding SIGTERM signal 
    sigaction(SIGTERM, &s, NULL);
    atexit(exit_message);

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

    return EXIT_SUCCESS;
}

