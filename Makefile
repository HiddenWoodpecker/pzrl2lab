.PHONY: all run clean
TARGET = lab2
all: $(TARGET)

calculate.o:
	gcc -c calculate.c -o calculate.o
parse.o:
	gcc -c parse.c -o parse.o
main.o:
	gcc -c main.c -o main.o
$(TARGET): main.o calculate.o parse.o
	gcc main.o calculate.o parse.o -lm -o $(TARGET)
clean:
	rm -rf *.exe *.o
run: $(TARGET)
	./$(TARGET)