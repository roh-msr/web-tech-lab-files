#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MYPORT 14904
#define MAX 500
#define BACKLOG 5
#define TLD_PORT 13456

int main()
{

    int sockfd, sin_size;
    char MSG[MAX];

    struct sockaddr_in my_addr, client_addr;

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket not created:");
        exit(1);
    }

    if (bind(sockfd, (const struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
        perror("\nSocket not Bound:");
        exit(1);
    }
    else
        printf("\nSocket Bound!!!");

    sin_size = sizeof(client_addr);
    while (1)
    {
        recvfrom(sockfd, MSG, MAX, MSG_WAITALL, (struct sockaddr *)&client_addr, &sin_size);
        printf("\nGot a query from the client ");
        printf("%s", MSG);
        //assume that the client always send the correct website name so that we don't need to validate that
        memset(MSG, '\0', MAX);

        snprintf(MSG, MAX, "%d", TLD_PORT);
        sendto(sockfd, (char *)MSG, strlen(MSG), 0, (const struct sockaddr *)&client_addr, sin_size); //it sends the port number of the TLD
        printf("\nRedirected the client to the TLD");
    }

    close(sockfd);
    return 0;
}