CC = gcc
WRITE_DATA = write_data.c 
READ_DATA = read_data.c
W_TARGET = write
R_TARGET = read
CLEAR = clear_key.c

all: write_data read_data

$(W_TARGET): $(WRITE_DATA) 
	$(CC) -o $(W_TARGET) $(WRITE_DATA) 

$(R_TARGET): $(READ_DATA)
	$(CC) -o $(R_TARGET) $(READ_DATA)

clear: $(CLEAR)
	$(CC) -o clear $(CLEAR)
	
run_write: $(W_TARGET)
	./$(W_TARGET)
	
run_read: $(R_TARGET)
	./$(R_TARGET)

run_clear: clear
	./clear

clean:
	rm -f $(W_TARGET) $(R_TARGET) clear
