#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#define DEFAULT_TABLE_SIZE 30

#define MAX_LINE_LEN 80
#define MAX_SYMBOL_LEN 40

typedef struct
{
	char name[MAX_SYMBOL_LEN];
	int addr;
} Symbol;

typedef struct
{
	unsigned int tableSize;
	unsigned int nextSymbol;
	int nextAddr;
	Symbol symbols[];
} SymbolTable ;

void preprocess (FILE *asmFile, SymbolTable **symbolTable);
void populateTable (SymbolTable *symbolTable);
void addSymbol (SymbolTable **symbolTable, char* name, int len, int addr);

int lookupTable (SymbolTable *symbolTable, char* name);
int getAddress (SymbolTable *symbolTable, char* name);

#endif