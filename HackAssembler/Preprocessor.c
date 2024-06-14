#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Preprocessor.h"

/******************************************************************************
Function: preprocess

Summary:  reads assembly file and adds all labels to the symbol table
*******************************************************************************
Pseudocode:

Begin
	Populate table with default symbols
	
	Loop through all instructions
		Skip all leading whitespace of instruction
		
		If instruction is a C or A instruction then
			Increment line number
		Else If instruction is a label (xxx) then
			Find length of symbol
			add new entry to the symbol table 
		End if
	End Loop
End

******************************************************************************/

void preprocess (FILE *asmFile, SymbolTable *symbolTable)
{
	unsigned int lineNumber;
	char instruction[MAX_LINE_LEN + 1];
	int symbolStart, symbolLen;
	
	populateTable(symbolTable);

	lineNumber = 0;
	
	while (fgets(instruction, MAX_LINE_LEN + 2, asmFile) != NULL)
	{
		symbolStart = 0;
		
		while (instruction[symbolStart] == ' ' || instruction[symbolStart] == '\t' || instruction[symbolStart] == '\n')
		{
			symbolStart++;
		}
		
		if (instruction[symbolStart] != '/' && instruction[symbolStart] != '(' && instruction[symbolStart + 1] != '\n' && instruction[symbolStart] != '\0') // Third condition used for blank lines
		{
			lineNumber++;
		}
		else if (instruction[symbolStart] == '(')
		{
			symbolStart++;
			
			symbolLen = 1; // Starts at one to leave room for a null terminator
			
			while (instruction[symbolStart + symbolLen] != ')' &&  symbolLen < MAX_SYMBOL_LEN)
			{
				symbolLen++;
			}
			
			addSymbol(&symbolTable, instruction+symbolStart, symbolLen, lineNumber);
		}
	}
}

void populateTable (SymbolTable *symbolTable)
{
	strcpy(symbolTable->symbols[0].name, "R0");
	symbolTable->symbols[0].addr = 0;
	strcpy(symbolTable->symbols[1].name, "R1");
	symbolTable->symbols[1].addr = 1;
	strcpy(symbolTable->symbols[2].name, "R2");
	symbolTable->symbols[2].addr = 2;
	strcpy(symbolTable->symbols[3].name, "R3");
	symbolTable->symbols[3].addr = 3;
	strcpy(symbolTable->symbols[4].name, "R4");
	symbolTable->symbols[4].addr = 4;
	strcpy(symbolTable->symbols[5].name, "R5");
	symbolTable->symbols[5].addr = 5;
	strcpy(symbolTable->symbols[6].name, "R6");
	symbolTable->symbols[6].addr = 6;
	strcpy(symbolTable->symbols[7].name, "R7");
	symbolTable->symbols[7].addr = 7;
	strcpy(symbolTable->symbols[8].name, "R8");
	symbolTable->symbols[8].addr = 8;
	strcpy(symbolTable->symbols[9].name, "R9");
	symbolTable->symbols[9].addr = 9;
	strcpy(symbolTable->symbols[10].name, "R10");
	symbolTable->symbols[10].addr = 10;
	strcpy(symbolTable->symbols[11].name, "R11");
	symbolTable->symbols[11].addr = 11;
	strcpy(symbolTable->symbols[12].name, "R12");
	symbolTable->symbols[12].addr = 12;
	strcpy(symbolTable->symbols[13].name, "R13");
	symbolTable->symbols[13].addr = 13;
	strcpy(symbolTable->symbols[14].name, "R14");
	symbolTable->symbols[14].addr = 14;
	strcpy(symbolTable->symbols[15].name, "R15");;
	symbolTable->symbols[15].addr = 15;
	
	strcpy(symbolTable->symbols[16].name, "SCREEN");
	symbolTable->symbols[16].addr = 16384;
	
	strcpy(symbolTable->symbols[17].name, "KBD");
	symbolTable->symbols[17].addr = 24576;
	
	strcpy(symbolTable->symbols[18].name, "SP");
	symbolTable->symbols[18].addr = 0;
	strcpy(symbolTable->symbols[19].name, "LCL");
	symbolTable->symbols[19].addr = 1;
	strcpy(symbolTable->symbols[20].name, "ARG");
	symbolTable->symbols[20].addr = 2;
	strcpy(symbolTable->symbols[21].name, "THIS");
	symbolTable->symbols[21].addr = 3;
	strcpy(symbolTable->symbols[22].name, "THAT");
	symbolTable->symbols[22].addr = 4;
	
	symbolTable->nextSymbol += 23;
	symbolTable->nextAddr += 16;
}

void addSymbol (SymbolTable **symbolTable, char* name, int len, int addr)
{
	unsigned int newSize;
	
	if ((*symbolTable)->nextSymbol >= (*symbolTable)->tableSize)														// FIX: The resizing does not work
    {
        newSize = (*symbolTable)->tableSize * 2;
		
		printf("%u\n", sizeof(SymbolTable) + newSize * sizeof(Symbol));
		
        SymbolTable *newTable = (SymbolTable *) realloc(*symbolTable, sizeof(SymbolTable) + newSize * sizeof(Symbol));
        
        if (newTable == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\nUnable to add label to symbol table.\n");
            return;
        }

        *symbolTable = newTable;
        (*symbolTable)->tableSize = newSize;
    }
	
	if (len >= MAX_SYMBOL_LEN) 
	{
		len = MAX_SYMBOL_LEN - 1;
	}
	strncpy((*symbolTable)->symbols[(*symbolTable)->nextSymbol].name, name, len);
	(*symbolTable)->symbols[(*symbolTable)->nextSymbol].name[len] = '\0';
	
	(*symbolTable)->symbols[(*symbolTable)->nextSymbol].addr = addr;
	
	(*symbolTable)->nextSymbol++;
}

/******************************************************************************
Function: lookupTable

Summary:  looks up a symbol name in the table, returns -1 if it does not exist
*******************************************************************************
Pseudocode:

Begin
	Set address to -1
	
	Loop through symbolTable
		If symbol name matches name then
			Set address to symbol address
		End if
	End loop
	
	Return address
End

******************************************************************************/

int lookupTable (SymbolTable *symbolTable, char* name)
{
	int i, addr;
	
	addr = -1;
	
	for (i = 0; i < symbolTable->nextSymbol; i++)
	{
		if (strcmp( symbolTable->symbols[i].name, name ) == 0)
		{
			addr = symbolTable->symbols[i].addr;
		}
	}
	
	return addr;
}

/******************************************************************************
Function: lookupTable

Summary:  gets the address from a symbol in the symbol table, adds a new symbol
	if it does not exits
*******************************************************************************
Pseudocode:

Begin
	Loop through 
End

******************************************************************************/

int getAddress (SymbolTable *symbolTable, char* name)
{
	int addr;
	
	addr = lookupTable(symbolTable, name);
	
	if (addr < 0) // If address does not exist in table already
	{
		addr = symbolTable->nextAddr;
		
		addSymbol(&symbolTable, name, sizeof(name), symbolTable->nextAddr);
		
		symbolTable->nextAddr++;
	}
	
	return addr;
}