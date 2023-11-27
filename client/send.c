#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sockets/send.h"
#include <sys/socket.h>
#include <net/route.h>
#include <netdb.h>
#define PORT 80

void close_and_exit(int sckt, char *message) {
    printf("%s\n", message);
    close(sckt);
    exit(-1);
}

// Send through socket sckt the first n bytes of buffer to host_addr 
void send_by_socket(int sckt, int n, char *buffer, struct hostent *host_addr) {
    
    
    if(host_addr == NULL) {
        close_and_exit(sckt, "Host cannot be found");
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_port = htons(3001);
    server_addr.sin_family = AF_INET;
    memcpy(&server_addr.sin_addr.s_addr, host_addr->h_addr_list[0], host_addr->h_length);

    int connection_status = connect(sckt, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    if(connection_status == -1) {
        close_and_exit(sckt, "Error connecting socket to host");
    }
 
    int send_status = write(sckt, buffer, strlen(buffer));
    
    
    if(send_status == -1) {
        close_and_exit(sckt, "Error sending buffer data through socket");
    }

    
}