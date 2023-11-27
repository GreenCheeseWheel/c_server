#ifndef _UTILS_H_
#define _UTILS_H_

typedef struct
{
    int *sckts;


} ClosingProto;

void CloseProto(ClosingProto *proto);
void DieWithUserMessage(char *failure, char *reasons, ClosingProto *proto);

#endif