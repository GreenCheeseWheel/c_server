#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sockets/recv.h"

// We must think of the possibility of receiving data in chunks
void recv_with_socket(int sckt, char *buffer, void (*f)(char*)) {
    int bytes_read = 0;
    int full_bytes = 0;

    // El buffer full_buffer es, en esencia, un array dinámico.
    char *full_buffer = malloc(sizeof(buffer));

    while ( (bytes_read = recv(sckt, buffer, sizeof(buffer), 0)) != -1 )
    {   
        
        full_bytes += bytes_read;
        full_buffer = (char*)realloc(full_buffer, full_bytes);
        memmove(&full_buffer[full_bytes -bytes_read], buffer, bytes_read);

        
    }
}