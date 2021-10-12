/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_6.c
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
// For TCP
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

bool running(true);

void stop_handler(int sig) //Stop handler
{
    printf("Received: signal %d \n", (sig));
    running = false;
}

void exit_message() //Function adding an exit message
{
    printf("Ending the program: %d... Goodbye, see you soon, take care ! :) \n", getpid());
}

int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");
	
    //Structure for sigaction
    struct sigaction s;
    s.sa_handler = &stop_handler;
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTERM, &s, NULL);
    sigaction(SIGPIPE, &s, NULL);
    
    while (running)
    {
        printf("[Server process], Pid: %d \n", getpid());

        int number_sent{rand()%100};
        if (write(client_sock, &number_sent, 1)==0){
            stop_handler(2);
        }
        printf("Random number sent : %d\n", number_sent);
        sleep(1);
    }

    atexit(exit_message);
    return EXIT_SUCCESS;
	
	return 0;
}