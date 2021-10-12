/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_5.c
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
// For strlen
#include <string.h>
// For fifo
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>

bool running(true);
//Fifo path specific please change it before using this
char const * const FIFO_PATH = "/Users/ariane/Desktop/fifo_ps";

void stop_handler(int sig) //Stop handler
{
    printf("Received: signal %d \n", (sig));
    running = false;
}

void exit_message() //Function adding an exit message
{
    printf("Ending the program: %d... Goodbye, see you soon, take care ! :) \n", getpid());
}

int main()
{
    //Structure for sigaction
    struct sigaction s;
    s.sa_handler = &stop_handler;
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTERM, &s, NULL);

    int read_fifo = open(FIFO_PATH, O_RDONLY);
    
    while (running)
    {
        printf("[Client process], Pid: %d \n", getpid());

        int number_received{};
        if (read(read_fifo, &number_received, 1)==0){
            stop_handler(2);
        }
        printf("Random number received : %d\n", number_received);
        sleep(1);
    }

    atexit(exit_message);

    return EXIT_SUCCESS;
}
