#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "sockets/recv.h"
#include "sockets/send.h"

#define BUFFER_SIZE 500


int main(int argc, char *argv[])
{
    struct sockaddr_in localhost =  {
        .sin_port = htons(3500),
        .sin_family = AF_INET,
    };

    localhost.sin_addr.s_addr = INADDR_ANY;

    int sckt = socket(AF_INET, SOCK_STREAM, 0);

    bind(sckt, (struct sockaddr*)&localhost, sizeof(localhost));
    listen(sckt, 1);
    int client_sckt = accept(sckt, NULL, NULL);

    char buffer_recv[BUFFER_SIZE]; 
    recv_with_socket(client_sckt, buffer_recv, NULL);
    
    close(client_sckt);
    close(sckt);
    
    return 0;
}
