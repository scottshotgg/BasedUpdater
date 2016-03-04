#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    while(1)
    {
        bzero(buffer,256);
        char* this = "a";
        n = write(sockfd, this, strlen(this));
        n = read(sockfd, buffer, sizeof(buffer));
        printf("%s\n", buffer);
        getchar();
        n = write(sockfd, this, strlen(this));

        if (n < 0) 
        {
            error("ERROR writing to socket");
            close(sockfd);
        }

        int bytes_read, bytes_written;
        int mybuffer[1000];
        //umask();
        int fd = open(buffer, O_RDWR | O_CREAT, 0400); // for some reason the macros for permissions don't work
        printf("file opened under name: %s\n", buffer);
        getchar();

        bzero(buffer,256);

        do
        {   
            printf("We are in the loop \n");
            bytes_read = read(sockfd, mybuffer, sizeof(mybuffer));
            printf("We are reading!! %s\n", mybuffer);

            printf("\n%c\n", mybuffer[0]);

            if(mybuffer[0] != 'e')
                printf("we got an e: %c", mybuffer[0]);

            bytes_written = write(fd, mybuffer, bytes_read);
            printf("We are writing!! \n");

            printf("Bytes read: %d\nBytes written: %d\n", bytes_read, bytes_written);
        }
        while(bytes_read > 0);

        printf("%s\n", "out of the inner loop");

       /* if (n < 0)
        {
            error("ERROR reading from socket");
            close(sockfd);
        } */
             
        printf("File transfer completerino");

        close(fd);
    }

    close(sockfd);

    printf("The end \n");
    return 0;
}