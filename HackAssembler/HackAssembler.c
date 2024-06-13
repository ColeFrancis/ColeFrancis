#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Preprocessor.h"
#include "Parser.h"

#define DEBUG_FORMATTER
#define DEBUG_PREPROCESSOR

void formatInst(char *oldStr, char *newStr);

/******************************************************************************
Function: main

Summary: loops through assembly file and assembles instructions
*******************************************************************************
Pseudocode:

Begin
	Verify commandline argument
	
	Open .asm file
	
	Allocate symbol table
	Preprocess asm file
	
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
	
	// I use the struct hack to include dynamic memory array (symbols) in SymbolTable struct
	SymbolTable *symbolTable = (SymbolTable *) malloc (sizeof(SymbolTable) + tableSize * sizeof(Symbol)); 
	
	symbolTable->tableSize = tableSize;
	symbolTable->nextSymbol = 0;
	symbolTable->nextAddr = 0;
	
	preprocess(asmFile, symbolTable);

	rewind(asmFile);
	while (fgets(instruction, MAX_LINE_LEN + 2, asmFile) != NULL)
	{
		formatInst(instruction, formattedInst);
		
		if (formattedInst[0] != '\0' && formattedInst[0] != '(')
		{
			
			#ifdef DEBUG_FORMATTER
				puts(formattedInst);
			#endif
			
			if (formattedInst[0] == '@')
			{
				binaryInst = ainst(formattedInst, symbolTable);
			}
			else
			{
				binaryInst = cinst(formattedInst, lineNumber); // Line number included for printing errors
			}
			
			fprintf(outputFile, "%s\n", binaryInst);
		}
		
		lineNumber++;
	}
	
	#ifdef DEBUG_PREPROCESSOR
		printf("\nSymbols:\n");
		
		for (int i = 0; i < symbolTable->nextSymbol; i++)
		{
			printf("%s - %d\n", symbolTable->symbols[i].name, symbolTable->symbols[i].addr);
		}
		printf("\n");
	#endif
	
	free(symbolTable);
	
	return 1;
}

/******************************************************************************
Function: formatInst

Summary:  processes assembly file before any parsing is done, removing 
	comments and whitespace before or after instructions. 
	Any lines lines containing only whitespace and/or comments will be
	returned as empty strings
******************************************************************************/

void formatInst(char *oldStr, char *newStr)
{
	char *p = oldStr;
	char *q = newStr;
	
	while (*p != '\0')
	{
		
		while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		{
			p++;
		}
		
		if (*p == '/' && *(p+1) == '/')
		{
			break;
		}
		
		*q++ = *p++;
	}
	
	*q = '\0';
}