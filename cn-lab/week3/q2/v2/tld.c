#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define MYPORT 9556
#define MAX 1025
#define BACKLOG 5
#define len_of_ip_list 5

void map_ip_addresses();
char *fetchIPAddresses(char *);

struct IP_struct
{
    char *IP;
    char *Name;
};

struct IP_struct list_of_ip_addr[len_of_ip_list];

int main()
{

    int sockfd, client_sockfd, sin_size;
    struct sockaddr_in my_addr, client_addr;
    char *IP_addr;
    char *domain_name;
    char *Msg;

    map_ip_addresses();

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    domain_name = (char *)malloc(sizeof(char) * MAX);
    Msg = (char *)malloc(sizeof(char) * MAX);
    IP_addr = (char *)malloc(sizeof(char) * MAX);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("\nSocket not created:");
        exit(1);
    }

    if (bind(sockfd, (const struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("\nNot Bound");
        exit(1);
    }

    printf("\nSocket bound");

    sin_size = sizeof(client_addr);

    while (1)
    {
        recvfrom(sockfd, (char *)domain_name, MAX, 0, (struct sockaddr *)&client_addr, &sin_size);
        IP_addr = "\0";
        IP_addr = fetchIPAddresses(domain_name);

        if (strcmp(IP_addr, "\0") == 0)
        {
            strcpy(Msg, "Incorrect Domain Name");
            sendto(sockfd, Msg, strlen(Msg), 0, (struct sockaddr *)&client_addr, sin_size);
            printf("\nIncorrect Domain Name!!!");
        }
        else
        {
            sendto(sockfd, (char *)IP_addr, strlen(IP_addr), 0, (struct sockaddr *)&client_addr, sin_size);
            printf("\nIP address sent!!!");
        }

        memset(IP_addr, '\0', MAX);
        memset(domain_name, '\0', MAX);
    }

    close(sockfd);

    return 0;
}

void map_ip_addresses()
{

    for (int i = 0; i < len_of_ip_list; i++)
    {
        list_of_ip_addr[i].IP = (char *)malloc(sizeof(char) * MAX);
        list_of_ip_addr[i].Name = (char *)malloc(sizeof(char) * MAX);
    }

    strcpy(list_of_ip_addr[0].IP, "248.28.142.210");
    strcpy(list_of_ip_addr[0].Name, "meta.com");

    strcpy(list_of_ip_addr[1].IP, "118.15.240.85");
    strcpy(list_of_ip_addr[1].Name, "yahoo.com");

    strcpy(list_of_ip_addr[2].IP, "51.204.60.59");
    strcpy(list_of_ip_addr[2].Name, "annauniv.edu.in");

    strcpy(list_of_ip_addr[3].IP, "45.205.90.67");
    strcpy(list_of_ip_addr[3].Name, "facebook.com");
    
    strcpy(list_of_ip_addr[4].IP, "235.205.90.67");
    strcpy(list_of_ip_addr[4].Name, "google.com");
}

char *fetchIPAddresses(char *domain_name)
{

    char *item = (char *)malloc(sizeof(char) * MAX);

    for (int i = 0; i < len_of_ip_list; i++)
    {
        if (strcmp(domain_name, (char *)(list_of_ip_addr[i].Name)) == 0)
        {
            item = list_of_ip_addr[i].IP;
            break;
        }
    }

    return item;
}