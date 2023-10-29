TARGET = process
SRC = process.c
RES = destination.txt
CC = gcc 

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(RES)

