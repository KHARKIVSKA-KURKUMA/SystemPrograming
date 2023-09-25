TARGET = process
SRC = process.c
INPUT_FILE = inp.txt

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	cc -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) $(INPUT_FILE)

clean:
	rm -f $(TARGET)
