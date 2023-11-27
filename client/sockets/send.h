#ifndef SEND_H_
#define SEND_H_
#include <netdb.h>

void send_by_socket(int sctk, int n, char *buffer, struct hostent *host_addr);

#endif