// A very simple UDP client that reads a line of user input
// and sends it (message) to a UDP server. The client then 
// waits for the server to acknowledge the receipt of the 
// message and terminates.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_LEN 1024

int main(int argc, char **argv)
{
    int sock;
    struct hostent *hp;
    struct sockaddr_in server_addr, from_addr;
    socklen_t from_len;
    //char buf[MAX_LEN]={'K','n','o','c','k','!',' ','K','n','o','c','k','!','\0'} ;
    char buf[MAX_LEN]="Knock! Knock!";
    int num_bytes;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s server port\n", argv[0]);
        exit(0);
    }
    
    // create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }
    
    // resolve server name for its IP address, etc.
    hp = gethostbyname(argv[1]);
    if (NULL == hp) {
        perror("gethostbyname");
        exit(2);
    }
    
    // build remote server addr/port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    memcpy(&server_addr.sin_addr, hp->h_addr, hp->h_length);
    server_addr.sin_port = htons(atoi(argv[2]));
    
    // ask user for a message to be sent
    //printf("Please enter a message: ");
    memset(buf, 0, MAX_LEN);
    char buf[MAX_LEN]={'K','n','o','c','k','!',' ','K','n','o','c','k','!','\0'} ;
    //fgets(buf, MAX_LEN, stdin);
    
        
    // send message KNOCK KNOCK 
    num_bytes = sendto(sock, buf, strlen(buf), 0,
                       (struct sockaddr *)&server_addr,
                       sizeof(server_addr));
    if (num_bytes < 0) {
        perror("sendto");
        exit(3);
    }
    
    memset(buf, 0, MAX_LEN);                                //added
    // receive message WHOSE THERE
    from_len = sizeof(from_addr);   // must set (in & out)
    num_bytes = recvfrom(sock, buf, MAX_LEN, 0,
                         (struct sockaddr *)&from_addr,
                         &from_len);
    if (num_bytes < 0) {
        perror("recvfrom");
        exit(4);
    }

     // display received ack message
    //printf("Got an ack: ");

    //PRINT WHOSE THERE
    write(1, "Got an ack: ", 12);
    write(1, buf, num_bytes);
    printf("\n");
    
    memset(buf, 0, MAX_LEN);
    char buf[MAX_LEN]={'R','o','b','i','n','\0'} ;

    
    // send message ROBIN 
    num_bytes = sendto(sock, buf, strlen(buf), 0,
                       (struct sockaddr *)&server_addr,
                       sizeof(server_addr));
    if (num_bytes < 0) {
        perror("sendto");
        exit(3);
    }

    memset(buf, 0, MAX_LEN);                        //added
    // receive message ROBIN WHO?
    from_len = sizeof(from_addr);   // must set (in & out)
    num_bytes = recvfrom(sock, buf, MAX_LEN, 0,
                         (struct sockaddr *)&from_addr,
                         &from_len);
    if (num_bytes < 0) {
        perror("recvfrom");
        exit(4);
    }

    //PRINT ROBIN WHO 
    // display received ack message
    //printf("Got an ack: ");
    write(1, "Got an ack: ", 12);
    write(1, buf, num_bytes);
    printf("\n");

        memset(buf, 0, MAX_LEN);                    //added
        char buf[MAX_LEN]={'R','o','b','i','n',' ','y','o','u',' ','.','H','a','n','d',' ','o','v','e','r',' ','y','o','u','r',' ','c','a','s','h','.','\0'} ;
     // send message ROBIN YOU... 
    num_bytes = sendto(sock, buf, strlen(buf), 0,
                       (struct sockaddr *)&server_addr,
                       sizeof(server_addr));
    if (num_bytes < 0) {
        perror("sendto");
        exit(3);
    }
    
    
    // close sock to release resource
    close(sock);
       
    return 0;
}