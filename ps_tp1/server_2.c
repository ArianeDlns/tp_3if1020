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

/*
Avec kill -s INT <PID> le message de l'handler est affiché 
Avec kill <PID> le message de l'handler ne s'affiche pas tant qu'on a pas rajouté la sigaction avec SIGTERM
Avec kill -s KILL <PID> le message de l'handler n'est pas affiché avec <FATHERPID> le terminal est fermé. 
Avec un signal SIGKILL par définition de ce type de signal il n'est pas possible de l'intercepter. (cf. documentation):
"signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP."

En retirant la variable running CTLR + C et kill <PID> sont reçus mais n'arrêtent pas le processus en cours. 
En rajoutant kill -9 <PID> cette fois le processus est bien Killed ! 

La fonction exit_message() s'execute bien avec un CTRL+C et un kill. 
En revanche un kill -9 ne permettra pas de voir le message de sortie. 
*/

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
          printf("randint: %d \n" , (random_nub));

          sleep(1);
    }
        
    return EXIT_SUCCESS;
}

