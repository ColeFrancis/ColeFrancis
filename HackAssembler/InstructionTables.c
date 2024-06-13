#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InstructionTables.h"

char* destTable(char* dest, unsigned int lineNumber)
{
	if (dest[0] == '\0')
	{
		return "000";
	}
	else if (strcmp(dest, "M") == 0)
	{
		return "001";
	}
	else if (strcmp(dest, "D") == 0)
	{
		return "010";
	}
	else if (strcmp(dest, "MD") == 0)
	{
		return "011";
	}
	else if (strcmp(dest, "A") == 0)
	{
		return "100";
	}
	else if (strcmp(dest, "AM") == 0)
	{
		return "101";
	}
	else if (strcmp(dest, "AD") == 0)
	{
		return "110";
	}
	else if (strcmp(dest, "AMD") == 0)
	{
		return "111";
	}
	else
	{
		fprintf(stderr, "Error, syntax error on line %d: %s\n", lineNumber, dest);
		exit(1);
	}
}

char* compTable(char* comp, unsigned int lineNumber)
{
	if (strcmp(comp, "0") == 0)
	{
		return "101010";
	}
	else if (strcmp(comp, "1") == 0)
	{
		return "111111";
	}
	else if (strcmp(comp, "-1") == 0)
	{
		return "111010";
	}
	else if (strcmp(comp, "D") == 0)
	{
		return "001100";
	}
	else if (strcmp(comp, "A") == 0 || strcmp(comp, "M") == 0)
	{
		return "110000";
	}
	else if (strcmp(comp, "!D") == 0)
	{
		return "001101";
	}
	else if (strcmp(comp, "!A") == 0 || strcmp(comp, "!M") == 0)
	{
		return "110001";
	}
	else if (strcmp(comp, "-D") == 0)
	{
		return "001111";
	}
	else if (strcmp(comp, "-A") == 0 || strcmp(comp, "-M") == 0)
	{
		return "110011";
	}
	else if (strcmp(comp, "D+1") == 0)
	{
		return "011111";
	}
	else if (strcmp(comp, "A+1") == 0 || strcmp(comp, "M+1") == 0)
	{
		return "110111";
	}
	else if (strcmp(comp, "D-1") == 0)
	{
		return "001110";
	}
	else if (strcmp(comp, "A-1") == 0 || strcmp(comp, "M-1") == 0)
	{
		return "110010";
	}
	else if (strcmp(comp, "D+A") == 0 || strcmp(comp, "D+M") == 0)
	{
		return "000010";
	}
	else if (strcmp(comp, "D-A") == 0 || strcmp(comp, "D-M") == 0)
	{
		return "010011";
	}
	else if (strcmp(comp, "A-D") == 0 || strcmp(comp, "M-D") == 0)
	{
		return "000111";
	}
	else if (strcmp(comp, "D&A") == 0 || strcmp(comp, "D&M") == 0)
	{
		return "000000";
	}
	else if (strcmp(comp, "D|A") == 0 || strcmp(comp, "D|M") == 0)
	{
		return "010101";
	}
	else 
	{
		fprintf(stderr, "Error, syntax error on line %d: %s\n", lineNumber, comp);
		exit(1);
	}
}

char* jumpTable(char* jump, unsigned int lineNumber)
{
	if (jump[0] == '\0')
	{
		return "000";
	}
	else if (strcmp(jump, "JGT") == 0)
	{
		return "001";
	}
	else if (strcmp(jump, "JEQ") == 0)
	{
		return "010";
	}
	else if (strcmp(jump, "JGE") == 0)
	{
		return "011";
	}
	else if (strcmp(jump, "JLT") == 0)
	{
		return "100";
	}
	else if (strcmp(jump, "JNE") == 0)
	{
		return "101";
	}
	else if (strcmp(jump, "JLE") == 0)
	{
		return "110";
	}
	else if (strcmp(jump, "JMP") == 0)
	{
		return "111";
	}
	else
	{
		fprintf(stderr, "Error, syntax error on line %d: %s\n", lineNumber, jump);
		exit(1);
	}
}