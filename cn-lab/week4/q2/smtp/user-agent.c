#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define BUFSIZE 1024
#define SERVERS_COUNT 2

struct server_config {
    char* mail_id;
    int server_port;
};

struct server_config SERVER_LIST[SERVERS_COUNT];

void setServerConfigs()
{

    for (int i = 0; i < SERVERS_COUNT; i++)
    {
        SERVER_LIST[i].mail_id = (char *)malloc(sizeof(char) * BUFSIZE);
    }

    strcpy(SERVER_LIST[0].mail_id, "greenlantern@gmail.com");
    SERVER_LIST[0].server_port = 8011;

    strcpy(SERVER_LIST[1].mail_id, "sinestro@outlook.com");
    SERVER_LIST[1].server_port = 8012;
}

int fetchPORT(char *mail_id_string)
{
    int port = -1;

    for (int i = 0; i < SERVERS_COUNT; i++)
    {
        if (strcmp(mail_id_string, (char *)(SERVER_LIST[i].mail_id)) == 0)
        {
            port = SERVER_LIST[i].server_port;
            break;
        }
    }

    return port;
}

void make_connection(int* c_sock, int OUR_PORT){
    struct sockaddr_in serverAddr;

    // Create a socket
    *c_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (*c_sock < -1)
    {
        perror("Socket Error: ");
        exit(-1);
    }

    // assign IP, port
    memset(&serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(OUR_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (connect(*c_sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Connect Error: ");
        exit(1);
    }
}

void getMyMails(int *c_sock, int my_port) {
    char buffer[BUFSIZE * 10];
    
    make_connection(c_sock, my_port);

    memset(buffer, '\0', BUFSIZE * 10);
    sprintf(buffer, "2");
    send(*c_sock, buffer, strlen(buffer), 0);

    memset(buffer, '\0', BUFSIZE * 10);
    if (recv(*c_sock, buffer, BUFSIZE * 10, 0) < 0)
    {
        printf("Error in receiving data.\n");
    }
    else
    {
        printf("\nServer: %s\n\n", buffer);
    }
}

void composeMail(int *c_sock, int my_port) {
    char buffer[BUFSIZE];
    char to_email[100];
    char subject[200];
    char message[300];
    
    make_connection(c_sock, my_port);

    sprintf(buffer, "1");
    send(*c_sock, buffer, BUFSIZE, 0);

    memset(buffer, '\0', BUFSIZE);
    if (recv(*c_sock, buffer, BUFSIZE, 0) < 0)
    {
        printf("Error in receiving data.\n");
        return;
    }
    else
    {
        printf("\nServer: %s\n\n", buffer);
    }

    char dummy;
    scanf("%c", &dummy);
    printf("TO : ");
    scanf("%[^\n]s", to_email);

    scanf("%c", &dummy);
    printf("SUBJECT : ");
    scanf("%[^\n]s", subject);

    scanf("%c", &dummy);
    printf("MESSAGE : ");
    scanf("%[^\n]s", message);

    sprintf(buffer, "%s\n%s\n%s\n", to_email, subject, message);

    if(send(*c_sock, buffer, sizeof(buffer), 0) == -1)
    {
        perror("send");
    }

    memset(buffer, '\0', BUFSIZE);
    if (recv(*c_sock, buffer, BUFSIZE, 0) < 0)
    {
        printf("Error in receiving data.\n");
        return;
    }
    else
    {
        printf("\nServer: %s\n\n", buffer);
    }
}

int main()
{
    int c_sock;
    char my_mail_id[BUFSIZE];

    setServerConfigs();

    printf("Enter your email-address: ");
    scanf("%s", my_mail_id);
    int my_port = fetchPORT(my_mail_id);

    if(my_port == -1){
        printf("Email doesnot exist!\n");
        exit(1);
    }

    char opt; 
    while(1){
        scanf("%c", &opt);
        printf("Enter 1 to compose e-mail \t 2 to open inbox \t 0 to exit\n"); 
        scanf("%c", &opt);

        if(opt == '1') { // compose mail
            composeMail(&c_sock, my_port);
            close(c_sock);
        }
        else if(opt == '2') { // open inbox
            getMyMails(&c_sock, my_port);
            close(c_sock);
        }
        else if(opt == '0') { // exit
            close(c_sock);
            break;
        }
        else {
            printf("\nEnter a valid option\n");
        }
    }
    
    printf("Disconnected from the mail server.\n\n");
    return 0;
}