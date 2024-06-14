#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "Preprocessor.h"

#include "Parser.h"
#include "InstructionTables.h"

char* cinst(char* oldInst, unsigned int lineNumber)
{
	char* newInst = (char *) malloc(BINARY_INST_SIZE + 1);
	
	char* dest = (char *) malloc(3);
	char* comp = (char *) malloc(3);
	char* jump = (char *) malloc(3);
	
	
	newInst[0] = '1';
	newInst[1] = '1';
	newInst[2] = '1';
	
	newInst[3] = parse(oldInst, dest, comp, jump);
	
	strcpy(newInst+4, compTable(comp, lineNumber));
	strcpy(newInst+10, destTable(dest, lineNumber));
	strcpy(newInst+13, jumpTable(jump, lineNumber));
	
	newInst[BINARY_INST_SIZE] = '\0';
	
	free(dest);
	free(comp);
	free(jump);
	
	return newInst;
}

char parse(char* inst, char* dest, char* comp, char* jump)
{
	char a;
	int i = 0, j;
	
	if (containsDest(inst)) // Parse dest
	{
		for (j = 0; inst[i] != '='; i++, j++)
		{
			dest[j]=inst[i];
		}
		
		dest[j] = '\0';
		
		i++;
	}
	else
	{
		dest[0] = '\0';
	}
	
	a = '0';
	
	for (j = 0; inst[i] != ';' && inst[i] != '\0'; i++, j++) // Parse comp
	{
		comp[j] = inst[i];
		
		if (comp[j] == 'M')
		{
			a = '1';
		}
	}
	
	comp[j] = '\0';
	
	if (inst[i] == ';') // Parse jump
	{
		i++;
		
		for (j = 0; inst[i] != '\0'; i++, j++)
		{
			jump[j] = inst[i];
		}
		
		jump[j] = '\0';
	}
	else
	{
		jump[0] = '\0';
	}
	
	return a;
}

int containsDest(char* str)
{
	int i;
	
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] == '=')
		{
			return 1;
		}
	}
	
	return 0;
}

char* ainst(char* oldInst, SymbolTable *symbolTable)
{
	int addr;
	char* newInst = (char *) malloc(BINARY_INST_SIZE + 1);
	
	newInst[0] = '0';
	
	if (isdigit(oldInst[1])) 
	{
		addr = atoi(oldInst+1);
	}
	else
	{
		addr = getAddress(symbolTable, oldInst+1);
	}
	
	decToBinary(addr, newInst+1);
	
	newInst[BINARY_INST_SIZE] = '\0';
	
	return newInst;
}

void decToBinary(int n, char* str)
{
	int i, j, k;
	
    // Size of address is 15 bits
    for (i = BINARY_INST_SIZE - 2, j = 0; i >= 0; i--, j++) 
	{
        k = n >> i;
		
		(k & 1) ? 
			(str[j] = '1') : 
			(str[j] = '0');
    }
}