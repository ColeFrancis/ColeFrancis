#ifndef PARSER_H
#define PARSER_H

char parse(char* inst, char* dest, char* comp, char* jump);
int containsDest(char* str);

char* ainst(char* oldInst, SymbolTable *symbolTable);
void decToBinary(int n, char* str);

char* cinst(char* oldInst, unsigned int lineNumber);

#endif