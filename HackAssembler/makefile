HackAssembler: HackAssembler.o Parser.o InstructionTables.o Preprocessor.o
	gcc -o HackAssembler HackAssembler.o Parser.o InstructionTables.o Preprocessor.o
	
HackAssembler.o: HackAssembler.c Parser.h Preprocessor.h
	gcc -c HackAssembler.c
	
Parser.o: Parser.c Parser.h InstructionTables.h
	gcc -c Parser.c
	
InstructionTables.o: InstructionTables.c InstructionTables.h
	gcc -c InstructionTables.c
	
Preprocessor.o: Preprocessor.c Preprocessor.h
	gcc -c Preprocessor.c