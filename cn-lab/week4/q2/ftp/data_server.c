#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 2020 // 20 not working in my system, so 2020
#define BUFSIZE 1024

void getFile(char buff[], char data[])
{
    FILE *fp = fopen(buff, "r");
    if (fp == NULL)
    {
        printf("\nFile not found\n");
        sprintf(data, "ERROR: FILE NOT FOUND!!");
        return;
    }

    memset(buff, 0, BUFSIZE);
    while (fgets(buff, BUFSIZE, fp))
    {
        strcat(data, buff);
    }

    fclose(fp);
}

void send_recv(int i, fd_set *master, int sockfd, int fdmax)
{
    int nbytes_recvd, j;
    char recv_buf[BUFSIZE], buf[BUFSIZE];

    //Receive the filename from client!
    memset(recv_buf, 0, BUFSIZE);
    if ((nbytes_recvd = recv(i, recv_buf, BUFSIZE, 0)) < 0)
    {
        perror("recv");
    }

    memset(buf, 0, BUFSIZE);
    getFile(recv_buf, buf);

    printf("%s = %s\n", recv_buf, buf);
    //

    // SEND THE CONTENTS TO CLIENT!
    if(send(i, buf, sizeof(buf), 0) == -1)
    {
        perror("send");
    }
    //

    // Receive 'exit' command to close this DATA CONNECTION
    memset(recv_buf, 0, BUFSIZE);
    if ((nbytes_recvd = recv(i, recv_buf, BUFSIZE, 0)) < 0)
    {
        perror("recv");
    }

    // Send Bye to the client!
    printf("socket %d hung up\n", i);
    close(i);
    FD_CLR(i, master);
}

void connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr)
{
    socklen_t addrlen;
    int newsockfd;

    addrlen = sizeof(struct sockaddr_in);
    if ((newsockfd = accept(sockfd, (struct sockaddr *)client_addr, &addrlen)) == -1)
    {
        perror("accept");
        exit(1);
    }
    else
    {
        FD_SET(newsockfd, master);
        if (newsockfd > *fdmax)
        {
            *fdmax = newsockfd;
        }
        printf("new connection from %s on port %d \n", inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
    }
}

void connect_request(int *sockfd, struct sockaddr_in *my_addr)
{
    int yes = 1;

    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }

    my_addr->sin_family = AF_INET;
    my_addr->sin_port = htons(PORT);
    my_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    memset(my_addr->sin_zero, 0, sizeof my_addr->sin_zero);

    if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }

    if (bind(*sockfd, (struct sockaddr *)my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Unable to bind");
        exit(1);
    }
    if (listen(*sockfd, 10) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("Server Waiting for client on port %d\n", PORT);
    fflush(stdout);
}

int main()
{
    fd_set master;
    fd_set read_fds;
    int fdmax, i;
    int sockfd = 0;
    struct sockaddr_in my_addr, client_addr;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    connect_request(&sockfd, &my_addr);
    FD_SET(sockfd, &master);

    fdmax = sockfd;
    while (1)
    {
        read_fds = master;
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(4);
        }

        for (i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &read_fds))
            {
                if (i == sockfd)
                    connection_accept(&master, &fdmax, sockfd, &client_addr);
                else
                    send_recv(i, &master, sockfd, fdmax);
            }
        }
    }
    return 0;
}