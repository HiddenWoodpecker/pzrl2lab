.PHONY: all run clean

all: $(TARGET)

calculate.o:
	gcc -c calculate.c -o calculate.o
parse.o:
	gcc -c parse.c -o parse.o
$(TARGET): calculate.o parse.o
	gcc main.c calculate.o parse.o -o $(TARGET)

clean:
	rm -r *.o $(TARGET)
run: $(TARGET)
	./$(TARGET)