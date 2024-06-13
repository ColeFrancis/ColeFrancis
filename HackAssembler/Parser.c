#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "InstructionTables.h"

char parse(char* inst, char* dest, char* comp, char* jump)
{
	char a = '0';
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
	
	for (j = 0; inst[i] != ';' && inst[i] != '\0'; i++, j++) // Parse comp
	{
		comp[j] = inst[i];
		
		if (comp[j] == 'M')
		{
			a = '1';
		}
	}
	
	if (inst[i] == ';') // Parse jump
	{
		i++;
		
		for (j = 0; inst[i] != '\0'; i++, j++)
		{
			jump[j] = inst[i];
		}
	}
	else
	{
		jump[0] = '\0';
	}
	
	return a;
}

char* ainst(char* oldInst)
{
	int addr;
	char* newInst = (char *) malloc(16);
	
	newInst[0] = '0';
	
	addr = atoi(oldInst+1);
	decToBinary(addr, newInst+1);
	
	return newInst;
}

char* cinst(char* oldInst, unsigned int lineNumber)
{
	char* newInst = (char *) malloc(16);
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
	
	free(dest);
	free(comp);
	free(jump);
	
	return newInst;
}

void decToBinary(int n, char* str)
{
	int i, j, k;
	
    // Size of address is 15 bits
    for (i = 14, j = 0; i >= 0; i--, j++) {
        k = n >> i; // right shift
        if (k & 1) // helps us know the state of first bit
              str[j] = '1';
        else str[j] = '0';
    }
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