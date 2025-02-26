/* 
 * Name : Avinash
 * COURSE-SECTION : CS440 SP25 
 * Assignment : 01
 * Due Date : 02/14/2025
 * Collaborators : -
 * Resources : man page
 * Description: Client Code for the Assignment - 01
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int MAX_LINE = 512;
const int SERVER_PORT = 11002;

/*
 * main() - It sets up a client socket, then connects to the server and 
 * sends a user-input question to the server, and displays the response 
 * sent by the server.
 * It handles errors and closes the socket after communication or error.
 */
int
main(int argc, char* argv[])
{
    char buf[MAX_LINE];
    struct hostent *hp;        
    struct sockaddr_in sin;
    char *host;
    int s, check_space;
    size_t len;

    if (argc == 2)
        /* name of machine you want to connect */
        host = argv[1]; 
    else{
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }
    
    /* translate the host name into an IP address */
    hp = gethostbyname(host);
    
    /* if error in fetching hostname */
    if (hp == NULL)
        errx(1, "unknown host %s", host);

    /* build address data structure */
    memset(&sin, 0, sizeof sin);
    sin.sin_family = AF_INET;
    memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);

    /* Create the socket */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        err(2, "socket creation failed");
    }

    /* Connect to the server */
    if (connect(s, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
        close(s);
        err(3, "connection failed");
    }

    /* Get the question from the user */ 
    printf("%s", "Enter your (yes/no) question: ");
    memset(buf, 0, sizeof buf);
    
    /* checking various constraints on the user input */
    if (fgets(buf, sizeof buf, stdin) > 0) {
        check_space = 1;
        
        /* loop to check if the user response is all spaces */
        for (int i = 0; buf[i] != '\0'; i++) {
            if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n') {
                 check_space = 0;
                 break;
            }
        }
        
        /* if the user has entered all spaces print error and close socket */
        if (check_space) {
            close(s);
            errx(4, "error: empty question !!!");
        } 

       /* check if the input exceeds the buffer size */ 
        if (buf[strlen(buf) - 1] !=  '\n' ) { 
            errx(5, "input exceeds expected length.\n");
            close(s);
        }   	
	len = strnlen(buf, sizeof buf);
	if (send(s, buf, len, 0) < 0) {
            close(s);
            errx(6, "send Failed");
        }   
	
        memset(buf, 0, sizeof buf);
        if (recv(s, buf, sizeof buf, 0) > 0) {
            printf("%s", buf);
            close(s);
        }
        else {
            close(s);
            errx(7, "receive error");
        }
    } 
    else {
        printf("%s", "Failed to read input/n");
    }
    close(s);
    return 0;
}


