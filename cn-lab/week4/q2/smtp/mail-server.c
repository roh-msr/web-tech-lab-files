#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFSIZE 1024
#define SERVERS_COUNT 2

char* my_email;

char my_inbox[10][750];
int my_inbox_count = 0;

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

void connect_request(int *sockfd, struct sockaddr_in *my_addr, int PORT)
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

void receiveEmail(int c_sock){
    char buf[BUFSIZE];

    send(c_sock, "ACK!", 5, 0);

    memset(buf, '\0', BUFSIZE);
    if (recv(c_sock, buf, BUFSIZE, 0) < 0)
    {
        perror("recv");
        return;
    }

    memset(my_inbox[my_inbox_count], '\0', BUFSIZE);
    strcpy(my_inbox[my_inbox_count++], buf);
    close(c_sock);
} 

int sendEmail(int MS_PORT, char to_email[], char subject[], char message[], time_t sent_time) {
    int ms_sock;
    char buffer[BUFSIZE];

    // Get time
    struct tm *ptm = gmtime(&sent_time);
    if (ptm == NULL) {
        puts("The localtime() function failed");
        close(ms_sock);
        return -1;
    }

    // Make connection
    make_connection(&ms_sock, MS_PORT);

    // Request to receive the mail
    sprintf(buffer, "3");
    send(ms_sock, buffer, BUFSIZE, 0);

    // Get acknowlegement from Mail Server
    memset(buffer, '\0', BUFSIZE);
    if (recv(ms_sock, buffer, BUFSIZE, 0) < 0)
    {
        perror("recv");
        close(ms_sock);
        return -1;
    }

    // Send the mail
    memset(buffer, '\0', BUFSIZE);
    sprintf(buffer, "FROM : %s\nTO : %s\nSUBJECT : %s\nMESSAGE : %s\nSENT AT : %s\n", my_email, to_email, subject, message, asctime(ptm));

    send(ms_sock, buffer, BUFSIZE, 0);
    
    close(ms_sock);
}

void composeEmail(int i){
    char buf[BUFSIZE];
    char recv_buf[BUFSIZE];
    char* rest;
    char* to_email;
    char* subject;
    char* message;
    int TO_PORT;
    int sent = -1;

    // Send acknowledgement!
    sprintf(buf, "WRITE YOUR EMAIL!");
    if(send(i, buf, sizeof(buf), 0) == -1)
    {
        perror("send");
        return;
    }

    // Receive the values from the user-agent
    memset(buf, '\0', BUFSIZE);
    if (recv(i, buf, BUFSIZE, 0) < 0)
    {
        perror("recv");
        return;
    }

    // Extract the text!
    rest = buf;
    to_email = strtok_r(rest, "\n", &rest);
    subject = strtok_r(rest, "\n", &rest);
    message = strtok_r(rest, "\n", &rest);

    // Find the port of the to_email server
    TO_PORT = fetchPORT(to_email);

    // memset(buf, '\0', BUFSIZE);
    // Bounce the email!
    if(TO_PORT == -1){
        sprintf(recv_buf, "MAIL NOT SENT! SEEMS SUCH EMAIL DOESN'T EXIST!!");
    }
    else{ // Send the mail if the email exists!
        sent = sendEmail(TO_PORT, to_email, subject, message, time(NULL));
    }

    if(sent != -1)
        sprintf(recv_buf, "MAIL SENT SUCCESSFULLY!");

    if(send(i, recv_buf, sizeof(recv_buf), 0) == -1)
    {
        perror("send");
    }
}

void getInboxEmails(int k){
    char buf[BUFSIZE * my_inbox_count];
    char* delim = "\n==================\n";

    for(int i = 0; i < my_inbox_count; ++i){
        strcat(buf, my_inbox[i]);
        strcat(buf, delim);
    }

    if(send(k, buf, sizeof(buf), 0) == -1)
    {
        perror("send");
    }
}

void send_recv(int i, fd_set *master, int sockfd, int fdmax)
{
    int nbytes_recvd, j;
    char recv_buf[BUFSIZE], buf[BUFSIZE];

    if ((nbytes_recvd = recv(i, recv_buf, BUFSIZE, 0)) < 0)
    {
        perror("recv");
    }

    if(strncmp(recv_buf, "1", 1) == 0){
        composeEmail(i);
    }
    else if(strncmp(recv_buf, "2", 1) == 0){
        getInboxEmails(i);
    }
    else if(strncmp(recv_buf, "3", 1) == 0){
        receiveEmail(i);
    }
    else{
        printf("INVALID REQUEST!");
    }

    close(i);
    printf("socket %d hung up\n", i);
    FD_CLR(i, master);
}

int main()
{
    char my_mail_id[BUFSIZE];

    setServerConfigs();

    printf("Enter your email-address: ");
    scanf("%s", my_mail_id);
    my_email = my_mail_id;
    int PORT = fetchPORT(my_mail_id);

    if(PORT == -1){
        printf("Email doesnot exist!\n");
        exit(1);
    }

    fd_set master;
    fd_set read_fds;
    int fdmax, i;
    int sockfd = 0;
    struct sockaddr_in my_addr, client_addr;

    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    connect_request(&sockfd, &my_addr, PORT);
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