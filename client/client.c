#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "sockets/recv.h"
#include "sockets/send.h"
#include "utils/utils.h"

#define BUFFER_SIZE 500


int main(int argc, char *argv[])
{
    if(argc < 4) {
        DieWithUserMessage("Parameter(s)", "<Server Address> <Echo Word> [<Server Port>]", NULL);
    }

    char *addr = argv[1];
    char *echo = argv[2];
    int port = atoi(argv[3]);

    int sckt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(sckt == -1) {
        DieWithUserMessage("Socket(s)", "socket() == -1", NULL);
    }

    ClosingProto proto;
    memset(&proto, 0, sizeof(proto));
    proto.sckts = &sckt;

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    int success = inet_pton(AF_INET, addr, &server_addr.sin_addr.s_addr);

    if(success <= 0) {
        DieWithUserMessage("IP Convert", "inet_pton() == 0", &proto);
    }
    server_addr.sin_port = htons(port);
    
    int connect_success = connect(sckt, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(connect_success < 0) {
        DieWithUserMessage("Socket Connection", "connect() failure", &proto);
    }

    ssize_t num_bytes = send(sckt, echo, strlen(echo), 0);
    if(num_bytes < 0) {
        DieWithUserMessage("Socket Send", "send() failure at echo", &proto);
    }

    int total_bytes = 0;
    char buffer[BUFFER_SIZE];

    while (total_bytes < strlen(echo))
    {
        int bytes_rcvd = recv(sckt, buffer, BUFFER_SIZE-1, 0);
        total_bytes += bytes_rcvd;
        buffer[bytes_rcvd] = '\0';
    }
    
    printf("ECHO BUFFER %s\r\n", buffer);
    CloseProto(&proto);

    return 0;
}
