#ifndef PARSER_H
#define PARSER_H

#define BINARY_INST_SIZE 16

char* cinst(char* oldInst, unsigned int lineNumber);
char parse(char* inst, char* dest, char* comp, char* jump);
int containsDest(char* str);

char* ainst(char* oldInst, SymbolTable *symbolTable);
void decToBinary(int n, char* str);

#endif