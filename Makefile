 # Makefile
 # Chris Alves
 # Password Encrypter

CC=gcc
CFLAGS= -o
TARGET=QuickPasswordEncrypter
all=$(TARGET)
DATA=runScript

#compiles
$(TARGET).out: $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).out $(TARGET).c


#removes executable
clean:
	rm $(TARGET).out

#shows warnings after compiling
debug:
	$(CC) -Wall $(CFLAGS) $(TARGET).out $(TARGET).c

#compiles then runs gdb with the text user interface
gdb:
	$(CC) -g $(CFLAGS) $(TARGET).out $(TARGET).c
	gdb -tui $(TARGET).out

#runs program
run:
	$(CC) $(CFLAGS) $(TARGET).out $(TARGET).c
	./$(TARGET).out

#runs program with a script
runs:
	$(CC) $(CFLAGS) $(TARGET).out $(TARGET).c
	./$(TARGET).out < $(DATA)
