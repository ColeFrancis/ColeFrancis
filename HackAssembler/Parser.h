#ifndef PARSER_H
#define PARSER_H

char parse(char* inst, char* dest, char* comp, char* jump);
char* ainst (char* oldInst);
char* cinst(char* oldInst, unsigned int lineNumber);
void decToBinary(int n, char* str);
int containsDest(char* str);

#endif