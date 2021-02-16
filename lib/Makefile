# OS specific part
ifeq ($(OS),Windows_NT)
	RM = del /S
	RMALLO = del /S *.o
	RMDIR = -RMDIR /S /Q
	#MKDIR = -mkdir
	#ERRIGNORE = 2>NUL || true
	#SEP="\\"
else
	RM = rm -f
	RMALLO = find . -type f -name '*.o' -print -delete
	RMDIR = rm -rf 
	#MKDIR = mkdir -p
	#ERRIGNORE = 2>/dev/null
	#SEP=/
endif
#PSEP = $(strip $(SEP))


SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)


CC	 = gcc
CFLAGS	 = -c -Wall
LFLAGS	 = 
INCLUDE = -I .

.PHONY: all
all: $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

#savedata.o: savedata.c savedata.h
#	$(CC) $(FLAGS) $(INCLUDE) -o savedata.o savedata.c

#huffman.o: huffman.c huffman.h
#	$(CC) $(FLAGS) $(INCLUDE) -o huffman.o huffman.c

.PHONY: clean
clean:
	$(RMALLO)