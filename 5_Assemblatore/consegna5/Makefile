SOURCES=main.o instruction.o assembler.o symbol_table.o
EXECUTABLE=assembler

assembler: $(SOURCES)
	gcc -o $(EXECUTABLE) $(SOURCES) -w

main.o: main.c assembler.h
	gcc -c main.c -w


instruction.o: instruction.c instruction.h symbol_table.h
	gcc -c instruction.c -w


assembler.o: assembler.c instruction.h symbol_table.h
	gcc -c assembler.c -w


symbol_table.o: symbol_table.c symbol_table.h 
	gcc -c symbol_table.c -w


clean:
	rm *.o assemble