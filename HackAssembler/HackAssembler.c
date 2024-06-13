/*
Hack Assembly assembler

Take in a .asm file and convert it to a .txt file containing the instructions in
1s an 0s, one instruction per line

Create symbol table
	Initiated with predefined symbols
	
	1st read adds all labels in program
	
	2nd read converts all symbols in program into corresponding values
	
	
	
	Symbol table:
		Dynamically allocated array of structs
			Struct will contain a pointer to string (symbol) and another pointer
			to a string (defintion)
	

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"
#include "Preprocessor.h"

#undef DEBUG_FORMATTER
#define DEBUG_PREPROCESSOR

char* format(char *str);

/******************************************************************************
Function: main

Summary: loops through assembly file and assembles instructions
*******************************************************************************
Pseudocode:

Begin
	Verify commandline argument
	
	Open .asm file
	
	Loop while get instruction != null
		Remove leading whitespace
		If instruction is not empty nor a comment then
			Parse instruction
		End if
	End loop
End
******************************************************************************/

int main (int argc, char **argv)
{
	FILE *asmFile, *outputFile;
	char instruction[MAX_LINE_LEN + 1];
	char *formattedInst;
	char *binaryInst;
	
	unsigned int lineNumber = 1;
	int tableSize = DEFAULT_TABLE_SIZE;
	
	printf("%u\n", sizeof(SymbolTable) + tableSize * sizeof(Symbol));
	
	// I use the struct hack to include dynamic memory array (symbols) in SymbolTable struct
	SymbolTable *symbolTable = (SymbolTable *) malloc (sizeof(SymbolTable) + tableSize * sizeof(Symbol)); 
	
	symbolTable->tableSize = tableSize;
	symbolTable->nextSymbol = 0;
	
	if (argc < 2)
	{
		printf("Error, you must include a file to be assembled\n");
		return 1;
	}
	
	asmFile = fopen(argv[1], "r");
	if (asmFile == NULL)
	{
		printf("Error, unable to open %s\n", argv[1]);
		return 1;
	}
	
	outputFile = fopen(argv[2], "w");
	if (outputFile == NULL)
	{
		printf("Error, unable to open %s\n", argv[2]);
		return 1;
	}
	
	preprocess(asmFile, symbolTable);
	
	#ifdef DEBUG_PREPROCESSOR
		for (int i = 0; i < symbolTable->nextSymbol; i++)
		{
			printf("%s - %d - %u\n", symbolTable->symbols[i].name, symbolTable->symbols[i].addr, (unsigned long int)(symbolTable->symbols+i)/36);
		}
		printf("\n");
	#endif

	rewind(asmFile);
	while (fgets(instruction, MAX_LINE_LEN + 2, asmFile) != NULL)
	{
		formattedInst = format(instruction);
		
		if (formattedInst[0] != '\0')
		{
			
			#ifdef DEBUG_FORMATTER
				puts(formattedInst);
			#endif
			
			/*if (formattedInst[0] == '@')
			{
				binaryInst = ainst(formattedInst);
			}
			else
			{
				binaryInst = cinst(formattedInst, lineNumber);
			}
			
			fprintf(outputFile, "%s\n", binaryInst);*/
		}
		
		lineNumber++;
	}
	
	free(symbolTable);
	
	return 1;
}

/******************************************************************************
Function: format

Summary:  processes assembly file before any parsing is done, removing 
	comments and whitespace before or after instructions. 
	Any lines lines containing only whitespace and/or comments will be
	returned as empty strings
******************************************************************************/

char* format(char *oldStr)
{
	char *newStr;
	
    int i, j;
	
    for (i = 0, j = 0; oldStr[i] != '\0' && oldStr[i] != '\n' && (oldStr[i] != '/' && oldStr[i+1] != '/'); i++, j++)
    {
		while (oldStr[i] == ' ' || oldStr[i] == '\t')   // Skip over whitespace
		{
			i++;
		}
		
		newStr[j] = oldStr[i];
    }
	
    newStr[j-1] = '\0';
	
	return newStr;
}