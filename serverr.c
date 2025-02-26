#include <signal.h>
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
const int MAX_PENDING = 5;
const int SERVER_PORT = 11002;
const int MAX_RESPONSE = 20;

/* all the possible resposnes that a user can get */
const char *possible_response[] = {
    "It is certain", "It is decidedly so",
    "Without a doubt", "Yes, definitely",
    "You may rely on it", "As I see it, yes",
    "Most likely", "Outlook good",
    "Yes", "Signs point to yes",
    "Reply hazy try again", "Ask again later",
    "Better not tell you now", "Cannot predict now",
    "Concentrate and ask again", "Don't count on it",
    "My reply is no", "My sources say no",
    "Outlook not so good", "Very doubtful"
};

int s = -1;

/*      
 * handling SIGINT, (CTRL-C) pressed by the user to close the socket 
 * and print message 
 */
void handle_sigint(int sig)
{   
    /* check if the socket has been created, if yes then close the socket */
    if(s != -1) {   
        close(s);
    } 
    printf("Exit Successfully \n");
    exit(EXIT_SUCCESS); 
}

/*
 * This function is going creates a socket ti listen at a specific
 * port , waits for client connections, recieves a question from
 * the client, then selects a random response froma list of 
 * predefined responses and then sends the reponse back to the client
 * after formatting it.
 */    
int 
main(void)
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    socklen_t new_len;
    int new_s, len;
    
    /* signal handeler to handel ctrl-c */
    signal(SIGINT, handle_sigint);

    /* build address data structure */
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;

    /* EVERY INTERFACE ON THE SERVER FOR THIS SOCKET */
    sin.sin_addr.s_addr = INADDR_ANY;

    /* What port i want to listen on */
    sin.sin_port = htons(SERVER_PORT);

    /* setup passive open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1 )
        err(1, "Unable to open  the socket");
    if ((bind(s, (struct sockaddr*)&sin,sizeof sin)) == -1) {
        close(s);
        err(2, "Unable to bind socket");
    }
    if ((listen(s, MAX_PENDING)) == -1) {
        close(s);
        err(3, "Unable to listen on socket");
    }

    /* wait for a connection, then recieve and print message */
    while (1) {
        memset(buf, 0, sizeof buf);
        new_len = sizeof sin;
        
        if ((new_s = accept(s,(struct sockaddr*)&sin, &new_len)) == -1) {
            close(s);
            err(4, "Accept error"); 
        }
        if (recv(new_s, buf, sizeof buf, 0) > 0) {
            unsigned int choice = arc4random_uniform(MAX_RESPONSE);
            char response[MAX_LINE];
            len = strnlen(buf, sizeof buf);
            buf[len - 1] = '\0';

            /* Format the response as required */
            snprintf(response, sizeof response, "Q: \"%s\" " "\n" "R: \"%s\" \n", 
                buf, possible_response[choice]);
                            
            /* Send response back to the client */
            if (send(new_s, response, strlen(response), 0) < 0) {      
                err(5, "Response send failed");
            }   
            close(new_s);   
	}
    }           
    close(s);
    return 0;
}
