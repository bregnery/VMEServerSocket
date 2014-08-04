/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "CAENVMElib.h"
#include "CAENVMEtypes.h"
#include "DataRead.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     int32_t storage[6];
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     //n = read(newsockfd,buffer,255);
     while(1){
     	n = read(newsockfd,storage, sizeof(storage));
     	if (n < 0) error("ERROR reading from socket");
     	if (n != sizeof(storage)) error("Sized received is wrong"); printf("%d\n", n);
     	printf("Recieved Data!");

     	// Identify the function to read the data
     	if (storage[0] == 1) ReadCAENVME_Init(storage, newsockfd);
     	else if (storage[0] == 2) ReadCAENVME_End(storage, newsockfd);
     	else if (storage[0] == 3) ReadCAENVME_WriteCycle(storage, newsockfd);
     	else if (storage[0] == 4) ReadCAENVME_ReadCycle(storage, newsockfd);
     	else printf("Undefined function \n");
     }
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     usleep(10000);
     close(newsockfd);
     close(sockfd);
     return 0; 
}
