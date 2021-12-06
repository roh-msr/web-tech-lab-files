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

int main()
{

    int sockfd, sin_size;
    char Domain_Name[MAX];
    char MSG[MAX];
    struct sockaddr_in server_sock;

    server_sock.sin_family = AF_INET;
    server_sock.sin_port = htons(MYPORT);
    server_sock.sin_addr.s_addr = INADDR_ANY;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("\nSocket not created!!!");
        exit(1);
    }

    while (1)
    {
        memset(MSG, '\0', MAX);
        printf("\nEnter the Domain name:");
        scanf("%s", Domain_Name); //gets the domain name from the user

        printf("\nAsking Root server.....");

        sin_size = sizeof(server_sock);
        sendto(sockfd, Domain_Name, strlen(Domain_Name), 0, (struct sockaddr *)&server_sock, sin_size);
        recvfrom(sockfd, (char *)MSG, MAX, 0, (struct sockaddr *)&server_sock, &sin_size); //root server returns the port number of TLD
        printf("\nGot the TLD port number....%s", MSG);

        server_sock.sin_port = htons(atoi(MSG));

        memset(MSG, '\0', MAX);

        printf("\nAsking the TLD.....");
        sendto(sockfd, Domain_Name, strlen(Domain_Name), 0, (struct sockaddr *)&server_sock, sizeof(server_sock));
        recvfrom(sockfd, MSG, MAX, 0, (struct sockaddr *)&server_sock, &sin_size);

        if (strcmp(MSG, "Incorrect Domain Name") == 0)
        {
            printf("\nWeb Page Not Found!!!");
        }
        else
        {
            printf("\nGot the IP address");
            printf("\n%s", MSG);
        }

        printf("\nDo you want to continue ?y/n:");
        char ch;

        scanf("%c", &ch);
        scanf("%[^\n]c", &ch);

        if (ch == 'y')
        {
            server_sock.sin_port = htons(MYPORT);
            continue;
        }
        else
            break;
    }
    close(sockfd);
    return 0;
}