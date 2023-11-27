#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "utils.h"

void CloseProto(ClosingProto *proto) {
    if(proto != NULL) {
        while (*proto->sckts > 0) {
            close(*proto->sckts);
            proto->sckts += 1;
        }
    
    }
}

void DieWithUserMessage(char *failure, char *reasons, ClosingProto *proto) {
    printf("Error type %s -- %s\r\n", failure, reasons);

    CloseProto(proto);

    exit(-1);
}

