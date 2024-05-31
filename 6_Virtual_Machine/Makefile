SOURCES=main.o translator.o parser.o
EXECUTABLE=VMtranslator

VMtranslator: $(SOURCES)
	gcc -o $(EXECUTABLE) $(SOURCES) -w

main.o: main.c translator.h parser.h
	gcc -c main.c -w

translator.o: translator.c translator.h parser.h
	gcc -c translator.c -w

parser.o: parser.c parser.h 
	gcc -c parser.c -w

clean:
	rm *.o VMtranslator