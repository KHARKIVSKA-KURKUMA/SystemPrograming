TARGET = process
SRC = process.c
INPUT_FILE = inp.txt
OUTPUT_FILE = out.txt  

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	cc -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) $(INPUT_FILE) $(OUTPUT_FILE)  

clean:
	rm -f $(TARGET) $(OUTPUT_FILE)
