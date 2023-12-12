.PHONY: all run clean
TARGET = lab2
all: $(TARGET)

calculate.o:
	gcc -c calculate.c -o calculate.o
parse.o:
	gcc -c parse.c -o parse.o
$(TARGET): calculate.o parse.o
	gcc main.c calculate.o parse.o -lm -o $(TARGET) 

clean:
	rm -rf *.o *.exe $(TARGET)
run: $(TARGET)
	./$(TARGET)